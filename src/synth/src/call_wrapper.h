#pragma once

#include "call_builder.h"

#include <props/props.h>
#include <support/dynamic_library.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
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

private:
  call_builder builder_;
  llvm::Function *function_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename T>
void call_wrapper::add_argument(T arg)
{
  builder_.add(arg);
}

}
