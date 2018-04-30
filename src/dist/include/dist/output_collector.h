#pragma once

#include <dist/types.h>

namespace accsynt {

template <template <typename> class F, typename R, typename... Args>
class output_collector {
public:
  output_collector(R r, Args... args) :
    return_type_(r), arg_types_(args...)
  {
  }

  template <typename Tuple, size_t idx>
  auto collect_impl(Tuple&& t) {
    using Arg = std::tuple_element_t<idx, std::tuple<Args...>>;

    if constexpr(is_output_type<Arg>::value) {
      auto f = F<Arg>{};
      return std::make_tuple(f(std::get<idx>(arg_types_), std::get<idx>(std::forward<decltype(t)>(t))));
    } else {
      return std::make_tuple();
    }
  }

  template <typename Tuple, std::size_t... Is>
  auto collect_impl2(Tuple&& t, std::index_sequence<Is...>) {
    return std::tuple_cat(
      collect_impl<Tuple, Is>(std::forward<decltype(t)>(t))...
    );
  }

  template <typename RV, typename Tuple>
  auto collect(RV return_val, Tuple&& t) {
    auto ret = collect_impl2(std::forward<decltype(t)>(t), std::make_index_sequence<sizeof...(Args)>());
    if constexpr(std::is_same_v<R, Void>) {
      return ret;
    } else {
      auto f = F<R>{};
      return std::tuple_cat(std::tuple(f(return_type_, return_val)), ret);
    }
  }

  template <typename Tuple>
  auto collect(Tuple&& t) {
    return collect_impl2(std::forward<decltype(t)>(t), std::make_index_sequence<sizeof...(Args)>());
  }

private:
  R return_type_;
  std::tuple<Args...> arg_types_;
};

template <typename Type>
struct val_to_val {
  template <typename Arg>
  Arg operator()(Type, Arg a)
  {
    return a;
  }
};

template <typename F, typename R, typename... Args>
class CollectCallable {
public:
  using return_type = typename all_outputs<R, Args...>::type;

  CollectCallable(F const& f, R r, Args... args) :
    func_(f),
    return_type_(r), arg_types_(args...)
  {
  }

  return_type operator()(typename Args::example_t... args);
private:
  F const& func_;

  R return_type_;
  std::tuple<Args...> arg_types_;
};

template <typename F, typename R, typename... Args>
typename CollectCallable<F, R, Args...>::return_type
CollectCallable<F, R, Args...>::operator()(typename Args::example_t... args)
{
  auto collector = std::apply([&](auto&&... ats) {
    return output_collector<val_to_val, R, Args...>(return_type_, ats...);
  }, arg_types_);

  if constexpr(std::is_same_v<R, Void>) {
    func_(args...);
    return collector.collect(std::tuple(args...));
  } else {
    auto ret = func_(args...);
    return collector.collect(ret, std::tuple(args...));
  }
}

}
