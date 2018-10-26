#include "blas_synth.h"
#include "dataflow_synth.h"
#include "loops.h"

#include <support/llvm_values.h>
#include <support/random.h>
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

Function *blas_synth::candidate()
{
  next_loop();

  auto fn = create_stub();

  auto [seeds, outputs, blocks, exit] = should_loop() ?
    build_control_flow(fn, *current_loop_) :
    build_control_flow(fn);

  auto data_synth = dataflow_synth(fn, [&] (auto *b) {
    auto ret = std::find(blocks.begin(), blocks.end(), b) != blocks.end();
    return ret;
  });

  // TODO: maybe put this code inside the control flow generator and pass a
  // reference to the dataflow synth?
  for(auto* instr : seeds) {
    data_synth.seed(instr);
  }

  for(auto& arg : fn->args()) {
    data_synth.seed(&arg);
  }

  auto& ctx = fn->getContext();

  auto rt = fn->getReturnType();
  if(rt->isVoidTy()) {
    ReturnInst::Create(ctx, exit);
  } else {
    ReturnInst::Create(ctx, Constant::getNullValue(rt), exit);
  }

  data_synth.create_dataflow();
  auto const& live = data_synth.block_live();

  for(auto out_ptr : outputs) {
    // TODO: unsafe cast
    auto type = cast<PointerType>(out_ptr->getType())->getElementType();

    auto block = out_ptr->getParent();
    auto block_live = with_type(type, live.at(block));

    if(!block_live.empty()) {
      // TODO: in some situations phis are preferable - basically if we have
      // nested loops. Work out a way to integrate this.

      auto store_val = *uniform_sample(block_live);
      auto phi_s = uniform_sample_if(block_live, [] (auto v) {
        return isa<PHINode>(v);
      });
      if(phi_s != block_live.end()) {
        store_val = *phi_s;
      }
      new StoreInst(store_val, out_ptr, block->getTerminator());
    }
  }

  if(!rt->isVoidTy()) {
    auto ret = exit->getTerminator();
    ret->eraseFromParent();

    auto exit_live = live.at(exit);
    auto ret_val = *uniform_sample(with_type(rt, exit_live));
    ReturnInst::Create(ctx, ret_val, exit);
  }

  llvm::errs() << *fn << '\n';
  return fn;
}

blas_control_data
blas_synth::build_control_flow(Function *fn, loop shape) const
{
  std::cerr << shape << '\n';
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
  auto blocks = std::vector<BasicBlock *>{};

  auto entry = BasicBlock::Create(ctx, "entry", fn);
  auto exit = BasicBlock::Create(ctx, "exit", fn);

  auto header = build_loop(shape, exit, seeds, outputs, blocks, {});
  BranchInst::Create(header, entry);

  return { seeds, outputs, blocks, exit };
}

blas_control_data
blas_synth::build_control_flow(Function *fn) const
{
  auto& ctx = fn->getContext();

  auto entry = BasicBlock::Create(ctx, "entry", fn);
  auto body = BasicBlock::Create(ctx, "body", fn);
  auto exit = BasicBlock::Create(ctx, "exit", fn);

  BranchInst::Create(body, entry);
  BranchInst::Create(exit, body);

  return { {}, {}, { body }, exit };
}

// TODO: handle nested loops in this method - loop over the children of shape
// and build them appropriately.
// TODO: logic to lay out sequences of loops when there's no parent.
BasicBlock *blas_synth::build_loop(loop shape, BasicBlock* end_dst, 
                                   std::vector<Instruction *>& seeds,
                                   std::vector<Instruction *>& outputs,
                                   std::vector<BasicBlock *>& data_blocks,
                                   std::vector<Value *> iters) const
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

  auto body_pre = BasicBlock::Create(ctx, "body_pre", fn);
  auto body_post = BasicBlock::Create(ctx, "body_post", fn);
  auto exit = BasicBlock::Create(ctx, "loop_exit", fn);

  data_blocks.push_back(body_pre);

  auto check = BasicBlock::Create(ctx, "loop_check", fn);
  B.SetInsertPoint(check);
  auto iter = B.CreatePHI(iter_ty, 2, "iter");
  iter->addIncoming(ConstantInt::get(iter_ty, 0), header);
  auto next = B.CreateAdd(iter, ConstantInt::get(iter_ty, 1), "next_iter");
  iter->addIncoming(next, body_post);
  auto cond = B.CreateICmpSLT(iter, B.CreateSExtOrBitCast(size_arg, iter_ty));
  B.CreateCondBr(cond, body_pre, exit);

  B.SetInsertPoint(body_pre);
  auto with_size = blas_props_.pointers_with_size(size_idx);
  for(auto ptr_idx : with_size) {
    auto ptr_arg = std::next(fn->arg_begin(), ptr_idx);
    auto gep = B.CreateGEP(ptr_arg, {iter});
    auto load = B.CreateLoad(gep);
    
    seeds.push_back(load);

    if(blas_props_.is_output(ptr_idx)) {
      // TODO: unsafe cast

      auto ip = B.saveIP();

      B.SetInsertPoint(body_post);
      auto store_gep = B.CreateGEP(ptr_arg, {iter});
      outputs.push_back(cast<Instruction>(store_gep));

      B.restoreIP(ip);
    }
  }

  iters.push_back(iter);
  if(iters.size() == 2) {
    for(auto idx : blas_props_.unsized_pointers()) {
      auto ptr_arg = std::next(fn->arg_begin(), idx);

      // TODO: make properly generic: push this code into an indexing
      // abstraction that can also do convolution.
      // ------- shortcut
      auto stride = std::next(fn->arg_begin());
      auto mul = B.CreateMul(iters.at(0), stride);
      auto array_index = B.CreateAdd(iters.at(1), mul);
      auto gep = B.CreateGEP(ptr_arg, {array_index});
      auto load = B.CreateLoad(gep);

      seeds.push_back(load);
      // ------- end shortcut
    }
  }

  BasicBlock *dest = body_post;
  for(auto& ch : shape) {
    dest = build_loop(*ch, dest, seeds, outputs, data_blocks, iters);
  }
  B.CreateBr(dest);

  B.SetInsertPoint(body_post);
  B.CreateBr(check);

  if(shape.children_size() > 0) {
    data_blocks.push_back(body_post);
  }

  BranchInst::Create(check, header);
  BranchInst::Create(end_dst, exit);

  return header;
}

bool blas_synth::should_loop() const
{
  return !loops_.empty();
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
