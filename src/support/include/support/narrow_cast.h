#pragma once

#include <utility>

namespace support {

template <typename To, typename From>
constexpr To narrow_cast(From&& from) noexcept
{
  return static_cast<To>(std::forward<From>(from));
}

} // namespace support
