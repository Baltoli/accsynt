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

constexpr auto reset = detail::specifier<0>();
constexpr auto bold = detail::specifier<1>();

} // namespace support::terminal
