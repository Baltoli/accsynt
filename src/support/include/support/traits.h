#pragma once

#include <algorithm>
#include <cstddef>
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

template <typename>
struct lazy_false : std::false_type {
};

template <typename T>
constexpr inline bool lazy_false_v = lazy_false<T>::value;

template <typename, typename = std::void_t<>>
struct has_member_find : std::false_type {
};

template <typename T>
struct has_member_find<T,
    std::void_t<decltype(
        std::declval<T>().find(
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
    return std::find(begin(std::forward<decltype(c)>(c)),
        end(std::forward<decltype(c)>(c)),
        key);
  }
}
}

#define static_fail(str) static_assert(support::lazy_false_v<void>, str)

#define FWD(x) std::forward<decltype(x)>(x)
