#pragma once

#include <interfind/region.h>

#include <props/props.h>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

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

void to_json(nlohmann::json& j, analysis_result const& ar);

}
