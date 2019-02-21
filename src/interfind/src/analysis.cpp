#include <interfind/analysis.h>

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace interfind {

analysis_result::analysis_result(props::signature sig) :
  signature_(sig), regions_{}
{
}

props::signature const& analysis_result::signature() const
{
  return signature_;
}

void analysis_result::add_candidate_region(region r)
{
  regions_.push_back(r);
}

std::vector<region> const& analysis_result::regions() const
{
  return regions_;
}

void to_json(json& j, analysis_result const& ar)
{
  j = {
    { "signature", fmt::format("{}", ar.signature()) },
    { "regions", ar.regions() }
  };
}

}
