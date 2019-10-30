#include "prepare_data.h"

#include <fmt/format.h>

#include <llvm/Support/Commandline.h>

#include <algorithm>

using namespace llvm;
using namespace props;

namespace predict {

dataset::dataset(props::property_set const& ps)
{
  update(ps);
}

void dataset::update(property_set const &ps)
{
  /* params_ = std::max(params_, ps.type_signature.parameters.size()); */
  /* num_props_ = std::max(num_props_, ps.properties.size()); */
  
  /* for(auto const& prop : ps.properties) { */
  /*   prop_names_.insert(prop.name); */
  /*   prop_arity_ = std::max(prop_arity_, prop.values.size()); */
  /* } */
}

int dataset::encode(base_type bt) const
{
  switch(bt) {
    case base_type::character:
      return 1;
    case base_type::boolean:
      return 2;
    case base_type::integer:
      return 3;
    case base_type::floating:
      return 4;
  }

  return 0;
}
  
int dataset::encode(std::string const& pn) const
{
  auto found = prop_names_.find(pn);
  return std::distance(prop_names_.begin(), found);
}

}
