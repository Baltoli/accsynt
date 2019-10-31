#include "internal.h"

#include <model/model.h>

#include <props/props.h>

#include <fmt/format.h>

namespace model {

int prop_category(std::string const& str)
{
  return map_name(str.c_str());
}

props::property_set predict(props::property_set ps)
{
  ps.properties.clear();

  fmt::print("{}\n", ps);

  return ps;
}

}
