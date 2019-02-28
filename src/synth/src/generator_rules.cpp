#include "generator_rules.h"

using namespace props;
using namespace support;

namespace synth {

argument_generator generator_for(property_set ps)
{
  for (auto prop : ps.properties) {
    if (prop.name == "generator") {
    }
  }

  return generator_named("uniform");
}

argument_generator generator_named(std::string const& name)
{
  if (name == "uniform") {
    return uniform_generator();
  }

  throw std::runtime_error("No such named generator");
}
}
