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
  /* Linear(R r, Args... args) : Synthesizer<R, Args...>(r, args...) {} */
  using Synthesizer<R, Args...>::Synthesizer;
  using Synthesizer<R, Args...>::operator();

private:
  void clear_functions(llvm::Module& module);

  template <typename Builder>
  void populate_instructions(Builder&& b, ValueSampler& sampler, 
                             llvm::Function *fn, size_t n) const;

  template <typename Builder>
  llvm::Value *create_return(Builder&& b, ValueSampler& sampler,
                             llvm::Function *fn) const;

  template <typename Builder>
  void create_oob_returns(Builder&& b, ValueSampler& sampler,
                          llvm::Function *fn) const;

  std::unique_ptr<llvm::Module> generate_candidate(bool&) override;
};

template <typename R, typename... Args>
Linear(R, Args...) -> Linear<R, Args...>;

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

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::generate_candidate(bool& done)
{
  auto mod = std::make_unique<llvm::Module>("linear-candidate", ThreadContext::get());
  auto B = llvm::IRBuilder<>{mod->getContext()};

  while(!done) {
    clear_functions(*mod);

    auto sampler = ValueSampler{};
    auto& meta = sampler.metadata();

    auto fn = llvm::Function::Create(this->llvm_function_type(), llvm::GlobalValue::ExternalLinkage, 
                                     "cand", mod.get());
    auto bb = llvm::BasicBlock::Create(fn->getContext(), "", fn);
    B.SetInsertPoint(bb);

    index_for_each(this->arg_types_, [&](auto&& at, auto idx) {
      if constexpr(is_index(at)) {
        meta.index_bound(fn->arg_begin() + idx + 1) = at.bound();
      }
      
      if constexpr(is_array(at)) {
        meta.size(fn->arg_begin() + idx + 1) =  at.array_size();
      }
    });

    populate_instructions(B, sampler, fn, 50);
    auto ret = create_return(B, sampler, fn);
    if(!ret) {
      return nullptr;
    }

    create_oob_returns(B, sampler, fn);

    if(this->satisfies_examples(fn)) {
      done = true;
      return std::move(mod);
    }
  }

  return nullptr;
}

template <typename R, typename... Args>
void Linear<R, Args...>::clear_functions(llvm::Module& module)
{
  auto to_clear = std::forward_list<llvm::Function *>{};

  for(auto& f : module) {
    if(f.getName() == "cand") {
      to_clear.push_front(&f);
    }
  }

  for(auto* f : to_clear) {
    f->eraseFromParent();
  }
}

}
