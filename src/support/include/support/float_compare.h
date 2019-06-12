#pragma once

#include <support/type_finder.h>

#include <cmath>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace support {

namespace detail {

// TODO: do a memcpy version of this rather than relying on unions
template <typename Floating>
struct equality_wrapper {
private:
  using int_t = int_of_equal_size_t<Floating>;

  union punned {
    Floating as_float;
    int_t as_int;
  };

  punned value_;

public:
  equality_wrapper(Floating val) { value_.as_float = val; }

  bool is_negative() const { return value_.as_int < 0; }

  int_t as_int() const { return value_.as_int; }
};

} // namespace detail

template <typename Float>
bool ulp_equal(Float A, Float B, int max_ulp_diff)
{
  auto a_wrap = detail::equality_wrapper(A);
  auto b_wrap = detail::equality_wrapper(B);

  if (a_wrap.is_negative() != b_wrap.is_negative()) {
    if (A == B) {
      return true;
    }
    return false;
  }

  auto ulps_diff = std::abs(a_wrap.as_int() - b_wrap.as_int());
  return ulps_diff <= max_ulp_diff;
}

int ulp_diff(float A, float B);

template <typename T>
bool approx_equal(T&& a, T&& b)
{
  using ElemT = typename std::decay_t<T>::value_type;

  if constexpr (std::is_floating_point_v<ElemT>) {
    if (a.size() != b.size()) {
      return false;
    }

    for (auto i = 0u; i < a.size(); ++i) {
      auto approx = ulp_equal(a.at(i), b.at(i), 10)
          || std::abs(a.at(i) - b.at(i)) <= 0.001;
      if (!approx) {
        return false;
      }
    }

    return true;
  }

  return a == b;
}
} // namespace support
