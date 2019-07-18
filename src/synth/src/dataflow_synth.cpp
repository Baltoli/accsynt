#include "dataflow_synth.h"

#include <support/llvm_values.h>

#include <llvm/IR/Argument.h>
#include <llvm/IR/IRBuilder.h>

#include <queue>

using namespace support;
using namespace llvm;

namespace synth {

dataflow_synth::dataflow_synth(Function* f)
    : dataflow_synth(f, [](auto) { return true; })
{
}

dataflow_synth::dataflow_synth(compile_context const& ctx)
    : dataflow_synth(ctx.func_, [&](auto* b) {
      auto const& meta = ctx.metadata_;
      return std::find(meta.data_blocks.begin(), meta.data_blocks.end(), b)
          != meta.data_blocks.end();
    })
{
  for (auto s : ctx.metadata_.seeds) {
    seed(s);
  }

  for (auto o : ctx.metadata_.outputs) {
    output(o);
  }
}

void dataflow_synth::seed(Value* instr) { seeds_.push_back(instr); }

void dataflow_synth::output(Instruction* val) { outputs_.push_back(val); }

void dataflow_synth::create_dataflow()
{
  dom_tree_.recalculate(*function_);
  auto const& roots = dom_tree_.getRoots();

  auto root_live = std::vector<llvm::Value*>{};
  root_live.push_back(
      sampler_.constant(Type::getInt32Ty(function_->getContext())));
  root_live.push_back(
      sampler_.constant(Type::getFloatTy(function_->getContext())));

  for (auto seed : seeds_) {
    if (auto arg = dyn_cast<Argument>(seed)) {
      // TODO: fix to include integers
      /* if (arg->getType()->isFloatTy()) { */
      root_live.push_back(arg);
      /* } */
    }
  }

  for (auto* root : roots) {
    create_block_dataflow(root, root_live);
  }

  for (auto phi : phis_) {
    sampler_.add_incoming(phi, final_live_);
  }
}

void dataflow_synth::create_outputs()
{
  auto& ctx = function_->getContext();

  for (auto out_ptr : outputs_) {
    /*   // TODO: unsafe cast */
    auto type = cast<PointerType>(out_ptr->getType())->getElementType();

    auto block = out_ptr->getParent();
    auto block_live = with_type(type, final_live_.at(block));

    if (!block_live.empty()) {
      auto store_val = *uniform_sample(block_live);

      // TODO: configure this from heuristics
      /* auto phi_s = uniform_sample_if(block_live, [] (auto v) { */
      /*   return isa<PHINode>(v); */
      /* }); */
      /* if(phi_s != block_live.end()) { */
      /*   store_val = *phi_s; */
      /* } */
      new StoreInst(store_val, out_ptr, block->getTerminator());
    }
  }

  auto rt = function_->getReturnType();
  if (!rt->isVoidTy()) {
    for (auto& block : *function_) {
      auto term = block.getTerminator();
      if (isa<ReturnInst>(term)) {
        term->eraseFromParent();
        auto exit_live = final_live_.at(&block);
        auto live_with_type = with_type(rt, exit_live);
        auto ret_val = *uniform_sample(live_with_type);

        if (!ret_val) {
          ret_val = Constant::getNullValue(rt);
        }

        ReturnInst::Create(ctx, ret_val, &block);
      }
    }
  }
}

void dataflow_synth::create_block_dataflow(
    llvm::BasicBlock* block, std::vector<llvm::Value*> live)
{
  // At each block, we make the set of seeds in that block live
  for (auto seed : seeds_) {
    if (auto instr = dyn_cast<Instruction>(seed)) {
      if (instr->getParent() == block) {
        live.push_back(instr);
      }
    }
  }

  auto builder = IRBuilder<>(&*block->begin());

  auto n_preds = std::distance(pred_begin(block), pred_end(block));
  if (n_preds > 1) {
    auto types = all_types(live);
    for (auto ty : types) {
      auto phi = builder.CreatePHI(ty, n_preds);
      live.push_back(phi);
      phis_.push_back(phi);
    }
  }

  // Note that the sampler is responsible for updating the set of live values -
  // it might synthesise things that shouldn't be considered.
  builder.SetInsertPoint(block->getTerminator());
  if (should_populate_(block)) {
    sampler_.block(builder, 4, live);
  }

  for (auto ch : dom_tree_.getNode(block)->getChildren()) {
    create_block_dataflow(ch->getBlock(), live);
  }

  final_live_.insert({ block, live });
}

dataflow_synth::block_live_map const& dataflow_synth::block_live() const
{
  return final_live_;
}
} // namespace synth
