#pragma once

#include "evaluator.h"
#include "fragment.h"
#include "gp_sampler.h"

#include <props/props.h>
#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>

namespace synth {

class scored_fragment {
public:
  scored_fragment(fragment::frag_ptr f);

  double mean() const;

private:
  size_t samples_;
  double mean_;
};

class hill_synth {
public:
  hill_synth(props::property_set ps, support::call_wrapper& ref);

  llvm::Function* generate();

private:
  std::vector<fragment::frag_ptr> choices_;

  props::property_set properties_;
  support::call_wrapper& reference_;
};

} // namespace synth
