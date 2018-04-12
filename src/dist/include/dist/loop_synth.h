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
  void construct(llvm::Function *f, llvm::IRBuilder<>& b) const override;
  
  std::map<size_t, size_t> sizes_ = {};
};

template <typename R, typename... Args>
void Loop<R, Args...>::construct(llvm::Function *f, llvm::IRBuilder<>& b) const
{
  b.CreateRet(b.getInt64(0));
}

}
