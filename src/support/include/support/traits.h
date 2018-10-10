#pragma once

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
struct lazy_false : std::false_type {};

template <typename T>
constexpr inline bool lazy_false_v = lazy_false<T>::value;

}

#define static_fail(str) static_assert(support::lazy_false_v<void>, str)
