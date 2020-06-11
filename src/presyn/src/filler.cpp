#include "filler.h"

#include <support/assert.h>

#include <llvm/IR/Constant.h>

using namespace llvm;

namespace presyn {

void filler::set_candidate(candidate& cand)
{
  assertion(
      candidate_ == nullptr,
      "Trying to reset candidate - precondition violated");
  candidate_ = &cand;
}

candidate& filler::get_candidate()
{
  assertion(
      candidate_ != nullptr, "Candidate not set - precondition violated!");
  return *candidate_;
}

Value* zero_filler::fill(CallInst* hole)
{
  return Constant::getNullValue(hole->getType());
}

} // namespace presyn
