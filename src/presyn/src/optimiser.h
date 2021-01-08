#pragma once

#include <holes/holes.h>

#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <unordered_map>

namespace presyn {

class optimiser {
public:
  optimiser(holes::provider&&);

  void run(llvm::Function*, support::call_wrapper& wrap);

private:
  holes::provider provider_;
};

} // namespace presyn
