#pragma once

#include "filler.h"

namespace presyn {

class rule_filler : public filler {
public:
  rule_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;

  // The number of values to collect for rule matching - a bigger pool size
  // means less emphasis on locality, and a greater likelihood of far-reaching
  // dependencies.
  int pool_size_ = 5;
};

} // namespace presyn
