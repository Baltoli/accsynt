#include "hill_synth.h"

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

hill_synth::hill_synth(property_set ps, call_wrapper& ref)
    : properties_(ps)
    , reference_(ref)
{
}

Function* hill_synth::generate() { return nullptr; }

} // namespace synth
