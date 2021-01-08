#include "optimiser.h"

#include <support/assert.h>

using namespace support;
using namespace llvm;

namespace presyn {

optimiser::optimiser(holes::provider&& hp)
    : provider_(std::move(hp))
{
}

void optimiser::run(Function* target, call_wrapper& wrap)
{
  assertion(
      target->getParent() == &provider_.module(),
      "No cross-module optimisation is supported");
}

} // namespace presyn
