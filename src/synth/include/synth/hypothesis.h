#pragma once

#include <synth/types.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <array>
#include <limits>
#include <memory>
#include <tuple>
#include <typeinfo>

/**
 * This class will act as a wrapper around an LLVM function that acts as a
 * hypothesis for what a device computes. Implementation questions that I need
 * to think about:
 *  - Should a hypothesis be responsible for updating itself or should a learner
 *    class do that somehow? For now, let's have the hypothesis only manage a
 *    function and have it be callable.
 *  - Could spinning up LLVM modules and functions for every single hypothesis
 *    we create be too expensive? Comes back to the idea that we might want a
 *    lightweight / verifiable encoding at first that can then be compiled into
 *    LLVM if we need.
 */
template<class R, class... Args>
class Hypothesis {
public:
  Hypothesis(std::string name="") :
    C{}, 
    mod_(std::make_unique<llvm::Module>(name, C))
  {
    llvm::IntegerType* ret_ty = get_llvm_int<R>(C);

    auto array = std::array<llvm::Type*, sizeof...(Args)>{ {get_llvm_int<Args>(C)...} };
    auto fun_ty = llvm::FunctionType::get(ret_ty, array, false);

    func_ = llvm::Function::Create(
      fun_ty, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "", mod_.get());
    auto bb = llvm::BasicBlock::Create(C, "", func_);

    auto ret = llvm::ConstantInt::get(ret_ty, 10);
    llvm::IRBuilder<> B(&func_->getEntryBlock());
    B.CreateRet(ret);
  }

  R operator()(Args... args);

//private:
  llvm::LLVMContext C;
  std::unique_ptr<llvm::Module> mod_;
  llvm::Function* func_;
};

template<class R, class... Args>
R Hypothesis<R, Args...>::operator()(Args... args)
{
  llvm::EngineBuilder eb(std::move(mod_));
  auto e = eb.create();
  llvm::GenericValue g;
  g.IntVal = 0;
  return R(e->runFunction(func_, {g, g}).IntVal.getLimitedValue(std::numeric_limits<R>::max()));
}
