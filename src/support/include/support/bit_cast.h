#pragma once

#include <algorithm>
#include <cstring>

namespace support {

template <class To, class From>
typename std::enable_if<std::is_trivially_copyable<From>::value
        && std::is_trivial<To>::value,
    To>::type
bit_cast(const From& src) noexcept
{
  auto dst = To(0);
  constexpr auto size = std::min(sizeof(To), sizeof(From));
  std::memcpy(&dst, &src, size);
  return dst;
}

} // namespace support
