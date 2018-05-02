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

    coalesced_ids_ = ids_to_coalesce();

    auto loop_set = Loop::loops(coalesced_ids_.size());
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

  auto next_shape() const;
  SynthMetadata initial_metadata(llvm::Function *) const;
  std::vector<std::set<long>> ids_to_coalesce() const;
  std::map<long, llvm::Value *> runtime_sizes(llvm::Function *) const;
  llvm::Value *create_valid_gep(llvm::IRBuilder<> b, llvm::Value *data, llvm::Value *idx) const;

  std::vector<long> outputs_;
  std::map<long, long> const_sizes_;
  std::map<long, long> rt_size_offsets_;
  std::vector<std::set<long>> coalesced_ids_;

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
  auto func_meta = initial_metadata(f);

  auto post_bb = llvm::BasicBlock::Create(f->getContext(), "post-loop", f);
  func_meta.return_loc = construct_return(f->getReturnType(), post_bb, b);

  auto all_sizes = runtime_sizes(f);

  auto irl = IRLoop(f, next_shape(), all_sizes, post_bb);
  b.SetInsertPoint(&f->getEntryBlock());
  b.CreateBr(irl.header);

  for(auto [loop_id, body] : irl.bodies()) {
    auto meta = func_meta;
    
    b.SetInsertPoint(body.insert_point);

    auto i = *body.loop_indexes.rbegin();
    meta.live(i) = true;

    for(auto id : coalesced_ids_.at(loop_id)) {
      auto arg = f->arg_begin() + id + 1;
      auto item_ptr = create_valid_gep(b, arg, i);
      meta.live(b.CreateLoad(item_ptr)) = true;
      if(meta.output(arg)) {
        meta.output(item_ptr) = true;
      }
    }

    if(meta.return_loc) {
      meta.live(b.CreateLoad(meta.return_loc)) = true;
    }

    auto gen = BlockGenerator{b, meta};
    gen.populate(20);
    gen.output();
  }
}

template <typename R, typename... Args>
auto LoopSynth<R, Args...>::next_shape() const
{
  std::unique_lock ul{mut};
  auto shape = loops_.at(0);
  std::rotate(begin(loops_), std::next(begin(loops_)), end(loops_));
  return shape;
}

template <typename R, typename... Args>
SynthMetadata LoopSynth<R, Args...>::initial_metadata(llvm::Function *f) const
{
  auto meta = SynthMetadata{};

  for(auto [idx, size] : const_sizes_) {
    meta.const_size(f->arg_begin() + idx + 1) = size;
  }

  for(auto idx : outputs_) {
    meta.output(f->arg_begin() + idx + 1) = true;
  }

  return meta;
}

template <typename R, typename... Args>
std::vector<std::set<long>> LoopSynth<R, Args...>::ids_to_coalesce() const
{
  auto ret = std::vector<std::set<long>>{};

  auto insert_equivs = [&] (auto& container) {
    for(auto pair : container) {
      auto key = pair.second;
      auto equiv = std::set<long>{};
      for(auto [other_idx, other_key] : container) {
        if(key == other_key) {
          equiv.insert(other_idx);
        }
      }
      ret.push_back(equiv);
    }
  };

  insert_equivs(const_sizes_);
  insert_equivs(rt_size_offsets_);

  auto last = std::unique(ret.begin(), ret.end());
  ret.erase(last, ret.end());

  return ret;
}

template <typename R, typename... Args>
std::map<long, llvm::Value *> LoopSynth<R, Args...>::runtime_sizes(llvm::Function *f) const
{
  auto ret = std::map<long, llvm::Value *>{};

  auto i = 0l;
  for(auto const& group : coalesced_ids_) {
    auto rep_id = *group.begin();
    
    if(auto ct_it = const_sizes_.find(rep_id);
       ct_it != const_sizes_.end()) {
      auto i64_ty = llvm::IntegerType::get(f->getContext(), 64);
      auto size = llvm::ConstantInt::get(i64_ty, ct_it->second);
      ret.insert({i++, size});
    }

    if(auto rt_it = rt_size_offsets_.find(rep_id);
       rt_it != rt_size_offsets_.end()) {
      ret.insert({i++, f->arg_begin() + rt_it->second + 1});
    }
  }

  return ret;
}

template <typename R, typename... Args>
llvm::Value *LoopSynth<R, Args...>::create_valid_gep(
  llvm::IRBuilder<> b, llvm::Value *data, llvm::Value *idx) const
{
  auto ptr_ty = llvm::cast<llvm::PointerType>(data->getType());
  auto el_ty = ptr_ty->getElementType();
  if(auto at = llvm::dyn_cast<llvm::ArrayType>(el_ty)) {
    return b.CreateGEP(data, {b.getInt64(0), idx});
  } else {
    return b.CreateGEP(data, idx);
  }
}

}
