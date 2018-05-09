#pragma once

#include <dist/function_callable.h>
#include <dist/generators.h>
#include <dist/types.h>

#include <llvm/Support/raw_ostream.h>

#include <array>
#include <string>
#include <optional>
#include <random>
#include <tuple>
#include <vector>

namespace accsynt {

inline namespace v1 {

template <typename T>		
struct has_error_code_st : std::false_type {};		
		
template <typename T>		
struct has_error_code_st<FunctionCallable<T>> : std::true_type {};		
		
template <typename T>		
constexpr inline bool has_error_code_v = has_error_code_st<std::decay_t<T>>::value;

template <typename F, typename... Args>		
decltype(auto) try_apply(F&& f, Args&&... args)		
{		
  using result_t = decltype(std::apply(std::forward<F>(f), std::forward<Args...>(args...)));		
		
  try {		
    auto result = std::apply(std::forward<F>(f), std::forward<Args...>(args...));		
		
    if constexpr(has_error_code_v<F>) {		
      if(auto err = f.get_error()) {		
        return std::make_pair(true, result);		
      }		
    }
		
    return std::make_pair(false, result);		
  } catch(...) {
    return std::make_pair(true, result_t{});		
  }		
}		

template <typename R, typename Args>
struct Counterexample {
  const R f_return;
  const R g_return;
  const bool f_err;
  const bool g_err;
  const Args args;
};

template <typename F, typename G, typename Synth>
class OracleDistinguisher {
public:
  using args_t = typename Synth::args_t;
  using return_t = decltype(std::apply(std::declval<F>(), std::declval<args_t>()));
  using counterexample_t = std::optional<Counterexample<return_t, args_t>>;

  OracleDistinguisher(F& f, G& g, Synth const* s) :
    f_(f), g_(g), synth_(s)
  {
  }

  counterexample_t operator()() const
  {
    for(auto i = 0u; i < example_limit_; ++i) {
      auto example = synth_->example();
      auto&& [f_err, f_result] = try_apply(f_, example);
      auto&& [g_err, g_result] = try_apply(g_, example);

      if((f_err != g_err) || (f_result != g_result)) {
        return {{f_result, g_result, f_err, g_err, example}};
      }
    }

    return {};
  }

  const size_t example_limit_ = 100;

private:
  F& f_;
  G& g_;
  Synth const* synth_;
};

}

namespace v2 {

template <typename RefFn, typename LLVMFn, typename Synth>
class OracleDistinguisher {
public:
private:
  RefFn&& ref_fn_;
  LLVMFn&& llvm_fn_;
};

}

}
