#pragma once

#include <llvm/IR/IRBuilder.h>

#include <dist/block_gen.h>
#include <dist/loop_shapes.h>
#include <dist/synth.h>
#include <dist/synth_metadata.h>

#include <memory>

namespace accsynt {

struct LoopBody {
  llvm::BasicBlock *body;
  std::vector<llvm::Value *> loop_indexes;
  llvm::Instruction *insert_point;
};

class IRLoop {
private:
  llvm::Function* func_;
  llvm::BasicBlock* post_loop_;
  Loop const& shape_;
  std::map<long, llvm::Value *> const& extents_;
  std::vector<llvm::Value *> parents_;
  llvm::IRBuilder<> B_;

  void build_sequence();
  void build_nested(long loop_id);

  bool own_bodies_map = false;
  std::map<long, LoopBody> *bodies_;

public:
  IRLoop(llvm::Function* f, Loop const& l, 
         std::map<long, llvm::Value *> const& e,
         llvm::BasicBlock* post,
         std::map<long, LoopBody> *b = nullptr,
         std::vector<llvm::Value *> p = {});

  ~IRLoop()
  {
    if(own_bodies_map && bodies_) {
      delete bodies_;
    }
  }

  std::map<long, LoopBody> const& bodies() const
  {
    return *bodies_;
  }

  llvm::BasicBlock *header;
  llvm::BasicBlock *body;
  llvm::BasicBlock *exit;
};

template <typename R, typename... Args>
class LoopSynth : public Synthesizer<R, Args...> {
public:
  LoopSynth(R r, Args... args) 
    : Synthesizer<R, Args...>(r, args...),
      const_sizes_{}, rt_size_offsets_{}
  {
    index_for_each(this->arg_types_, [&] (auto& ty, auto i) {
      register_arg(ty, i);
    });

    auto ids = std::vector<long>{};
    for(auto pair : const_sizes_) {
      ids.emplace_back(pair.first);
    }
    for(auto pair : rt_size_offsets_) {
      ids.emplace_back(pair.first);
    }

    auto loop_set = Loop::loops(ids.size(), ids.begin(), ids.end());
    std::copy(begin(loop_set), end(loop_set), std::back_inserter(loops_));
  }

  template <typename ArgTy>
  void register_arg(ArgTy ty, int i)
  {
    if constexpr(is_array(ty)) {
      const_sizes_.insert_or_assign(i, ty.array_size());
    }

    if constexpr(is_output(ty)) {
      outputs_.emplace_back(i);
      register_arg(ty.type(), i);
    }

    if constexpr(is_sized_pointer(ty)) {
      rt_size_offsets_.insert_or_assign(i, ty.size_index);
    }
  }

  using Synthesizer<R, Args...>::operator();

  // We can use this synthesizer when at least one (for now, exactly one?) of
  // the parameters is sized (i.e. is a fixed size array)
  // extend to handle sized pointers next
  virtual bool can_synthesize() const override
  {
    return !const_sizes_.empty() || !rt_size_offsets_.empty();
  }

private:
  void construct(llvm::Function *f, llvm::IRBuilder<>& b) const override;
  llvm::Value *construct_return(llvm::Type *rt, llvm::BasicBlock *where, 
                                llvm::IRBuilder<>& b) const;

  std::vector<long> outputs_;
  std::map<long, long> const_sizes_;
  std::map<long, long> rt_size_offsets_;

  mutable std::mutex mut = {};
  mutable std::vector<Loop> loops_;
};

template <typename R, typename... Args>
llvm::Value *
LoopSynth<R, Args...>::construct_return(
    llvm::Type *rt, llvm::BasicBlock *where, 
    llvm::IRBuilder<>& b) const
{
  auto insert = b.saveIP();

  auto ret = [&] () -> llvm::Value* {
    if(rt->isVoidTy()) {
      b.SetInsertPoint(where);
      b.CreateRetVoid();
      return nullptr;
    } else {
      auto loc = b.CreateAlloca(rt);
      b.CreateStore(llvm::ConstantInt::get(rt, 0), loc);

      b.SetInsertPoint(where);
      auto ret_load = b.CreateLoad(loc);
      b.CreateRet(ret_load);

      return loc;
    }
  }();

  b.restoreIP(insert);
  return ret;
}

template <typename R, typename... Args>
void LoopSynth<R, Args...>::construct(llvm::Function *f, llvm::IRBuilder<>& b) const
{
  auto func_meta = SynthMetadata{};
  for(auto [idx, size] : const_sizes_) {
    func_meta.const_size(f->arg_begin() + idx + 1) = size;
  }

  for(auto idx : outputs_) {
    func_meta.output(f->arg_begin() + idx + 1) = true;
  }

  auto post_bb = llvm::BasicBlock::Create(f->getContext(), "post-loop", f);
  func_meta.return_loc = construct_return(f->getReturnType(), post_bb, b);

  std::unique_lock ul{mut};
  auto shape = loops_.at(0);
  ul.unlock();

  auto all_sizes = std::map<long, llvm::Value *>{};
  for(auto [idx, size] : const_sizes_) {
    all_sizes.insert_or_assign(idx, b.getInt64(size));
  }
  for(auto [idx, size_idx] : rt_size_offsets_) {
    all_sizes.insert_or_assign(idx, f->arg_begin() + size_idx + 1);
  }
  auto irl = IRLoop(f, shape, all_sizes, post_bb);

  b.SetInsertPoint(&f->getEntryBlock());
  b.CreateBr(irl.header);

  for(auto [id, body] : irl.bodies()) {
    auto meta = func_meta;
    
    b.SetInsertPoint(body.insert_point);

    auto i = *body.loop_indexes.rbegin();
    meta.live(i) = true;

    auto arg = f->arg_begin() + id + 1;
    // distinguish array vs. ptr
    auto item_ptr = b.CreateGEP(arg, i);
    meta.live(b.CreateLoad(item_ptr)) = true;
    if(meta.output(arg)) {
      meta.output(item_ptr) = true;
    }

    /* for(auto& [arg, size] : meta.const_size) { */
    /*   if(size == const_sizes_.at(id)) { */
    /*     auto item_ptr = b.CreateGEP(arg, {b.getInt64(0), i}); */
    /*     meta.live(b.CreateLoad(item_ptr)) = true; */

    /*     if(meta.output(arg)) { */
    /*       auto output_ptr = b.CreateGEP(arg, {b.getInt64(0), i}); */
    /*       meta.output(output_ptr) = true; */
    /*     } */
    /*   } */
    /* } */

    if(meta.return_loc) {
      meta.live(b.CreateLoad(meta.return_loc)) = true;
    }

    auto gen = BlockGenerator{b, meta};
    gen.populate(20);
    gen.output();
  }

  ul.lock();
  std::rotate(begin(loops_), std::next(begin(loops_)), end(loops_));
  ul.unlock();
}

}
