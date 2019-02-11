#pragma once

#include <fmt/format.h>

namespace interfind {

class analysis_result {
public:
private:
};

}

template <>
struct fmt::formatter<interfind::analysis_result> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const interfind::analysis_result& ar, FormatContext& ctx)
  {
    return format_to(ctx.out(), "ANALYSIS");
  }
};
