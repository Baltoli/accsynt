#include "synthesizer.h"

#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

blas_synth::blas_synth(property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref),
  gen_(ps)
{
  make_examples(gen_, 1'000);
}

std::string blas_synth::name() const
{
  return "BLAS";
}

llvm::Function *blas_synth::candidate()
{
  auto fn = create_stub();
  auto rt = fn->getFunctionType()->getReturnType();
  
  auto bb = BasicBlock::Create(thread_context::get(), "ret", fn);
  auto rv = rt->isVoidTy() ? nullptr : Constant::getNullValue(rt);
  ReturnInst::Create(mod_.getContext(), rv, bb);
  return fn;
}

}
