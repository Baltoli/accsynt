#pragma once

#include "compile_metadata.h"
#include "evaluator.h"

#include <props/props.h>

#include <llvm/IR/Function.h>

namespace synth {

class gp_sampler {
public:
  gp_sampler(evaluator const&);

  void sample(props::property_set, compile_metadata const&) const;

private:
  evaluator const& eval_;
};

} // namespace synth
