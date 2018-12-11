#pragma once

#include "fragment.h"
#include "synthesizer.h"

#include <unordered_set>

namespace synth {

class rule_synth : public synthesizer {
public:
  rule_synth(props::property_set ps, call_wrapper& wrap);

  virtual std::string name() const;

protected:
  virtual llvm::Function *candidate();

private:
  fragment::frag_set fragments_;
  fragment::frag_set::iterator current_fragment_;
};

}
