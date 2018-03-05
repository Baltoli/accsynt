#pragma once

#include <dist/distinguisher.h>
#include <dist/function_callable.h>
#include <dist/linear_synth.h>

#include <memory>

namespace llvm {
  class Function;
}

namespace synth {

template <typename F, typename R, typename... Args>
class Oracle {
public:
  Oracle(F f, R r, Args... args) :
    linear_{r, args...},
    reference_{f}
  {}

  std::unique_ptr<llvm::Module> operator()();

private:
  Linear<R, Args...> linear_;
  F reference_;
};

template <typename F, typename R, typename... Args>
std::unique_ptr<llvm::Module> Oracle<F, R, Args...>::operator()()
{
  using ret_t = typename decltype(linear_)::ret_t;

  while(true) {
    auto candidate = linear_();
    if(!candidate) {
      return nullptr;
    }

    auto fc = FunctionCallable<ret_t>{candidate.get(), "cand", true};
    auto dist = dist::OracleDistinguisher{reference_, fc, linear_.arg_types()};

    auto example = dist();
    if(example) {
      linear_.add_example(example->f_return, example->args);
    } else {
      return candidate;
    }
  }
}

}
