#pragma once

#include <dist/distinguisher.h>
#include <dist/function_callable.h>
#include <dist/linear_synth.h>

namespace llvm {
  class Function;
}

namespace synth {

template <typename F, typename R, typename... Args>
class Oracle {
public:
  Oracle(F f, R r, Args... args) :
    reference_{f}
  {}

  /* llvm::Function *operator()(); */
private:
  /* Linear<R, Args...> linear_; */
  F reference_;
};

/* template <typename F, typename R, typename... Args> */
/* llvm::Function *Oracle<F, R, Args...>::operator()() */
/* { */
  /* while(true) { */
  /*   auto candidate = linear_(); */
  /*   auto fc = FunctionCallable<R>{candidate}; */
  /*   auto dist = dist::make_oracle_distinguisher<Args...>(reference_, fc); */

  /*   auto example = dist(); */
  /*   if(example) { */
  /*     linear_.add_example(example->f_return, example->args); */
  /*   } else { */
  /*     return candidate; */
  /*   } */
  /* } */
/* } */

}
