#pragma once

namespace support::detail {

#ifdef NDEBUG
static constexpr bool debug = false;
#else
static constexpr bool debug = true;
#endif

void assert_impl(bool cond)
{
  if constexpr (detail::debug) {
    if (!cond) {
      std::exit(1);
    }
  }
}

} // namespace support::detail

#define assertion(...)                                                         \
  do {                                                                         \
    support::detail::assert_impl(__VA_ARGS__);                                 \
  } while (false)
