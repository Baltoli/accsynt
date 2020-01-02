#pragma once

#include <fmt/format.h>

#include <filesystem>

namespace support::detail {

#ifdef NDEBUG
static constexpr bool debug = false;
#else
static constexpr bool debug = true;
#endif

template <typename... Args>
void assert_impl(bool cond, char const* file, int line, Args... args)
{
  if constexpr (detail::debug) {
    if (!cond) {
      auto path = std::filesystem::path(file);
      fmt::print("Assert: {}:{}\n", path.filename().string(), line);
      if constexpr (sizeof...(args) > 0) {
        fmt::print("{}\n", fmt::format(args...));
      }
      std::exit(1);
    }
  }
}

} // namespace support::detail

#define assertion(c, ...)                                                      \
  do {                                                                         \
    support::detail::assert_impl(c, __FILE__, __LINE__, __VA_ARGS__);          \
  } while (false)
