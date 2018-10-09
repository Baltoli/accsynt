#pragma once

#include <cstddef>

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

}
