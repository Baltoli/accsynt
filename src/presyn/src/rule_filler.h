#pragma once

#include "filler.h"

#include <vector>

namespace presyn {

class rule_filler : public filler {
public:
  rule_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;

private:
  // Collect values from any blocks that dominate this one (i.e. walking
  // backwards in the dominance tree). This will collect us values that are safe
  // to use in the synthesis, but might not be as interesting as local ones once
  // we incorporate weighting).
  std::vector<llvm::Value*> collect_safe(llvm::CallInst*) const;

  // Collect local values walking backwards from this hole (only in the same
  // basic block).
  std::vector<llvm::Value*> collect_local(llvm::CallInst*) const;

  // Collect function parameters
  std::vector<llvm::Value*> collect_params(llvm::CallInst*) const;

  // Collect interesting constants that might appear in a filled hole.
  std::vector<llvm::Value*> collect_constants(llvm::CallInst*) const;

  // The number of values to collect for rule matching - a bigger pool size
  // means less emphasis on locality, and a greater likelihood of far-reaching
  // dependencies.
  size_t pool_size_ = 5;
};

} // namespace presyn
