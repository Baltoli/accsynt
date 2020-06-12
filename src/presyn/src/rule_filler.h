#pragma once

#include "filler.h"

namespace presyn {

class rule_filler : public filler {
public:
  rule_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;
};

} // namespace presyn
