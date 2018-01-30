#pragma once

#include <array>
#include <string>
#include <optional>
#include <random>
#include <tuple>
#include <vector>

template<class... Args>
class TupleSampler {
public:
  TupleSampler() :
    rd(), engine(rd()) {}

  template<class... Ds>
  std::tuple<Args...> sample(Ds... ds);

  template<class Dists>
  std::tuple<Args...> sample(Dists ds);
private:
  std::random_device rd;
  std::default_random_engine engine;
};

template<class... Args>
template<class... Ds>
std::tuple<Args...> TupleSampler<Args...>::sample(Ds... ds)
{
  return sample(std::tuple<Ds...>(ds...));
}

template<class... Args>
template<class Dists>
std::tuple<Args...> TupleSampler<Args...>::sample(Dists ds)
{
  static_assert(sizeof...(Args) == std::tuple_size_v<Dists>, "Each argument needs a distribution");

  auto ret = std::tuple<Args...>{};
  zip_for_each(ret, ds, [this](auto&& t, auto&& d) {
    t = d(engine);
  });

  return ret;
}

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

  OracleDistinguisher(F&& f, G&& g, size_t limit=10000) :
    f_(f), g_(g), example_limit_(limit)
  {
    static_assert(std::is_convertible_v<
      std::invoke_result<F, Args...>, // from
      std::invoke_result<G, Args...>  // to
    >, "f and g must yield the same result type");
  }

  counterexample_t<F, Args...> operator()() const;

private:
  F& f_;
  G& g_;
  size_t example_limit_;
};

template<class... Args>
auto make_oracle_distinguisher(auto&& f, auto&& g)
{
  return OracleDistinguisher<decltype(f), decltype(g), Args...>(f, g);
}

template<class F, class G, class... Args>
counterexample_t<F, Args...> OracleDistinguisher<F, G, Args...>::operator()() const
{
  auto dists = std::make_tuple(std::geometric_distribution<Args>{0.1}...);
  auto sampler = TupleSampler<Args...>{};

  for(auto i = 0; i < example_limit_; ++i) {
    auto args = sampler.sample(dists);
    auto f_result = return_t{std::apply(f_, args)};
    auto g_result = std::apply(g_, args);
    
    if(f_result != g_result) {
      return {{f_result, g_result, args}};
    }
  }

  return {};
}
