#pragma once

#include <llvm/IR/IRBuilder.h>

#include <dist/synth.h>

#include <memory>

namespace accsynt {

template <typename R, typename... Args>
class Loop : public Synthesizer<R, Args...> {
public:
  Loop(R r, Args... args) : Synthesizer<R, Args...>(r, args...) {}
  using Synthesizer<R, Args...>::operator();

private:
  std::unique_ptr<llvm::Module> generate_candidate(bool&) override;
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Loop<R, Args...>::generate_candidate(bool& done)
{
  auto mod = std::make_unique<llvm::Module>("loop-candidate", ThreadContext::get());
  auto B = llvm::IRBuilder<>{mod->getContext()};

  while(!done) {
    auto fn = llvm::Function::Create(this->llvm_function_type(), llvm::GlobalValue::ExternalLinkage, 
                                     "cand", mod.get());
    auto bb = llvm::BasicBlock::Create(fn->getContext(), "", fn);
    B.SetInsertPoint(bb);

    // Can we make this more general? Code repeated. Need to separate the loop
    // from the generation of a single example

    if(this->satisfies_examples(fn)) {
      done = true;
      return std::move(mod);
    }
  }

  return nullptr;
}

}
