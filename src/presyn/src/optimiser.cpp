#include "optimiser.h"

#include <support/assert.h>

using namespace support;
using namespace llvm;

namespace presyn {

optimiser::optimiser(holes::provider&& hp)
    : provider_(std::move(hp))
    , constants_ {}
{
}

void optimiser::run(Function* target, call_wrapper& wrap)
{
  assertion(
      target->getParent() == &provider_.module(),
      "No cross-module optimisation is supported");

  auto initial_holes = provider_.holes();

  for (auto hole : initial_holes) {
    if (hole->getType() == provider_.hole_type()) {
      auto cst = get_constant(0, IntegerType::get(provider_.ctx(), 64));
      provider_.rauw_nt(hole, cst);
    }
  }

  provider_.reset();
}

} // namespace presyn
