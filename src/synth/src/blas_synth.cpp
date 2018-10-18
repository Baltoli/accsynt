#include "loops.h"
#include "synthesizer.h"

#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <iostream>

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

blas_synth::blas_synth(property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref),
  blas_props_(ps), gen_(ps),
  loops_(loop::loops(blas_props_.loop_count())),
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
  build_control_flow(*current_loop_, fn);

  llvm::errs() << *fn << '\n';
  return fn;
}

std::vector<llvm::Instruction *> 
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

  auto entry = BasicBlock::Create(ctx, "entry", fn);
  auto exit = BasicBlock::Create(ctx, "exit", fn);
  BranchInst::Create(exit, entry);

  // Create dummy return value until we do data flow properly.
  auto rt = fn->getReturnType();
  if(rt->isVoidTy()) {
    ReturnInst::Create(ctx, exit);
  } else {
    ReturnInst::Create(ctx, Constant::getNullValue(rt), exit);
  }

  return {};
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
