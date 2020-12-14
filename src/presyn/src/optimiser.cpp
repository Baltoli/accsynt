#include "optimiser.h"

#include <support/assert.h>

using namespace support;
using namespace llvm;

namespace presyn {

optimiser::optimiser(Function* f, holes::provider&& hp)
    : target_(f)
    , provider_(std::move(hp))
{
  assertion(
      target_->getParent() == &provider_.module(),
      "No cross-module optimisation is supported");
}

void optimiser::run(call_wrapper& wrap) { }

} // namespace presyn
