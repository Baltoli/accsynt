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

template<class R>
class FunctionCallable {
public:
  FunctionCallable(llvm::Function *f);

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
    func_ = function_copy(f, module_.get());
  }
}

template<class R>
template<class... Args>
R FunctionCallable<R>::operator()(Args... args) 
{
  assert(func_->arg_size() == sizeof...(args) && "Argument count mismatch");
  auto engine = create_engine(module_.get());

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { make_generic(args)... }
  };

  auto ret = engine->runFunction(func_, func_args);
  return R(ret.IntVal.getLimitedValue(std::numeric_limits<R>::max()));
}
