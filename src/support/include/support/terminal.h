#pragma once

#include <algorithm>
#include <array>
#include <tuple>

/**
 * This file implements a mechanism for printing terminal escape sequences that
 * change how text is displayed in the terminal. By combining different codes
 * it's possible to get lots of different text appearances.
 */

namespace support::terminal {

namespace detail {

template <int... vals>
struct specifier {
  constexpr explicit specifier()
      : codes_ { vals... }
  {
  }

  template <int... OCs>
  constexpr auto operator+(specifier<OCs...> other) const;

  std::array<int, sizeof...(vals)> codes_;
};

// Combining specifiers and specifiers

template <int... Cs>
template <int... OCs>
constexpr auto specifier<Cs...>::operator+(specifier<OCs...> other) const
{
  return specifier<Cs..., OCs...>();
}

} // namespace detail

constexpr auto reset = detail::specifier<0>();
constexpr auto bold = detail::specifier<1>();

} // namespace support::terminal
