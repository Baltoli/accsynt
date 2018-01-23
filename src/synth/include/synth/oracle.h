#ifndef ORACLE_H
#define ORACLE_H

#include <functional>
#include <type_traits>

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<T, decltype(std::tuple_size<T>::value, void())> : std::true_type {};

template<class R, class... Args>
struct Example {
  std::tuple<Args...> input;
  R output;
};

/**
 * An oracle conceptually "wraps" an accelerator's interface and provides a set
 * of operations that can be accessed using a uniform interface.
 *
 * Currently, the only supported interaction model with an oracle is as if the
 * interface is a function call.
 */
template<class R, class... Args>
struct Oracle {
  using interface_t = std::function<R(Args...)>;

  Oracle(interface_t i) :
    interface_(i) {}

  bool member(R out, Args... in);

  template<
    class Gen, 
    typename std::enable_if_t<is_tuple<typename Gen::return_t>::value, int> = 0
  >
  Example<R, Args...> positive(Gen& g);

  template<
    class Gen, 
    typename std::enable_if_t<!is_tuple<typename Gen::return_t>::value, int> = 0
  >
  Example<R, Args...> positive(Gen& g);
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
Example<R, Args...> Oracle<R, Args...>::positive(Gen& g)
{
  auto in = g();
  return {
    in,
    std::apply([&](auto&&... x)
      { return interface_(x...); },
      in
    )
  };
}

template<class R, class... Args>
template<
  class Gen, 
  typename std::enable_if_t<!is_tuple<typename Gen::return_t>::value, int>
>
Example<R, Args...> Oracle<R, Args...>::positive(Gen& g)
{
  auto in = g();
  return {in, interface_(in)};
}

#endif
