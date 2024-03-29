#include <props/props.h>

#include <tuple>

namespace props {

bool param::compatible(param const& other) const
{
  return std::tie(type, pointer_depth)
         == std::tie(other.type, other.pointer_depth);
}

bool param::operator==(param const& other) const
{
  return std::tie(name, type, pointer_depth)
         == std::tie(other.name, other.type, other.pointer_depth);
}

bool param::operator!=(param const& other) const { return !(*this == other); }

bool signature::compatible(signature const& other) const
{
  if (parameters.size() != other.parameters.size()) {
    return false;
  }

  for (auto i = 0; i < parameters.size(); ++i) {
    if (!parameters[i].compatible(other.parameters[i])) {
      return false;
    }
  }

  return return_type == other.return_type;
}

bool signature::operator==(signature const& other) const
{
  return std::tie(return_type, name, parameters)
         == std::tie(other.return_type, other.name, other.parameters);
}

bool signature::operator!=(signature const& other) const
{
  return !(*this == other);
}
} // namespace props
