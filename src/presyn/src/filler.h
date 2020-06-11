#pragma once

#include "candidate.h"

#include <llvm/IR/Value.h>

namespace presyn {

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

} // namespace presyn
