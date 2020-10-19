#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <tuple>
#include <vector>

namespace presyn {

namespace rules {

#define RULE(name)                                                             \
  struct name {                                                                \
    void match(                                                                \
        llvm::CallInst* hole, std::vector<llvm::Value*> const& choices,        \
        std::vector<llvm::Value*>& generated) const;                           \
  } // namespace rules

RULE(do_nothing);
RULE(all_of_type);

#undef RULE

} // namespace rules

inline auto all_rules()
{
  // clang-format off
  return std::tuple {
    rules::do_nothing {}, 
    rules::all_of_type {}
  };
  // clang-format on
}

} // namespace presyn
