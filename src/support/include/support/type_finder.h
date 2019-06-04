#pragma once

#include <cstdint>
#include <type_traits>

namespace support {

template <typename...>
struct int_type_finder;

template <typename FT>
struct int_type_finder<FT> {
  using type = void;
};

template <typename FT, typename IT, typename... ITs>
struct int_type_finder<FT, IT, ITs...> {
  using type = std::conditional_t<sizeof(FT) == sizeof(IT), IT,
      typename int_type_finder<FT, ITs...>::type>;
};

template <typename T>
struct int_of_equal_size {
  using type =
      typename int_type_finder<T, int8_t, int16_t, int32_t, int64_t>::type;
};

template <typename T>
using int_of_equal_size_t = typename int_of_equal_size<T>::type;

} // namespace support
