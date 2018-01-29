#pragma once

#include <array>
#include <string>
#include <optional>
#include <random>
#include <vector>

template<class... Args>
class TupleSampler {
public:
  template<class... Ds>
  std::tuple<Args...> sample(Ds... ds);

private:
  std::random_device rd;
  std::default_random_engine engine;
};

template<class... Args>
template<class... Ds>
std::tuple<Args...> TupleSampler<Args...>::sample(Ds... ds)
{
  static_assert(sizeof...(Args) == sizeof...(Ds), "Each argument needs a distribution");

  auto ret = std::tuple<Args...>{};
  for_each(ret, std::tuple<Ds...>(ds...), [this](auto& t, auto& d) {
    t = d(engine);
  });
  return ret;
}

template<class F, class G, class... Args>
class OracleDistinguisher {
public:
  using return_t = std::invoke_result<G, Args...>;

  OracleDistinguisher(F&& f, G&& g, size_t limit=10000) :
    example_limit_(limit)
  {
    static_assert(std::is_convertible_v<
      std::invoke_result<F, Args...>, // from
      std::invoke_result<G, Args...>  // to
    >, "f and g must yield the same result type");
  }

  std::optional<std::tuple<Args...>> operator()() const;

private:
  size_t example_limit_;
};

template<class... Args>
auto make_oracle_distinguisher(auto&& f, auto&& g)
{
  return OracleDistinguisher<decltype(f), decltype(g), Args...>(f, g);
}
