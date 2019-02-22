#include <interfind/analysis.h>

namespace interfind {

analysis_result::analysis_result(props::signature sig)
    : signature_(sig)
    , regions_{}
{
}

props::signature const& analysis_result::signature() const
{
  return signature_;
}

void analysis_result::add_candidate_region(region r) { regions_.push_back(r); }

std::vector<region> const& analysis_result::regions() const { return regions_; }
}
