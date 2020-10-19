#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <tuple>
#include <vector>

namespace presyn {

namespace rules {

struct do_nothing {
  void match(
      llvm::CallInst* hole, std::vector<llvm::Value*> const& choices,
      std::vector<llvm::Value*>& generated) const
  {
  }
};

} // namespace rules

inline auto all_rules() { return std::tuple {rules::do_nothing {}}; }

} // namespace presyn
