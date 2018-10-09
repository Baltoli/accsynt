#pragma once

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <memory>

namespace synth {

class call_wrapper {
public:
  call_wrapper(llvm::Module& mod, std::string const& name);

private:
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

}
