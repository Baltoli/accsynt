#pragma once

#include "filler.h"

namespace presyn {

class random_filler : public filler {
public:
  random_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;
};

} // namespace presyn
