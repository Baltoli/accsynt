#pragma once

#include "filler.h"

#include <vector>

namespace presyn {

class random_filler : public filler {
public:
  random_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;

private:
  std::vector<llvm::Value*> live_values(llvm::CallInst*) const;
};

} // namespace presyn
