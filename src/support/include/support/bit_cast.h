#pragma once

#include <cstring>

namespace support {

template <class To, class From>
typename std::enable_if<std::is_trivially_copyable<From>::value
        && std::is_trivial<To>::value,
    To>::type
bit_cast(const From& src) noexcept
{
  auto dst = To(0);

  if constexpr (sizeof(To) > sizeof(From)) {
    constexpr auto d_offset = sizeof(To) - sizeof(From);
    auto dst_off = reinterpret_cast<char*>(&dst) + d_offset;
    std::memcpy(dst_off, &src, sizeof(From));
  } else if constexpr (sizeof(From) > sizeof(To)) {
    constexpr auto s_offset = sizeof(From) - sizeof(To);
    auto src_off = reinterpret_cast<char const*>(&src) + s_offset;
    std::memcpy(&dst, src_off, sizeof(To));
  } else {
    std::memcpy(&dst, &src, sizeof(To));
  }

  return dst;
}

} // namespace support
