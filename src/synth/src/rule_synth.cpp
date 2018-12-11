#include "rule_synth.h"

namespace synth {

rule_synth::rule_synth(props::property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref)
{
}

std::string rule_synth::name() const
{
  return "rule_synth";
}

llvm::Function *rule_synth::candidate()
{
  return nullptr;
}

}
