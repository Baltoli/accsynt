#pragma once

#include <synth/types.h>

#include <functional>
#include <optional>

/**
 * An example just aggregates an input-output pair, whatever their types and the
 * size of the output are.
 */
template<class R, class... Args>
struct Example {
  std::tuple<Args...> input;
  R output;
};

/**
 * A query response can be either an example or nothing at all, so we model them
 * using an optional.
 */
template<class R, class... Args>
using Response = std::optional<Example<R, Args...>>;

/**
 * An oracle conceptually "wraps" an accelerator's interface and provides a set
 * of operations that can be accessed using a uniform interface.
 *
 * Currently, the only supported interaction model with an oracle is as if the
 * interface is a function call.
 */
template<class R, class... Args>
class Oracle {
public:
  using interface_t = std::function<R(Args...)>;

  Oracle(interface_t i) :
    interface_(i) {}

  bool member(R out, Args... in);

  template<
    class Gen, 
    typename std::enable_if_t<is_tuple<typename Gen::return_t>::value, int> = 0
  >
  Response<R, Args...> positive(Gen& g);

  template<
    class Gen, 
    typename std::enable_if_t<!is_tuple<typename Gen::return_t>::value, int> = 0
  >
  Response<R, Args...> positive(Gen& g);
private:
  interface_t interface_;
};

template<class R, class... Args>
bool Oracle<R, Args...>::member(R out, Args... in)
{
  return interface_(in...) == out;
}

template<class R, class... Args>
template<
  class Gen, 
  typename std::enable_if_t<is_tuple<typename Gen::return_t>::value, int>
>
Response<R, Args...> Oracle<R, Args...>::positive(Gen& g)
{
  auto in = g();
  return {{
    in, std::apply([&](auto&&... x)
      { return interface_(x...); }, in
    )
  }};
}

template<class R, class... Args>
template<
  class Gen, 
  typename std::enable_if_t<!is_tuple<typename Gen::return_t>::value, int>
>
Response<R, Args...> Oracle<R, Args...>::positive(Gen& g)
{
  auto in = g();
  return {in, interface_(in)};
}
