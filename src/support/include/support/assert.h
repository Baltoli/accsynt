#pragma once

#include <support/filesystem.h>
#include <support/llvm_format.h>
#include <support/terminal.h>

#include <fmt/format.h>

#include <cstdlib>

namespace support {

namespace detail {

inline constexpr void assert_fail() { }

#ifdef NDEBUG
static constexpr bool debug = false;
#else
static constexpr bool debug = true;
#endif

template <typename Cond, typename... Args>
void assert_impl(
    Cond&& cond, char const* check, char const* type, char const* file,
    int line, char const* func, Args&&... args)
{
  using namespace fmt::literals;
  namespace term = support::terminal;

  auto result = std::forward<Cond>(cond)();
  if (!result) {
    assert_fail();

    if constexpr (detail::debug) {
      auto path = filesystem::path(file);
      fmt::print(
          "{type}{bad}{check}{reset} at:\n"
          "  {bold}{file}:{line} ({func}){reset}\n",
          "bad"_a = term::f_red + term::bold, "reset"_a = term::reset,
          "bold"_a = term::bold, "check"_a = check,
          "file"_a = path.filename().string(), "line"_a = line, "type"_a = type,
          "func"_a = func);

      if constexpr (sizeof...(args) > 0) {
        fmt::print("  {}\n", fmt::format(std::forward<Args>(args)...));
      }

      std::exit(1);
    } else {
      std::abort();
    }
  }
}

} // namespace detail

template <typename Func>
void in_debug(Func&& f)
{
  if constexpr (detail::debug) {
    std::forward<Func>(f)();
  }
}

} // namespace support

#define ASSERT_LAZY_ARG(x) [&] { return static_cast<bool>(x); }

#define assertion(c, ...)                                                      \
  do {                                                                         \
    ::support::detail::assert_impl(                                            \
        ASSERT_LAZY_ARG(c), #c, "Assertion failure: ", __FILE__, __LINE__,     \
        __func__, __VA_ARGS__);                                                \
  } while (false)

#define assumes(c, ...)                                                        \
  do {                                                                         \
    ::support::detail::assert_impl(                                            \
        ASSERT_LAZY_ARG(c), #c, "Precondition violated: ", __FILE__, __LINE__, \
        __func__, __VA_ARGS__);                                                \
  } while (false)

#define ensures(c, ...)                                                        \
  do {                                                                         \
    ::support::detail::assert_impl(                                            \
        ASSERT_LAZY_ARG(c), #c, "Postcondition violated: ", __FILE__,          \
        __LINE__, __func__, __VA_ARGS__);                                      \
  } while (false)

#define unimplemented()                                                        \
  do {                                                                         \
    ::support::detail::assert_impl(                                            \
        ASSERT_LAZY_ARG(false), "", "Unimplemented code reached", __FILE__,    \
        __LINE__, __func__);                                                   \
    __builtin_unreachable();                                                   \
  } while (false)

#define invalid_state()                                                        \
  do {                                                                         \
    ::support::detail::assert_impl(                                            \
        ASSERT_LAZY_ARG(false), "", "Invalid state reached", __FILE__,         \
        __LINE__, __func__);                                                   \
    __builtin_unreachable();                                                   \
  } while (false)
