#pragma once

#include "evaluator.h"

namespace synth {

class gp_sampler {
public:
  gp_sampler(evaluator const&);

private:
  evaluator const& eval_;
};

} // namespace synth
