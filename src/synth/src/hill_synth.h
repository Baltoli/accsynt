#pragma once

#include "fragment.h"

#include <props/props.h>
#include <support/call_wrapper.h>

#include <llvm/IR/Function.h>

namespace synth {

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
