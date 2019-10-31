#include <support/float_compare.h>

namespace support {

int ulp_diff(float A, float B)
{
  auto a_wrap = detail::equality_wrapper(A);
  auto b_wrap = detail::equality_wrapper(B);

  return std::abs(a_wrap.as_int() - b_wrap.as_int());
}
} // namespace support
