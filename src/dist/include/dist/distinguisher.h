#pragma once

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

namespace v2 {

template <typename R, typename Args>
struct Counterexample {
  const R f_return;
  const R g_return;
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

    for(auto i = 0; i < example_limit_; ++i) {
      auto example = gen();
      auto f_result = std::apply(f_, example);
      auto g_result = return_t{std::apply(g_, example)};

      if(f_result != g_result) {
        return {{f_result, g_result, example}};
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

}
