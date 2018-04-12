#pragma once

#include <llvm/IR/IRBuilder.h>

#include <dist/synth.h>

#include <memory>

namespace accsynt {

template <typename R, typename... Args>
class Loop : public Synthesizer<R, Args...> {
public:
  Loop(R r, Args... args) 
    : Synthesizer<R, Args...>(r, args...) 
  {
    index_for_each(this->arg_types_, [this] (auto& ty, auto i) {
      if constexpr(is_array(ty)) {
        sizes_.insert_or_assign(i, ty.array_size());
      }
    });
  }

  using Synthesizer<R, Args...>::operator();

  // We can use this synthesizer when at least one (for now, exactly one?) of
  // the parameters is sized (i.e. is a fixed size array)
  // extend to handle sized pointers next
  virtual bool can_synthesize() const override
  {
    return !sizes_.empty();
  }

private:
  std::unique_ptr<llvm::Module> generate_candidate(bool&) override;
  
  std::map<size_t, size_t> sizes_ = {};
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
