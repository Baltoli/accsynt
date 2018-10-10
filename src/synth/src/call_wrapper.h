#pragma once

#include <props/props.h>
#include <support/dynamic_library.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <memory>

namespace synth {

class call_wrapper {
public:
  call_wrapper(props::signature sig, llvm::Module const& mod, std::string const& name);
  call_wrapper(props::signature sig, llvm::Module const& mod, std::string const& name, support::dynamic_library const& dl);

private:
  call_wrapper(props::signature sig, llvm::Module const& mod);

  props::signature signature_;
  llvm::Function *function_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

}
