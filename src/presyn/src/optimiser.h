#pragma once

#include <holes/holes.h>

#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <set>

namespace presyn {

class optimiser {
public:
  optimiser(llvm::Function*, holes::provider&&);

  void run(support::call_wrapper& wrap);

private:
  llvm::Function* target_;
  holes::provider provider_;
};

} // namespace presyn
