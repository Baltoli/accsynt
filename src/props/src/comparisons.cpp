#include <props/props.h>

#include <tuple>

namespace props {

bool param::operator==(param const& other) const
{
  return std::tie(name, type, pointer_depth)
      == std::tie(other.name, other.type, other.pointer_depth);
}

bool param::operator!=(param const& other) const { return !(*this == other); }

bool signature::operator==(signature const& other) const
{
  return std::tie(return_type, name, parameters)
      == std::tie(other.return_type, other.name, other.parameters);
}

bool signature::operator!=(signature const& other) const
{
  return !(*this == other);
}
}
