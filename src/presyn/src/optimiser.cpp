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

  for (auto hole : provider_.holes()) {
    if (hole->getType() == provider_.hole_type()) {
      unimplemented();
    }
  }

  provider_.reset();

  unimplemented();
}

} // namespace presyn
