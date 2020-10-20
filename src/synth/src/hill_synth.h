#pragma once

#include "fragment.h"
#include "synthesizer.h"

#include <props/props.h>
#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

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
  static constexpr auto num_examples = 1000;

public:
  hill_synth(props::property_set ps, support::call_wrapper& ref);

  generate_result generate();

private:
  llvm::Module mod_;

  std::vector<fragment::frag_ptr> choices_;

  props::property_set properties_;
  /* support::call_wrapper& reference_; */
};

} // namespace synth
