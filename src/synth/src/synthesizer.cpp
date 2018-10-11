#include "synthesizer.h"

using namespace props;
using namespace llvm;

namespace synth {

synthesizer::synthesizer(property_set ps, Function *fn)
  : properties_(ps), reference_(fn)
{
}

std::string null_synth::name() const
{
  return "Null";
}

}
