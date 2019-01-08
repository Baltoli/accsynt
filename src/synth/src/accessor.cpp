#include "accessor.h"

using namespace llvm;

namespace synth {

std::set<Value *> accessor::create_geps(
    Value *index, Value *base, IRBuilder<>& builder) const
{
  auto mapped = map_index(index);
  auto geps = std::set<Value *>{};

  for(auto idx : mapped) {
    geps.insert(builder.CreateGEP(base, idx));
  }

  return geps;
}

// Default implementation that other accessors can override if needed
std::set<Value *> accessor::map_index(Value* index) const
{
  return { index };
}

}
