#pragma once

#include "fragment.h"
#include "value_sampler.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Function.h>

#include <functional>
#include <map>

namespace synth {

class dataflow_synth {
public:
  using block_live_map = std::map<llvm::BasicBlock*, std::vector<llvm::Value*>>;

  template <typename BlockPred>
  dataflow_synth(llvm::Function*, BlockPred&& pred);

  dataflow_synth(llvm::Function*);

  dataflow_synth(compile_context const& ctx);

  void seed(llvm::Value*);
  void output(llvm::Instruction*);
  void create_dataflow();
  void create_outputs();

  block_live_map const& block_live() const;

private:
  void create_block_dataflow(
      llvm::BasicBlock* block, std::vector<llvm::Value*> live);

  llvm::Function* function_;
  llvm::DominatorTree dom_tree_;

  std::vector<llvm::Value*> seeds_ = {};
  std::vector<llvm::Instruction*> outputs_ = {};
  std::vector<llvm::PHINode*> phis_ = {};
  block_live_map final_live_ = {};

  std::function<bool(llvm::BasicBlock*)> should_populate_;

  value_sampler sampler_ = {};
};

template <typename BlockPred>
dataflow_synth::dataflow_synth(llvm::Function* fn, BlockPred&& pred)
    : function_(fn)
    , dom_tree_()
    , should_populate_(pred)
{
}
} // namespace synth
