/**
 * \file function_callable.h
 */

#pragma once

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
  FunctionCallable(llvm::Function *f);

  /**
   * \brief Call the LLVM function with a variadic set of arguments.
   *
   * The compile-time size of \p args must be the same as the argument count of
   * the LLVM function associated with this callable.
   */
  template<class... Args>
  R operator()(Args... args);
private:
  llvm::ValueToValueMapTy v;
  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;
  llvm::Function *func_;
};

template<class R>
FunctionCallable<R>::FunctionCallable(llvm::Function *f)
{
  if(f->getParent()) {
    module_ = llvm::CloneModule(f->getParent(), v);
    func_ = llvm::cast<llvm::Function>(v[f]);
  } else {
    module_ = std::make_unique<llvm::Module>("", C_);
    func_ = util::copy_function(f, module_.get());
  }
}

template<class R>
template<class... Args>
R FunctionCallable<R>::operator()(Args... args) 
{
  assert(func_->arg_size() == sizeof...(args) && "Argument count mismatch");
  auto engine = util::create_engine(module_.get());

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { util::make_generic(args)... }
  };

  auto ret = engine->runFunction(func_, func_args);
  return R(ret.IntVal.getLimitedValue(std::numeric_limits<R>::max()));
}
