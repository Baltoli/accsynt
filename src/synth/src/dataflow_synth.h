#pragma once

#include "value_sampler.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Function.h>

#include <map>

namespace synth {

class dataflow_synth {
public:
  using block_live_map = 
    std::map<llvm::BasicBlock *, std::vector<llvm::Value *>>;

  dataflow_synth(llvm::Function *);

  void seed(llvm::Value *);
  void create_dataflow();

  block_live_map const& block_live() const;

private:
  void create_block_dataflow(llvm::BasicBlock *block, 
                             std::vector<llvm::Value *> live);

  llvm::Function *function_;
  llvm::DominatorTree dom_tree_;

  std::vector<llvm::Value *> seeds_ = {};
  std::vector<llvm::PHINode *> phis_ = {};
  block_live_map final_live_ = {};

  value_sampler sampler_ = {};
};

}
