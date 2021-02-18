#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <type_traits>

namespace support {

template <typename T>
struct pointer_depth {
  static constexpr size_t value = 0;
};

template <typename T>
struct pointer_depth<T*> {
  static constexpr size_t value = pointer_depth<T>::value + 1;
};

template <typename T>
constexpr inline size_t pointer_depth_v = pointer_depth<T>::value;

template <typename...>
constexpr inline bool false_v = false;

template <typename, typename = std::void_t<>>
struct has_member_find : std::false_type {
};

template <typename T>
struct has_member_find<
    T, std::void_t<decltype(std::declval<T>().find(
           std::declval<typename T::key_type>()))>> : std::true_type {
};

template <typename T>
constexpr inline bool has_member_find_v = has_member_find<T>::value;

template <typename Container, typename Key>
decltype(auto) container_find(Container&& c, Key const& key)
{
  using std::begin;
  using std::end;

  if constexpr (has_member_find_v<Container>) {
    return std::forward<decltype(c)>(c).find(key);
  } else {
    return std::find(
        begin(std::forward<decltype(c)>(c)), end(std::forward<decltype(c)>(c)),
        key);
  }
}

template <class T, std::size_t = sizeof(T)>
std::true_type is_complete_impl(T*);

std::false_type is_complete_impl(...);

template <class T>
using is_complete = decltype(is_complete_impl(std::declval<T*>()));

template <typename T>
constexpr inline bool is_complete_v = is_complete<T>::value;

template <template <typename...> class Template, typename... Ts>
constexpr inline bool is_specialized_v = is_complete_v<Template<Ts...>>;

template <typename T>
struct is_unique_ptr : std::false_type {
};

template <typename T>
struct is_unique_ptr<std::unique_ptr<T>> : std::true_type {
};

template <typename T>
constexpr bool is_unique_ptr_v = is_unique_ptr<T>::value;

template <typename T>
struct is_buildable_int {
  static constexpr bool value
      = std::is_integral_v<T> && sizeof(T) == sizeof(int64_t);
};

template <typename T>
constexpr bool is_buildable_int_v = is_buildable_int<T>::value;

template <typename T, typename... Ts>
struct are_same : std::conjunction<std::is_same<T, Ts>...> {
};

template <typename T, typename... Ts>
constexpr inline bool are_same_v = are_same<T, Ts...>::value;

template <typename T, typename... Ts>
struct is_any : std::disjunction<std::is_same<T, Ts>...> {
};

template <typename T, typename... Ts>
constexpr inline bool is_any_v = is_any<T, Ts...>::value;

} // namespace support
