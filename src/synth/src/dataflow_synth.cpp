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

  auto work = std::queue<BasicBlock *>{};
  for(auto *root : roots) {
    work.push(root);
  }

  while(!work.empty()) {
    auto block = work.front();
    work.pop();

    auto builder = IRBuilder<>(block->getTerminator());
    sampler_(builder, 1, seeds_);

    for(auto ch : dom_tree_.getNode(block)->getChildren()) {
      work.push(ch->getBlock());
    }
  }
}

}
