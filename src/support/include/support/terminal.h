#pragma once

#include <fmt/format.h>

#include <array>

/**
 * This file implements a mechanism for printing terminal escape sequences that
 * change how text is displayed in the terminal. By combining different codes
 * it's possible to get lots of different text appearances.
 */

namespace support::terminal {

namespace detail {

template <int... Cs>
struct specifier {
  constexpr explicit specifier()
      : codes_ { Cs... }
  {
  }

  template <int... OCs>
  constexpr auto operator+(specifier<OCs...> other) const
  {
    return specifier<Cs..., OCs...>();
  }

  std::array<int, sizeof...(Cs)> codes_;
};

} // namespace detail

// Codes taken from
// https://stackoverflow.com/a/33206814
// (not a complete selection of features in this implementation)

constexpr inline auto reset = detail::specifier<0>();
constexpr inline auto bold = detail::specifier<1>();
constexpr inline auto underline = detail::specifier<4>();
constexpr inline auto reverse = detail::specifier<7>();
constexpr inline auto strike = detail::specifier<9>();

constexpr inline auto f_black = detail::specifier<30>();
constexpr inline auto f_red = detail::specifier<31>();
constexpr inline auto f_green = detail::specifier<32>();
constexpr inline auto f_yellow = detail::specifier<33>();
constexpr inline auto f_blue = detail::specifier<34>();
constexpr inline auto f_pink = detail::specifier<35>();
constexpr inline auto f_cyan = detail::specifier<36>();
constexpr inline auto f_white = detail::specifier<37>();
constexpr inline auto f_default = detail::specifier<39>();

constexpr inline auto b_black = detail::specifier<40>();
constexpr inline auto b_red = detail::specifier<41>();
constexpr inline auto b_green = detail::specifier<42>();
constexpr inline auto b_yellow = detail::specifier<43>();
constexpr inline auto b_blue = detail::specifier<44>();
constexpr inline auto b_pink = detail::specifier<45>();
constexpr inline auto b_cyan = detail::specifier<46>();
constexpr inline auto b_white = detail::specifier<47>();
constexpr inline auto b_default = detail::specifier<49>();

} // namespace support::terminal

template <int... Cs>
struct fmt::formatter<support::terminal::detail::specifier<Cs...>> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(support::terminal::detail::specifier<Cs...> const& spec,
      FormatContext& ctx)
  {
    return fmt::format_to(ctx.out(), "\033[{}m", fmt::join(spec.codes_, ";"));
  }
};
