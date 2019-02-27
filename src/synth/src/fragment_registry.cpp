#include "rules.h"

#include "regular_loop_fragment.h"

using namespace props;
using namespace support;

namespace synth {

value_ptr<fragment> fragment_registry::get(
    std::string const& name, std::vector<value> args)
{
  if (name == "regularLoop") {
    return make_value<regular_loop_fragment>(args);
  }

  if (name == "outputLoop") {
    return make_value<regular_loop_fragment>(args, true);
  }

  return nullptr;
}
}
