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

bool filler::has_unknown_type(Value* val) const
{
  return val->getType() == get_candidate().hole_type();
}

bool filler::is_hole(Value* val) const
{
  if (has_unknown_type(val)) {
    return true;
  }

  if (auto call = dyn_cast<CallInst>(val)) {
    return call->getCalledFunction()->isDeclaration();
  }

  return false;
}

Value* filler::copy_value(Value* val) const
{
  using namespace fmt::literals;

  if (auto inst = dyn_cast<Instruction>(val)) {
    auto& cand = get_candidate();
    auto conv = cand.converter(inst->getType(), inst->getType());

    auto name
        = "{}copy"_format(inst->hasName() ? inst->getName().str() + "." : "");

    auto call = CallInst::Create(conv, {inst}, name, inst);
    call->moveAfter(inst);
    return call;
  } else {
    // TODO: think harder about what needs copied through an ID function - is it
    // just instructions, or are there other things that need the same?
    return val;
  }
}

CallInst* filler::select_type(CallInst* call, Type* type)
{
  auto& cand = get_candidate();
  auto new_call = cand.update_type(call, type);
  cand.safe_rauw(call, new_call);
  return new_call;
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
