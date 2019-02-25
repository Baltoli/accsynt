#include <support/argument_generator.h>
#include <support/random.h>

namespace support {

// Wrapper methods
argument_generator::argument_generator(argument_generator& other)
    : strategy_(other.strategy_->clone())
{
}

argument_generator& argument_generator::operator=(argument_generator other)
{
  using std::swap;
  swap(*this, other);
  return *this;
}

void swap(argument_generator& a, argument_generator& b)
{
  using std::swap;
  swap(a.strategy_, b.strategy_);
}

void argument_generator::gen_args(call_builder& build)
{
  /* build.reset(); */
  /* auto const& sig = build.signature(); */

  /* for (auto const& param : sig.parameters) { */
  /*   if (param.pointer_depth > 0) { */
  /*     throw std::runtime_error( */
  /*         "Can't generate pointers with new interface yet"); */
  /*   } */

  /*   if (param.type == props::data_type::integer) { */
  /*     build.add(gen_int()); */
  /*   } else if (param.type == props::data_type::floating) { */
  /*     build.add(gen_float()); */
  /*   } else { */
  /*     throw std::runtime_error("Unknown data type"); */
  /*   } */
  /* } */
}

// Uniform generator implementation
uniform_generator::uniform_generator()
    : engine_(get_random_device()())
{
}

uniform_generator::uniform_generator(std::random_device::result_type seed)
    : engine_(seed)
{
}
}
