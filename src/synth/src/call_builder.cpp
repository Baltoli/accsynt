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

std::vector<GenericValue> const& call_builder::args() const
{
  return args_;
}

void call_builder::add(int i)
{
  auto gv = GenericValue{};
  gv.IntVal = APInt(32, i, true);
  args_.push_back(gv);
}

void call_builder::add(float f)
{
  auto gv = GenericValue{};
  gv.FloatVal = f;
  args_.push_back(gv);
}

void call_builder::add(void *ptr)
{
  auto gv = GenericValue{ptr};
  args_.push_back(gv);
}

}
