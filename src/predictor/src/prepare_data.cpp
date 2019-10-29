#include "prepare_data.h"

#include <algorithm>

using namespace props;

namespace predict {

void summary::update(property_set ps)
{
  params_ = std::max(params_, ps.type_signature.parameters.size());
  num_props_ = std::max(num_props_, ps.properties.size());
  
  for(auto const& prop : ps.properties) {
    prop_names_.insert(prop.name);
    prop_arity_ = std::max(prop_arity_, prop.values.size());
  }
}

summary::report summary::get() const
{
  return { params_, prop_names_.size(), num_props_, prop_arity_ };
}

}
