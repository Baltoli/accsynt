#include "optimiser.h"

#include <support/assert.h>

using namespace support;
using namespace llvm;

namespace presyn {

optimiser::optimiser(Function* f, std::set<Instruction*> hs)
    : target_(f)
    , holes_(hs)
{
  for (auto hole : hs) {
    assertion(
        hole->getFunction() == target_,
        "Instruction outside target function: {}", *hole);
  }
}

void optimiser::run(call_wrapper& wrap) { }

} // namespace presyn
