#include <interfind/analysis.h>
#include <interfind/format.h>
#include <interfind/region.h>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace interfind {

void to_json(json& j, region const& r)
{
  auto ins = std::vector<std::string>{};
  auto beg = r.inputs().begin();
  auto end = r.inputs().end();
  auto back = std::back_inserter(ins);

  std::transform(beg, end, back, [](auto in) {
    return fmt::format("{}", in);
  });

  j = {
    { "output", fmt::format("{}", r.output()) },
    { "inputs", ins }
  };
}

void to_json(json& j, analysis_result const& ar)
{
  j = {
    { "signature", fmt::format("{}", ar.signature()) },
    { "regions", ar.regions() }
  };
}
}
