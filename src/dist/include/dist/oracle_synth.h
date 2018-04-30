#pragma once

#include <dist/distinguisher.h>
#include <dist/function_callable.h>
#include <dist/linear_synth.h>
#include <dist/loop_synth.h>
#include <dist/synth.h>

#include <memory>

namespace llvm {
  class Function;
}

namespace accsynt {

template <typename F, typename R, typename... Args>
class Oracle {
public:
  using synth_t = Synthesizer<R, Args...>;
  using ret_t = typename synth_t::ret_t;

  Oracle(F f, R r, Args... args) :
    return_type_(r), arg_types_(args...),
    reference_{f}
  {
    options_.emplace_back(new LoopSynth{r, args...});
    options_.emplace_back(new Linear{r, args...});
  }

  std::unique_ptr<llvm::Module> operator()();

private:
  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<std::unique_ptr<synth_t>> options_ = {};
  F reference_;
};

template <typename F, typename R, typename... Args>
std::unique_ptr<llvm::Module> Oracle<F, R, Args...>::operator()()
{
  auto synth_i = std::find_if(begin(options_), end(options_), [](auto& opt) {
    return opt->can_synthesize();
  });

  if(synth_i == end(options_)) {
    return nullptr;
  }

  auto synth = synth_i->get();
  while(true) {
    // This isn't so nice
    auto candidate = synth->operator()();
    if(!candidate) {
      return nullptr;
    }

    auto fc = std::apply([&](auto&&... args) {
      return v2::FunctionCallable(v2::with_error_code, candidate.get(), "cand", return_type_, args...);
    }, arg_types_);
    /* auto dist = OracleDistinguisher{reference_, fc, synth}; */

    /* auto example = dist(); */
    /* if(example) { */
    /*   synth->add_example(example->f_return, example->args); */
    /* } else { */
    /*   return candidate; */
    /* } */
  }
}

}
