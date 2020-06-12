#pragma once

#include "filler.h"

#include <llvm/IR/Dominators.h>

#include <map>
#include <vector>

namespace presyn {

class random_filler : public filler {
public:
  random_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;

private:
  std::vector<llvm::Value*> live_values(llvm::CallInst*) const;

  llvm::DominatorTree tree_for(llvm::CallInst*) const;
};

} // namespace presyn
