#include "gp_sampler.h"

#include <llvm/Support/raw_ostream.h>

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

gp_sampler::gp_sampler(evaluator const& e)
    : eval_(e)
{
}

void gp_sampler::sample(property_set ps, compile_metadata const& meta) const
{
  auto wrap = call_wrapper(
      ps.type_signature, *meta.function->getParent(), meta.function->getName());

  errs() << eval_(wrap).score << '\n';
}

} // namespace synth
