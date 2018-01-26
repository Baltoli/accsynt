#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

#include <functional>
#include <tuple>
#include <type_traits>

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<T, decltype(std::tuple_size<T>::value, void())> : std::true_type {};

template<typename I>
llvm::IntegerType *get_llvm_int(llvm::LLVMContext& c) {
  static_assert(std::is_integral_v<I>, "Integral value required");
  return llvm::IntegerType::get(c, sizeof(I)*8);
}

/**
 * Tuple for each implementation
 */
namespace detail {
  template<int... Is>
  struct seq { };

  template<int N, int... Is>
  struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

  template<int... Is>
  struct gen_seq<0, Is...> : seq<Is...> { };

  template<typename T, typename F, int... Is>
  void for_each(T&& t, F f, seq<Is...>)
  {
      auto l = { (f(std::get<Is>(t)), 0)... };
  }
}

template<typename... Ts, typename F>
void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
{
    detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
}
