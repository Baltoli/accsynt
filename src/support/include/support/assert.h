#pragma once

#include <support/terminal.h>

#include <fmt/format.h>

#include <filesystem>

namespace support::detail {

#ifdef NDEBUG
static constexpr bool debug = false;
#else
static constexpr bool debug = true;
#endif

template <typename Cond, typename... Args>
void assert_impl(
    Cond&& cond, char const* check, char const* file, int line, Args... args)
{
  using namespace fmt::literals;
  namespace term = support::terminal;

  if constexpr (detail::debug) {
    if (!static_cast<bool>(cond)) {
      auto path = std::filesystem::path(file);
      fmt::print("Assertion {bad}{check}{reset} failed at:\n"
                 "  {bold}{file}:{line}{reset}\n",
          "bad"_a = term::f_red + term::bold, "reset"_a = term::reset,
          "bold"_a = term::bold, "check"_a = check,
          "file"_a = path.filename().string(), "line"_a = line);

      if constexpr (sizeof...(args) > 0) {
        fmt::print("\n{}\n", fmt::format(args...));
      }

      std::exit(1);
    }
  }
}

} // namespace support::detail

#define assertion(c, ...)                                                      \
  do {                                                                         \
    support::detail::assert_impl(c, #c, __FILE__, __LINE__, __VA_ARGS__);      \
  } while (false)
