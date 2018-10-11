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

  template <typename T>
  void add_argument(T arg);

  void call();
  void call(call_builder builder);

private:
  size_t marshalled_size(llvm::Type const* type) const;

  template <typename Builder>
  llvm::Value *make_vector(Builder &B, size_t size) const;

  llvm::Function *build_wrapper_function(llvm::Module& mod, llvm::Function *fn) const;

  call_builder builder_;
  llvm::Function *impl_;
  llvm::Function *wrapper_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename Builder>
llvm::Value *call_wrapper::make_vector(Builder &B, size_t size) const
{
  auto byte_ty = llvm::IntegerType::get(support::thread_context::get(), 8);
  auto vec_ty = llvm::VectorType::get(byte_ty, size);
  return llvm::Constant::getNullValue(vec_ty);
}

template <typename T>
void call_wrapper::add_argument(T arg)
{
  builder_.add(arg);
}

}
