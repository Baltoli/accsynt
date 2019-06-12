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

  // This convoluted code is needed to reverse the zero-extension / casting done
  // by the LLVM callable wrapper, where the high-order bits in returned values
  // are zeroed and the result is written into the low-order bits.
  //
  // See `make_return` in `call_wrapper.h` to understand why we need this code
  // in both directions.
  //
  // I've verified on compiler explorer that doing this with constexpr means
  // that minimal assembly is generated (mostly just shifts / truncations where
  // needed) to handle the extra work.
  //
  // The conversions are tested extensively using random data.
  //
  // Really bit_cast isn't the best name for this as it's a twisted version of
  // the C++20 version, but it'll do for now.
  if constexpr (sizeof(To) > sizeof(From)) {
    // In this case we're putting a small value into a big one, so we offset the
    // destination by the difference in size.
    constexpr auto d_offset = sizeof(To) - sizeof(From);
    auto dst_off = reinterpret_cast<char*>(&dst) + d_offset;
    std::memcpy(dst_off, &src, sizeof(From));
  } else if constexpr (sizeof(From) > sizeof(To)) {
    // Similarly, here we're casting a bigger value into a smaller one, so we
    // offset the source to ignore the high bits.
    constexpr auto s_offset = sizeof(From) - sizeof(To);
    auto src_off = reinterpret_cast<char const*>(&src) + s_offset;
    std::memcpy(&dst, src_off, sizeof(To));
  } else {
    // Standard version
    std::memcpy(&dst, &src, sizeof(To));
  }

  return dst;
}

} // namespace support
