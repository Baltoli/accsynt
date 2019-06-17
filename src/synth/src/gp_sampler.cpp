#include "gp_sampler.h"

namespace synth {

gp_sampler::gp_sampler(llvm::Function* f, evaluator const& e)
    : skeleton_(f)
    , eval_(e)
{
}

} // namespace synth
