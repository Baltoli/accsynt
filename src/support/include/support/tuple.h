#pragma once

namespace {

/**
 * These functions are implementation details for the tuple iteration methods
 * below. They are taken from:
 *
 * https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/
 */
template <std::size_t... Idx>
auto make_index_dispatcher(std::index_sequence<Idx...>) {
    return [] (auto&& f) { (f(std::integral_constant<std::size_t,Idx>{}), ...); };
}

template <std::size_t N>
auto make_index_dispatcher() {
    return make_index_dispatcher(std::make_index_sequence<N>{}); 
}

}

namespace support {

/**
 * \brief Iterate over each item in a tuple.
 *
 * The callable \p f is called for each element of \p t, which can be any type
 * that supports \p std::get and \p std::tuple_size.
 */
template <typename Tuple, typename Func>
void for_each(Tuple&& t, Func&& f) {
  constexpr auto n = std::tuple_size_v<std::decay_t<Tuple>>;
  auto dispatcher = ::make_index_dispatcher<n>();

  dispatcher([&f,&t](auto idx) {
    f(std::get<idx>(std::forward<Tuple>(t)));
  });
}

template <typename Tuple, typename Func>
void index_for_each(Tuple&& t, Func&& f) {
  constexpr auto n = std::tuple_size_v<std::decay_t<Tuple>>;
  auto dispatcher = ::make_index_dispatcher<n>();

  dispatcher([&f,&t](auto idx) {
    f(std::get<idx>(std::forward<Tuple>(t)), idx);
  });
}

/**
 * \brief Iterate over two zipped tuples.
 *
 * The callable \p f is called with two arguments, one from each tuple. The
 * types \p Tuple1 and \p Tuple2 must both support \p std::get and \p
 * std::tuple_size. The size of \p Tuple1 must be less than or equal to the size
 * of \p Tuple2.
 */
template <typename Tuple1, typename Tuple2, typename Func>
void zip_for_each(Tuple1&& t1, Tuple2&& t2, Func&& f) {
  constexpr auto a1_size = std::tuple_size_v<std::decay_t<Tuple1>>;
  constexpr auto a2_size = std::tuple_size_v<std::decay_t<Tuple2>>;

  static_assert(a1_size <= a2_size, "Second argument tuple is too small");

  constexpr auto n = std::tuple_size_v<std::decay_t<Tuple1>>;
  auto dispatcher = ::make_index_dispatcher<n>();

  dispatcher([&f,&t1,&t2](auto idx) {
    f(std::get<idx>(std::forward<Tuple1>(t1)), 
      std::get<idx>(std::forward<Tuple2>(t2))); 
  });
}

}
