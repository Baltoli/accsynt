#include "dataflow_synth.h"

using namespace llvm;

namespace synth {

dataflow_synth::dataflow_synth(Function *f) :
  function_(f)
{
}

void dataflow_synth::seed(Instruction *instr)
{
}

void dataflow_synth::create_dataflow()
{
}

}
