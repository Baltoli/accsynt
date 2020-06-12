#include "random_filler.h"

#include <support/assert.h>
#include <support/llvm_format.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

using namespace llvm;

namespace presyn {

Value* random_filler::fill(CallInst* hole)
{
  auto possible = live_values(hole);
  assertion(!possible.empty(), "No live values for this hole: {}", *hole);

  return nullptr;
}

std::vector<Value*> random_filler::live_values(CallInst* hole) const
{
  auto tree = tree_for(hole);
  auto func = hole->getFunction();

  auto ret = std::vector<Value*> {};

  for (auto& bb : *func) {
    for (auto& inst : bb) {
      if (tree.dominates(&inst, hole)) {
        ret.push_back(&inst);
      }
    }
  }

  return ret;
}

DominatorTree random_filler::tree_for(CallInst* hole) const
{
  auto func = hole->getFunction();
  assertion(func != nullptr, "Hole does not have a function: {}", *hole);

  return DominatorTree(*func);
}

} // namespace presyn
