/**
 * \file function_callable.h
 */

#pragma once

#include <dist/contexts.h>
#include <dist/utils.h>

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <memory>
#include <vector>

namespace llvm {
  class Function;
  class Module;
}

/**
 * \brief Wraps an LLVM function in a callable interface.
 *
 * This class creates a copy of the function it is constructed with, and allows
 * it to be called with native values as arguments. The return type of the
 * function must be known in advance to construct an instance of this class.
 */
template<class R>
class FunctionCallable {
public:
  /**
   * \brief Construct a callable wrapper by copying \p f.
   */
  FunctionCallable(llvm::Module *m, llvm::StringRef name);

  /**
   * \brief Call the LLVM function with a variadic set of arguments.
   *
   * The compile-time size of \p args must be the same as the argument count of
   * the LLVM function associated with this callable.
   */
  template<class... Args>
  R operator()(Args... args);

private:
  std::unique_ptr<llvm::Module> module_;
  llvm::Function *func_;
  llvm::ExecutionEngine *engine_;
};

template<class R>
FunctionCallable<R>::FunctionCallable(llvm::Module *m, llvm::StringRef name) :
  module_{util::copy_module_to(ThreadContext::get(), m)},
  func_{module_->getFunction(name)}
{
  auto eb = llvm::EngineBuilder{std::move(module_)};
  engine_ = eb.create();
}

template<class R>
template<class... Args>
R FunctionCallable<R>::operator()(Args... args) 
{
  assert(func_->arg_size() == sizeof...(args) && "Argument count mismatch");

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { util::make_generic(args)... }
  };

  auto ret = engine_->runFunction(func_, func_args);
  
  // TODO: this needs to be changed
  return R(ret.IntVal.getLimitedValue(std::numeric_limits<R>::max()));
}
