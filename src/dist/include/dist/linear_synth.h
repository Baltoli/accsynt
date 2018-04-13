#pragma once

#include <dist/function_callable.h>
#include <dist/synth_op.h>
#include <dist/synth.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <forward_list>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <type_traits>

namespace llvm {
  class Function;
  class Module;
}

namespace accsynt {

template <typename R, typename... Args>
class Linear : public Synthesizer<R, Args...> {
public:
  Linear(R r, Args... args) : Synthesizer<R, Args...>(r, args...) {}
  using Synthesizer<R, Args...>::operator();

  // This synthesizer can try to synthesize anything, it just might not be the
  // fastest way of doing it.
  bool can_synthesize() const override
  {
    return true;
  }

private:
  template <typename Builder>
  void populate_instructions(Builder&& b, ValueSampler& sampler, 
                             llvm::Function *fn, size_t n) const;

  template <typename Builder>
  llvm::Value *create_return(Builder&& b, ValueSampler& sampler,
                             llvm::Function *fn) const;

  template <typename Builder>
  void create_oob_returns(Builder&& b, ValueSampler& sampler,
                          llvm::Function *fn) const;

  virtual void construct(llvm::Function *f, llvm::IRBuilder<>& b) const override;
};

template <typename R, typename... Args>
void Linear<R, Args...>::construct(llvm::Function *fn, llvm::IRBuilder<>& b) const
{
  auto sampler = ValueSampler{};
  auto& meta = sampler.metadata();

  index_for_each(this->arg_types_, [&](auto&& at, auto idx) {
    if constexpr(is_index(at)) {
      meta.index_bound(fn->arg_begin() + idx + 1) = at.bound();
    }
    
    if constexpr(is_array(at)) {
      meta.size(fn->arg_begin() + idx + 1) =  at.array_size();
    }
  });

  populate_instructions(b, sampler, fn, 50);
  create_return(b, sampler, fn);
  create_oob_returns(b, sampler, fn);
}

template <typename R, typename... Args>
template <typename Builder>
void Linear<R, Args...>::populate_instructions(Builder&& B,
                                               ValueSampler& sampler, 
                                               llvm::Function *fn, 
                                               size_t n) const
{
  auto& meta = sampler.metadata();

  for(auto arg = std::next(fn->arg_begin()); arg != fn->arg_end(); ++arg) {
    meta.live(arg) = true;
  }

  for(auto i = 0u; i < n; ++i) {
    auto live = meta.live;
    auto v1 = uniform_sample(std::begin(live), std::end(live));
    auto v2 = uniform_sample(std::begin(live), std::end(live));
    
    if(auto next = sampler(B, {v1, v2})) {
      meta.live(next) = true;
    }
  }
}

template <typename R, typename... Args>
template <typename Builder>
llvm::Value *Linear<R, Args...>::create_return(Builder&& B, 
                                               ValueSampler& sampler,
                                               llvm::Function *fn) const
{
  auto& meta = sampler.metadata();
  auto fn_ty = fn->getFunctionType();

  auto possibles = std::vector<llvm::Value*>{};
  std::copy_if(std::begin(meta.live), std::end(meta.live), 
               std::back_inserter(possibles), 
    [&] (auto inst) {
      return inst->getType() == fn_ty->getReturnType();
    }
  );

  if(possibles.empty()) {
    return nullptr;
  }

  return B.CreateRet(uniform_sample(possibles));
}

template <typename R, typename... Args>
template <typename Builder>
void Linear<R, Args...>::create_oob_returns(Builder&& b, 
                                            ValueSampler& sampler, 
                                            llvm::Function *fn) const
{
  auto& meta = sampler.metadata();

  auto ret_ty = fn->getFunctionType()->getReturnType();
  auto zero = llvm::ConstantInt::get(ret_ty, 0);
  auto one = llvm::ConstantInt::get(ret_ty, 1);

  auto oob_bb = llvm::BasicBlock::Create(fn->getContext(), "oob-exit", fn);
  b.SetInsertPoint(oob_bb);
  b.CreateStore(one, fn->arg_begin()); 
  b.CreateRet(zero);

  for(auto oob_flag_val : meta.oob) {
    auto oob_flag = llvm::cast<llvm::Instruction>(oob_flag_val);

    auto old_bb = oob_flag->getParent();
    auto new_bb = old_bb->splitBasicBlock(oob_flag);

    auto old_term = old_bb->getTerminator();

    b.SetInsertPoint(old_term);
    auto br = b.CreateCondBr(oob_flag_val, oob_bb, new_bb);
    oob_flag->moveBefore(br);
    old_term->eraseFromParent();
  }
}

}
