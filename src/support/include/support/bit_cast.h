#pragma once

#include <cstring>

namespace support {

template <class To, class From>
typename std::enable_if<(sizeof(To) == sizeof(From))
        && std::is_trivially_copyable<From>::value
        && std::is_trivial<To>::value,
    To>::type
bit_cast(const From& src) noexcept
{
  To dst;
  std::memcpy(&dst, &src, sizeof(To));
  return dst;
}

} // namespace support
