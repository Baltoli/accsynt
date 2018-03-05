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

using gen::Geometric;
using gen::Tuple;

namespace dist {

template <typename R, typename Args>
struct Counterexample {
  const R f_return;
  const R g_return;
  const bool f_err;
  const bool g_err;
  const Args args;
};

template <typename F, typename G, typename ArgsT>
class OracleDistinguisher {
public:
  using args_tuple_t = typename types::example_ts<ArgsT>::type;
  using return_t = decltype(std::apply(std::declval<F>(), std::declval<args_tuple_t>()));
  using counterexample_t = std::optional<Counterexample<return_t, args_tuple_t>>;

  OracleDistinguisher(F& f, G& g, ArgsT args) :
    f_(f), g_(g), args_(args)
  {}

  counterexample_t operator()() const
  {
    const auto gen = [this] {
      auto ret = args_tuple_t{};
      util::zip_for_each(ret, args_, [&](auto& ex, auto a) {
        ex = a.generate();
      });
      return ret;
    };

    for(auto i = 0u; i < example_limit_; ++i) {
      auto example = gen();
      auto&& [f_err, f_result] = try_apply(f_, example);
      auto&& [g_err, g_result] = try_apply(g_, example);

      if((f_err != g_err) || (f_result != g_result)) {
        return {{f_result, g_result, f_err, g_err, example}};
      }
    }

    return {};
  }

  size_t example_limit_ = 10'000;

private:
  F& f_;
  G& g_;
  ArgsT args_;
};

}
