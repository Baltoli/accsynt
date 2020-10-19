#include "filler.h"
#include "candidate.h"

#include <support/assert.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>

#include <fmt/format.h>

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

Value* filler::copy_value(llvm::Value* val) const
{
  using namespace fmt::literals;

  if (auto inst = dyn_cast<Instruction>(val)) {
    auto& cand = get_candidate();
    auto conv = cand.converter(inst->getType(), inst->getType());

    auto name
        = "{}copy"_format(inst->hasName() ? inst->getName().str() + "." : "");

    return CallInst::Create(conv, {inst}, name, inst);
  } else {
    // TODO: think harder about what needs copied through an ID function - is it
    // just instructions, or are there other things that need the same?
    return val;
  }
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
