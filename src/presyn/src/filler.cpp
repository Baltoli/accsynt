#include "filler.h"
#include "candidate.h"

#include <support/assert.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>

using namespace llvm;

namespace presyn {

void filler::set_candidate(candidate& cand)
{
  assertion(
      candidate_ == nullptr,
      "Trying to reset candidate - precondition violated");
  candidate_ = &cand;
}

candidate& filler::get_candidate() const
{
  assertion(
      candidate_ != nullptr, "Candidate not set - precondition violated!");
  return *candidate_;
}

bool filler::has_unknown_type(llvm::Value* val) const
{
  return val->getType() == get_candidate().hole_type();
}

Value* zero_filler::fill(CallInst* hole)
{
  auto ty = hole->getType();

  if (has_unknown_type(hole)) {
    // If we see something with unknown type then just say it's an int64
    auto& ctx = get_candidate().module().getContext();
    ty = IntegerType::get(ctx, 64);
  }

  return Constant::getNullValue(ty);
}

} // namespace presyn
