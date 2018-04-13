#pragma once

#include <llvm/IR/IRBuilder.h>

#include <dist/synth.h>

#include <memory>

namespace accsynt {

template <typename Builder>
class LoopBuilder {
public:
  LoopBuilder(llvm::Function *f, Builder& b) :
    func_(f), b_(b), 
    entry_block_(&f->getEntryBlock()),
    loop_block_(llvm::BasicBlock::Create(func_->getContext(), "body", func_)),
    exit_block_(llvm::BasicBlock::Create(func_->getContext(), "exit", func_)),
    return_loc_(b_.CreateAlloca(f->getReturnType()))
  {}

  void construct(size_t length);

private:
  void construct_body(llvm::Value *iter);

  llvm::Function *func_;
  Builder &b_;

  llvm::BasicBlock *entry_block_;
  llvm::BasicBlock *loop_block_;
  llvm::BasicBlock *exit_block_;

  llvm::Value *return_loc_;
};

template <typename Builder>
void LoopBuilder<Builder>::construct_body(llvm::Value *iter)
{
}

template <typename Builder>
void LoopBuilder<Builder>::construct(size_t length)
{
  auto rt = func_->getReturnType();
  auto iter_t = llvm::IntegerType::get(func_->getContext(), 64);

  b_.CreateStore(llvm::ConstantInt::get(rt, 0), return_loc_);
  b_.CreateBr(loop_block_);

  b_.SetInsertPoint(loop_block_);
  auto iter = b_.CreatePHI(iter_t, 2);
  iter->addIncoming(b_.getInt64(0), entry_block_);
  auto add = b_.CreateAdd(iter, b_.getInt64(1));
  iter->addIncoming(add, loop_block_);

  construct_body(iter);

  auto end_test = b_.CreateICmpEQ(add, b_.getInt64(length));
  b_.CreateCondBr(end_test, exit_block_, loop_block_);
  b_.SetInsertPoint(exit_block_);

  auto ret_load = b_.CreateLoad(return_loc_);
  b_.CreateRet(ret_load);
}

template <typename R, typename... Args>
class Loop : public Synthesizer<R, Args...> {
public:
  Loop(R r, Args... args) 
    : Synthesizer<R, Args...>(r, args...) 
  {
    index_for_each(this->arg_types_, [this] (auto& ty, auto i) {
      if constexpr(is_array(ty)) {
        sizes_.insert_or_assign(i, ty.array_size());
      }
    });
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

  std::map<size_t, size_t> sizes_ = {};
};

template <typename R, typename... Args>
void Loop<R, Args...>::construct(llvm::Function *f, llvm::IRBuilder<>& b) const
{
  auto loop_b = LoopBuilder(f, b);
  loop_b.construct(begin(sizes_)->second);
}

}
