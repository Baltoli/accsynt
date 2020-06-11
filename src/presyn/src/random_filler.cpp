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

std::vector<llvm::Value*> random_filler::live_values(llvm::CallInst* hole) const
{
  return {};
}

} // namespace presyn
