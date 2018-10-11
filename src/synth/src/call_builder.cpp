#include "call_builder.h"

#include <llvm/ADT/APInt.h>

using namespace llvm;

namespace synth {

call_builder::call_builder(props::signature sig) :
  signature_(sig)
{
}

props::signature const& call_builder::signature() const
{
  return signature_;
}

uint8_t* call_builder::args()
{
  return args_.data();
}

}
