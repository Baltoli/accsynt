#pragma once

#include "value_sampler.h"

#include <llvm/IR/Function.h>

namespace synth {

class dataflow_synth {
public:
  dataflow_synth(llvm::Function *);

  void seed(llvm::Instruction *);
  void create_dataflow();

private:
  llvm::Function *function_;
  value_sampler sampler_ = {};
};

}
