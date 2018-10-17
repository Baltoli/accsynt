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
  gen_(ps), mod_("blas_mod", thread_context::get())
{
}

std::string blas_synth::name() const
{
  return "BLAS";
}

llvm::Function *blas_synth::generate()
{
  if(examples_.empty()) {
    make_examples(gen_, 1'000);
  }

  auto cand = candidate();
  errs() << satisfies_examples(cand) << '\n';
  return cand;
}

llvm::Function *blas_synth::candidate()
{
  for(auto& fn : mod_) { 
    fn.eraseFromParent();
  }

  auto fn = properties_.type_signature.create_function(mod_);
  auto rt = fn->getFunctionType()->getReturnType();
  
  auto bb = BasicBlock::Create(thread_context::get(), "ret", fn);
  auto rv = rt->isVoidTy() ? nullptr : Constant::getNullValue(rt);
  ReturnInst::Create(mod_.getContext(), rv, bb);
  return fn;
}

bool blas_synth::satisfies_examples(llvm::Function *cand) const
{
  call_wrapper wrap(properties_.type_signature, *cand->getParent(), cand->getName());

  for(auto [in, out] : examples_) {
    auto ret = wrap.call(in);

    if(ret != out.return_value || in != out.output_args) {
      return false;
    }
  }

  return true;
}

}
