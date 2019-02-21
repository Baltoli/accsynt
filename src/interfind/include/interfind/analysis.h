#pragma once

#include <interfind/region.h>

#include <props/props.h>

#include <fmt/format.h>

#include <vector>

namespace interfind {

/**
 * Represents the result of an InterFind analysis being run on a module. The
 * details currently being reported are:
 *
 * - The type signature (and therefore library function name) being analysed.
 * - A list of potential regions found by the analysis.
 */
class analysis_result {
public:
  analysis_result(props::signature);

  props::signature const& signature() const;

  void add_candidate_region(region);
  std::vector<region> const& regions() const;

private:
  props::signature signature_;
  std::vector<region> regions_;
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
