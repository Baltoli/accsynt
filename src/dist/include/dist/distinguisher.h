#pragma once

#include <dist/generators.h>

#include <array>
#include <string>
#include <optional>
#include <random>
#include <tuple>
#include <vector>

using gen::Geometric;
using gen::Tuple;

template<class R, class... Args>
struct Counterexample {
  R f_return;
  R g_return;
  std::tuple<Args...> args;
};

template<class F, class... Args>
using counterexample_t = 
  std::optional<Counterexample<std::invoke_result_t<F, Args...>, Args...>>;

template<class F, class G, class... Args>
class OracleDistinguisher {
public:
  using return_t = std::invoke_result_t<G, Args...>;

  OracleDistinguisher(F&& f, G&& g, size_t limit) :
    f_(f), g_(g), example_limit_(limit)
  {
    static_assert(std::is_convertible_v<
      std::invoke_result_t<F, Args...>, // from
      std::invoke_result_t<G, Args...>  // to
    >, "f and g must yield the same result type");
  }

  counterexample_t<F, Args...> operator()() const;

private:
  F& f_;
  G& g_;
  size_t example_limit_;
};

template<class... Args>
auto make_oracle_distinguisher(auto&& f, auto&& g, size_t limit=10'000)
{
  return OracleDistinguisher<decltype(f), decltype(g), Args...>(f, g, limit);
}

template<class F, class G, class... Args>
counterexample_t<F, Args...> OracleDistinguisher<F, G, Args...>::operator()() const
{
  auto sampler = Tuple(Geometric<Args>(0.1)...);

  for(auto i = 0; i < example_limit_; ++i) {
    auto args = sampler();
    auto f_result = return_t{std::apply(f_, args)};
    auto g_result = std::apply(g_, args);
    
    if(f_result != g_result) {
      return {{f_result, g_result, args}};
    }
  }

  return {};
}
