#include "accessor.h"

using namespace llvm;

namespace synth {

std::set<Value *> accessor::create_geps(
    std::set<Value *> indices,
    Value *base, IRBuilder<>& builder) const
{
  auto mapped = map_indices(indices);
  auto geps = std::set<Value *>{};

  for(auto idx : mapped) {
    geps.insert(builder.CreateGEP(base, idx));
  }

  return geps;
}

// Default implementation that other accessors can override if needed
std::set<Value *> accessor::map_indices(std::set<Value *> indices) const
{
  return indices;
}

}
