#pragma once

#include <dist/linear_synth.h>

namespace llvm {
  class Function;
}

namespace synth {

template <typename F, typename R, typename... Args>
class Oracle {
public:
  Oracle(F f) :
    linear_{}, reference_{f} {}

  llvm::Function *operator()();
private:
  Linear<R, Args...> linear_;
  F reference_;
};

template <typename R, typename... Args>
auto make_oracle_synth(auto f)
{
  return Oracle<decltype(f), R, Args...>(f);
}

template <typename F, typename R, typename... Args>
llvm::Function *Oracle<F, R, Args...>::operator()()
{
  return nullptr;
}

}
