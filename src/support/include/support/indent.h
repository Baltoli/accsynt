#pragma once

#include <fmt/format.h>

namespace support {

struct indent {
  size_t depth = 0;
};
} // namespace support

namespace fmt {

template <>
struct formatter<support::indent> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const support::indent& ind, FormatContext& ctx)
  {
    auto it = ctx.begin();
    for (auto i = 0u; i < ind.depth; ++i) {
      it = format_to(it, "  ");
    }
    return it;
  }
};
} // namespace fmt
