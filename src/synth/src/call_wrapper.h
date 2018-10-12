#pragma once

#include "call_builder.h"

#include <props/props.h>
#include <support/dynamic_library.h>
#include <support/thread_context.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <memory>

namespace synth {

class call_wrapper {
public:
  call_wrapper(props::signature sig, llvm::Module const& mod, std::string const& name);
  call_wrapper(props::signature sig, llvm::Module const& mod, std::string const& name, support::dynamic_library const& dl);

  call_builder get_builder() const;
  void call(call_builder& builder);

private:
  size_t marshalled_size(llvm::Type const* type) const;

  template <typename Builder>
  llvm::Value *make_vector(Builder &B, size_t size) const;

  template <typename Builder>
  llvm::Value *make_return(Builder &B, llvm::Value *ret = nullptr) const;

  llvm::Function *build_wrapper_function(llvm::Module& mod, llvm::Function *fn) const;

  props::signature signature_;
  llvm::Function *impl_;
  llvm::Function *wrapper_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename Builder>
llvm::Value *call_wrapper::make_vector(Builder &B, size_t size) const
{
  auto vec_ty = llvm::VectorType::get(B.getInt8Ty(), size);
  return llvm::Constant::getNullValue(vec_ty);
}

template <typename Builder>
llvm::Value *call_wrapper::make_return(Builder &B, llvm::Value *ret) const
{
  if(!ret) {
    ret = B.getInt64(0);
  }

  auto* to_extend = ret;
  if(ret->getType()->isFloatTy()) {
    to_extend = B.CreateBitCast(ret, B.getInt32Ty());
  }

  auto* return_val = B.CreateZExt(to_extend, B.getInt64Ty());
  return B.CreateRet(return_val);
}

}
