#include "rules.h"

#include "regular_loop_fragment.h"

using namespace props;

namespace synth {

std::unique_ptr<fragment> fragment_registry::get(
    std::string const& name, 
    std::vector<value> args)
{
  if(name == "regularLoop") {
    return std::make_unique<regular_loop_fragment>(args);
  }

  if(name == "outputLoop") {
    return std::make_unique<regular_loop_fragment>(args, true);
  }

  return nullptr;
}

}
