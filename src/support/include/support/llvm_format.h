#pragma once

#include <support/string.h>

#include <fmt/format.h>

#include <llvm/Support/raw_ostream.h>

#include <type_traits>

namespace support::detail {

/**
 * SFINAE helper to detect any type that can be converted to an llvm Value.
 */
template <typename T>
using is_value = std::enable_if_t<std::is_convertible_v<T, llvm::Value*>>;
}

/**
 * Fully specialised formatter that is enabled for any type that can be
 * converted to an llvm value using SFINAE.
 */
template <typename T, typename Char>
struct fmt::formatter<T, Char, support::detail::is_value<T>> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(T v, FormatContext& ctx)
  {
    auto str = std::string{};
    auto os = llvm::raw_string_ostream(str);

    os << *v;
    return format_to(ctx.out(), "{}", support::left_trim(str));
  }
};
