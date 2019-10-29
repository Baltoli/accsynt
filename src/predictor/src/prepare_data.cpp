#include "prepare_data.h"

#include <algorithm>

using namespace props;

namespace predict {

std::string example::dump_input() const
{
  return "in";
}

std::string example::dump_output() const
{
  return "out";
}

summary::summary(props::property_set const& ps)
{
  update(ps);
}

void summary::update(property_set const &ps)
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

int summary::encode(base_type bt) const
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
  
int summary::encode(std::string const& pn) const
{
  auto found = prop_names_.find(pn);
  return std::distance(prop_names_.begin(), found);
}

example summary::encode(props::property_set const& ps) const
{
  auto ret = example{};
  auto [params, names, props, arity] = get();

  if(auto dt = ps.type_signature.return_type) {
    ret.input.push_back(encode(dt->base));
    ret.input.push_back(dt->pointers);
  } else {
    ret.input.push_back(0);
    ret.input.push_back(0);
  }

  for(auto const& param : ps.type_signature.parameters) {
    ret.input.push_back(encode(param.type));
    ret.input.push_back(param.pointer_depth);
  }

  auto params_pad = params - ps.type_signature.parameters.size();
  for(auto i = 0; i < params_pad; ++i) {
    ret.input.push_back(-1);
    ret.input.push_back(-1);
  }

  for(auto const& prop : ps.properties) {
    ret.output.push_back(encode(prop.name));

    for(auto const& val : prop.values) {
      ret.output.push_back(ps.type_signature.param_index(val.param_val));
    }

    auto values_pad = arity - prop.values.size();
    for(auto i = 0; i < values_pad; ++i) {
      ret.output.push_back(-1);
    }
  }

  auto props_pad = props - ps.properties.size();
  for(auto i = 0; i < props_pad; ++i) {
    for(auto j = 0; j < arity + 1; ++j) {
      ret.output.push_back(-1);
    }
  }

  return ret;
}

props::property_set summary::decode(example const&) const
{
  return {};
}

}
