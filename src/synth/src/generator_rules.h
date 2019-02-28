#pragma once

#include <props/props.h>
#include <support/argument_generator.h>

namespace synth {

support::argument_generator generator_for(props::property_set ps);
support::argument_generator generator_named(std::string const& name);
}
