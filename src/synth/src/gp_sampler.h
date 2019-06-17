#pragma once

#include "evaluator.h"

#include <llvm/IR/Function.h>

namespace synth {

class gp_sampler {
public:
  gp_sampler(llvm::Function*, evaluator const&);

private:
  llvm::Function* skeleton_;
  evaluator const& eval_;
};

} // namespace synth
