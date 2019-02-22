#include <props/props.h>

#include <set>

namespace props {

size_t signature::param_index(std::string const& name) const
{
  size_t idx = 0;
  for (auto const& param : parameters) {
    if (param.name == name) {
      return idx;
    }
    ++idx;
  }

  throw std::runtime_error("Invalid name to get index for");
}

bool property_set::is_valid() const
{
  auto param_names = std::set<std::string_view>{};
  for (auto const& param : type_signature.parameters) {
    auto [iter, ins] = param_names.insert(param.name);
    if (!ins) {
      return false; // Non-unique parameter name
    }
  }

  for (auto const& prop : properties) {
    for (auto const& val : prop.values) {
      if (val.value_type == value::type::parameter) {
        auto found = param_names.find(val.param_val);
        if (found == param_names.end()) {
          return false;
        }
      }
    }
  }

  return true;
}

bool value::operator==(value const& other) const
{
  if (value_type != other.value_type) {
    return false;
  }

  switch (value_type) {
  case type::integer:
    return int_val == other.int_val;
  case type::floating:
    return float_val == other.float_val;
  case type::parameter:
    return param_val == other.param_val;
  case type::string:
    return string_val == other.string_val;
  }

  return false;
}

bool value::operator!=(value const& other) const { return !(*this == other); }
}
