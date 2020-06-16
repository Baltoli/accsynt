#pragma once

#include "filler.h"

#include <llvm/IR/Value.h>

#include <tuple>
#include <vector>

namespace presyn {

struct first_of_type {
  void match(
      filler const&, llvm::CallInst*, std::vector<llvm::Value*> const&,
      std::vector<llvm::Value*>&) const;
};

inline auto all_rules() { return std::tuple {first_of_type {}}; }

} // namespace presyn
