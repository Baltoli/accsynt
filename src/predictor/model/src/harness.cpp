#include "internal.h"

#include <model/model.h>

#include <props/props.h>

#include <fmt/format.h>

namespace model {

props::property_set predict(props::property_set ps)
{
  ps.properties.clear();

  fmt::print("{}\n", ps);

  return ps;
}

}
