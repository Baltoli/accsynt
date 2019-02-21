#pragma once

#include <interfind/interfind.h>

#include <fmt/format.h>

template <>
struct fmt::formatter<interfind::region> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const interfind::region& region, FormatContext& ctx)
  {
    return format_to(ctx.out(), nlohmann::json(region).dump(2));
  }
};

template <>
struct fmt::formatter<interfind::analysis_result> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(interfind::analysis_result const& ar, FormatContext& ctx)
  {
    auto js = nlohmann::json(ar);
    return format_to(ctx.out(), "{}\n", js.dump(2));
  }
};
