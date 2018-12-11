#pragma once

#include "synthesizer.h"

namespace synth {

class rule_synth : public synthesizer {
public:
  rule_synth(props::property_set ps, call_wrapper& wrap);

  virtual std::string name() const;

protected:
  virtual llvm::Function *candidate();
};

}
