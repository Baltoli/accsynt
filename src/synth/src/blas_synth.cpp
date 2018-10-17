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
  build_control_flow(*current_loop_, fn);

  return fn;
}

std::vector<llvm::Instruction *> 
blas_synth::build_control_flow(loop shape, Function *fn) const
{
  auto rt = fn->getFunctionType()->getReturnType();
  auto bb = BasicBlock::Create(thread_context::get(), "ret", fn);
  auto rv = rt->isVoidTy() ? nullptr : Constant::getNullValue(rt);
  ReturnInst::Create(mod_.getContext(), rv, bb);
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
