#pragma once

#include "rule_filler.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <tuple>
#include <vector>

namespace presyn {

namespace rules {

#define ALL_RULE_DEFS                                                          \
  RULE(do_nothing)                                                             \
  RULE(all_of_type)                                                            \
  RULE(all_if_opaque)

#define RULE(name)                                                             \
  struct name {                                                                \
    void match(                                                                \
        rule_filler& filler, llvm::CallInst* hole,                             \
        std::vector<llvm::Value*> const& choices,                              \
        std::vector<llvm::Value*>& generated) const;                           \
  }; // namespace rules

ALL_RULE_DEFS

#undef RULE

} // namespace rules

inline auto all_rules()
{
  // clang-format off
  return std::tuple {
#define RULE(name) rules::name {},
    ALL_RULE_DEFS
#undef RULE
  };
  // clang-format on
}

} // namespace presyn
