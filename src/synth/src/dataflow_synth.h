#pragma once

#include "value_sampler.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Function.h>

namespace synth {

class dataflow_synth {
public:
  dataflow_synth(llvm::Function *);

  void seed(llvm::Value *);
  void create_dataflow();

private:
  void create_block_dataflow(llvm::BasicBlock *block, 
                             std::vector<llvm::Value *> live);

  llvm::Function *function_;
  llvm::DominatorTree dom_tree_;

  std::vector<llvm::Value *> seeds_ = {};
  value_sampler sampler_ = {};
};

}
