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
  std::map<long, long> const& extents_;
  std::vector<llvm::Value *> parents_;
  llvm::IRBuilder<> B_;

  void build_sequence();
  void build_nested(long loop_id);

  bool own_bodies_map = false;
  std::map<long, LoopBody> *bodies_;

public:
  IRLoop(llvm::Function* f, Loop const& l, 
         std::map<long, long> const& e,
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
    : Synthesizer<R, Args...>(r, args...), sizes_{}
  {
    index_for_each(this->arg_types_, [this] (auto& ty, auto i) {
      if constexpr(is_array(ty)) {
        sizes_.insert_or_assign(i, ty.array_size());
      }
    });

    auto ids = std::vector<long>{};
    for(auto pair : sizes_) {
      ids.emplace_back(pair.first);
    }

    auto loop_set = Loop::loops(sizes_.size(), ids.begin(), ids.end());
    std::copy(begin(loop_set), end(loop_set), std::back_inserter(loops_));
  }

  using Synthesizer<R, Args...>::operator();

  // We can use this synthesizer when at least one (for now, exactly one?) of
  // the parameters is sized (i.e. is a fixed size array)
  // extend to handle sized pointers next
  virtual bool can_synthesize() const override
  {
    return !sizes_.empty();
  }

private:
  void construct(llvm::Function *f, llvm::IRBuilder<>& b) const override;

  std::map<long, long> sizes_;

  mutable std::mutex mut = {};
  mutable std::vector<Loop> loops_;
};

template <typename R, typename... Args>
void LoopSynth<R, Args...>::construct(llvm::Function *f, llvm::IRBuilder<>& b) const
{
  auto entry = &f->getEntryBlock();
  auto rt = f->getReturnType();
  auto return_loc_ = b.CreateAlloca(rt);
  b.CreateStore(llvm::ConstantInt::get(rt, 0), return_loc_);

  auto post_bb = llvm::BasicBlock::Create(f->getContext(), "post-loop", f);
  b.SetInsertPoint(post_bb);
  auto ret_load = b.CreateLoad(return_loc_);
  b.CreateRet(ret_load);

  std::unique_lock ul{mut};
  auto shape = loops_.at(0);
  ul.unlock();

  auto irl = IRLoop(f, shape, sizes_, post_bb);

  b.SetInsertPoint(entry);
  b.CreateBr(irl.header);

  for(auto [id, body] : irl.bodies()) {
    b.SetInsertPoint(body.insert_point);

    auto datas = std::vector<llvm::Value *>{};
    for(auto pair : sizes_) {
      if(pair.second == sizes_.at(id)) {
        datas.push_back(f->arg_begin() + pair.first + 1);
      }
    }

    auto i = *body.loop_indexes.rbegin();

    auto meta = SynthMetadata{};

    for(auto data : datas) {
      auto item_ptr = b.CreateGEP(data, {b.getInt64(0), i});
      meta.live(b.CreateLoad(item_ptr)) = true;
    }

    meta.live(i) = true;
    meta.live(b.CreateLoad(return_loc_)) = true;

    meta.output(return_loc_) = true;

    auto gen = BlockGenerator{b, meta};
    gen.populate(20);
    gen.output();
  }

  ul.lock();
  std::rotate(begin(loops_), std::next(begin(loops_)), end(loops_));
  ul.unlock();
}

}
