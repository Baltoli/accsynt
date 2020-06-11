#pragma once

#include <llvm/IR/Value.h>

namespace presyn {

class candidate;

/**
 * Interface that represents something capable of choosing values for a
 * particular hole. The only operation publicly visible is construction;
 * everything else is handled by passing it to a newly constructed candidate.
 */
class filler {
  friend class candidate;

public:
  virtual ~filler() = default;

protected:
  virtual llvm::Value* fill(llvm::Value*) = 0;
};

/**
 * Intentionally stupid filler implementation to test the interface - it always
 * fills holes with the constant value 0 for the same type as the hole.
 */
class zero_filler : public filler {
public:
  zero_filler() = default;

protected:
  llvm::Value* fill(llvm::Value*) override;
};

} // namespace presyn
