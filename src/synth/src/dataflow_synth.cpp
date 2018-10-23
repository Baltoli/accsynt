#include "dataflow_synth.h"

#include <support/llvm_values.h>

#include <llvm/IR/IRBuilder.h>

#include <queue>

using namespace support;
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

void dataflow_synth::create_dataflow()
{
  dom_tree_.recalculate(*function_);
  auto const& roots = dom_tree_.getRoots();

  for(auto *root : roots) {
    create_block_dataflow(root, {});
  }

  for(auto phi : phis_) {
    sampler_.add_incoming(phi, final_live_);
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

  auto builder = IRBuilder<>(&*block->begin());

  auto n_preds = std::distance(pred_begin(block), pred_end(block));
  if(n_preds > 1) {
    auto types = all_types(live);
    for(auto ty : types) {
      auto phi = builder.CreatePHI(ty, n_preds);
      live.push_back(phi);
      phis_.push_back(phi);
    }
  }

  // Note that the sampler is responsible for updating the set of live values -
  // it might synthesise things that shouldn't be considered.
  builder.SetInsertPoint(block->getTerminator());
  sampler_.block(builder, 1, live);

  for(auto ch : dom_tree_.getNode(block)->getChildren()) {
    create_block_dataflow(ch->getBlock(), live);
  }

  final_live_.insert({block, live});
}

}
