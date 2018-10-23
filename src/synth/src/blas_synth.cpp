#include "blas_synth.h"
#include "dataflow_synth.h"
#include "loops.h"

#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

#include <iostream>

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

blas_synth::blas_synth(property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref),
  blas_props_(ps), gen_(ps),
  loops_(loop::loops(blas_props_.merged_loop_count())),
  current_loop_(loops_.begin())
{
  make_examples(gen_, 1'000);
}

std::string blas_synth::name() const
{
  return "BLAS";
}

llvm::Function *blas_synth::candidate()
{
  next_loop();

  auto fn = create_stub();
  // TODO: this doesn't handle the case where there is no loop - it needs to be
  // optional
  auto data_synth = dataflow_synth(fn);
  auto [seeds, outputs, exit] = build_control_flow(*current_loop_, fn);

  // TODO: maybe put this code inside the control flow generator and pass a
  // reference to the dataflow synth?
  for(auto* instr : seeds) {
    data_synth.seed(instr);
  }

  data_synth.create_dataflow();
  llvm::errs() << *fn << '\n';
  return fn;
}

blas_control_data
blas_synth::build_control_flow(loop shape, Function *fn) const
{
  /*
   * What this needs to do for BLAS is lay out loop control flow based on the
   * shape passed in.
   *
   * We need an auxiliary method that will lay out the control flow for a single
   * loop but with a specified end point. That allows us to handle both
   * sequencing and nesting by walking the structure properly.
   *
   * That aux. method will also get a reference to the insertion points vector
   * so that it knows where to put them - this parent function will then handle
   * collecting them together and building the overall control flow.
   *
   * Data flow follows.
   */
  auto& ctx = fn->getContext();
  auto seeds = std::vector<Instruction *>{};
  auto outputs = std::vector<Instruction *>{};

  auto entry = BasicBlock::Create(ctx, "entry", fn);
  auto exit = BasicBlock::Create(ctx, "exit", fn);

  auto header = build_loop(shape, exit, seeds, outputs);
  BranchInst::Create(header, entry);

  // Create dummy return value until we do data flow properly.
  auto rt = fn->getReturnType();
  if(rt->isVoidTy()) {
    ReturnInst::Create(ctx, exit);
  } else {
    ReturnInst::Create(ctx, Constant::getNullValue(rt), exit);
  }

  return { seeds, outputs, exit };
}

// TODO: handle nested loops in this method - loop over the children of shape
// and build them appropriately.
// TODO: logic to lay out sequences of loops when there's no parent.
BasicBlock *blas_synth::build_loop(loop shape, BasicBlock* end_dst, 
                                   std::vector<Instruction *>& seeds,
                                   std::vector<Instruction *>& outputs) const
{
  auto loop_id = *shape.ID();
  auto indexes = blas_props_.size_indexes();
  auto size_idx = *std::next(indexes.begin(), loop_id);

  auto fn = end_dst->getParent();
  auto& ctx = fn->getContext();

  auto size_arg = std::next(fn->arg_begin(), size_idx);
  auto iter_ty = IntegerType::get(ctx, 32); // TODO: ???

  auto header = BasicBlock::Create(ctx, "header", fn);
  auto B = IRBuilder<>(header);

  auto pre_body = BasicBlock::Create(ctx, "pre", fn);
  B.SetInsertPoint(pre_body);
  auto iter = B.CreatePHI(iter_ty, 2, "iter");
  iter->addIncoming(ConstantInt::get(iter_ty, 0), header);

  auto with_size = blas_props_.pointers_with_size(size_idx);
  for(auto ptr_idx : with_size) {
    auto ptr_arg = std::next(fn->arg_begin(), ptr_idx);
    auto gep = B.CreateGEP(ptr_arg, {iter});
    auto load = B.CreateLoad(gep);
    
    seeds.push_back(load);

    if(blas_props_.is_output(ptr_idx)) {
      // Now somehow store
    }
  }

  auto post_body = BasicBlock::Create(ctx, "post", fn);
  B.SetInsertPoint(post_body);

  auto exit = BasicBlock::Create(ctx, "loop_exit", fn);
  B.SetInsertPoint(exit);
  auto next = B.CreateAdd(iter, ConstantInt::get(iter_ty, 1), "next_iter");
  iter->addIncoming(next, exit);
  auto cond = B.CreateICmpEQ(iter, B.CreateSExtOrBitCast(size_arg, iter_ty));
  B.CreateCondBr(cond, end_dst, pre_body);

  BranchInst::Create(pre_body, header);
  BranchInst::Create(post_body, pre_body);
  BranchInst::Create(exit, post_body);

  return header;
}

void blas_synth::next_loop()
{
  if(loops_.begin() == loops_.end()) {
    return;
  }

  current_loop_++;
  if(current_loop_ == loops_.end()) {
    current_loop_ = loops_.begin();
  }
}

}
