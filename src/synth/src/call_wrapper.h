#pragma once

#include <support/dynamic_library.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <memory>

namespace synth {

class call_wrapper {
public:
  call_wrapper(llvm::Module const& mod, std::string const& name);
  call_wrapper(llvm::Module const& mod, std::string const& name, support::dynamic_library dl);

private:
  call_wrapper(llvm::Module const& mod);

  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

}
