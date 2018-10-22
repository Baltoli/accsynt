#include "dataflow_synth.h"

#include <llvm/IR/IRBuilder.h>

#include <queue>

using namespace llvm;

namespace synth {

dataflow_synth::dataflow_synth(Function *f) :
  function_(f), dom_tree_()
{
}

void dataflow_synth::seed(Value *instr)
{
  seeds_.push_back(instr);
}

// This really needs to be recursive - we should keep track of a vector of
// values, then recurse into each child block as we come to them. Keep proper
// track of the live values at each step - just handing over the seeds obviously
// doesn't work ;)
void dataflow_synth::create_dataflow()
{
  dom_tree_.recalculate(*function_);
  auto const& roots = dom_tree_.getRoots();

  for(auto *root : roots) {
    create_block_dataflow(root, {});
  }
}

void dataflow_synth::create_block_dataflow(llvm::BasicBlock *block, 
                                           std::vector<llvm::Value *> live)
{
  // At each block, we make the set of seeds in that block live
  for(auto seed : seeds_) {
    if(auto instr = dyn_cast<Instruction>(seed)) {
      if(instr->getParent() == block) {
        live.push_back(instr);
      }
    }
  }

  // Note that the sampler is responsible for updating the set of live values -
  // it might synthesise things that shouldn't be considered.
  auto builder = IRBuilder<>(block->getTerminator());
  sampler_(builder, 1, live);

  for(auto ch : dom_tree_.getNode(block)->getChildren()) {
    create_block_dataflow(ch->getBlock(), live);
  }
}

}
