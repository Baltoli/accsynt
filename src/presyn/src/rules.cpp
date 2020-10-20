#include "rules.h"

#include <llvm/IR/InstrTypes.h>

using namespace llvm;

namespace presyn::rules {

void do_nothing::match(
    rule_filler& fill, CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
}

void all_of_type::match(
    rule_filler& fill, CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
  if (fill.has_known_type(hole)) {
    for (auto val : choices) {
      if (val->getType() == hole->getType()) {
        generated.push_back(fill.copy_value(val));
      }
    }
  }
}

void all_if_opaque::match(
    rule_filler& fill, CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
  if (fill.has_unknown_type(hole)) {
    for (auto val : choices) {
      generated.push_back(fill.select_type(hole, val->getType()));
    }
  }
}

void add::match(
    rule_filler& fill, CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
  /* if (!fill.has_unknown_type(hole)) { */
  /*   for (auto v1 : choices) { */
  /*     for (auto v2 : choices) { */
  /*       if (v1->getType() == v2->getType()) { */
  /*         generated.push_back( */
  /*             BinaryOperator::Create(Instruction::BinaryOps::Add, v1, v2));
   */
  /*       } */
  /*     } */
  /*   } */
  /* } */
}

} // namespace presyn::rules
