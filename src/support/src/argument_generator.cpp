#include <support/argument_generator.h>
#include <support/random.h>

using namespace props;

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
  strategy_->gen_args(build);
}

// Uniform generator implementation

uniform_generator::uniform_generator(std::random_device::result_type seed)
    : engine_(seed)
    , size_(max_size)
{
}

uniform_generator::uniform_generator()
    : uniform_generator(get_random_device()())
{
}

void uniform_generator::gen_args(call_builder& build)
{
  auto const& sig = build.signature();
  for (auto p : sig.parameters) {
    if (p.pointer_depth > 1) {
      throw std::runtime_error("No nested pointers");
    }

    if (p.pointer_depth == 0) {
      if (p.type == data_type::integer) {
        build.add(gen_single<int>());
      } else if (p.type == data_type::floating) {
        build.add(gen_single<float>());
      } else {
        throw std::runtime_error("Unknown data_type");
      }
    } else {
      if (p.type == data_type::integer) {
        build.add(gen_array<int>());
      } else if (p.type == data_type::floating) {
        build.add(gen_array<float>());
      } else {
        throw std::runtime_error("Unknown data_type");
      }
    }
  }
}

template <>
int uniform_generator::gen_single<int>()
{
  return std::uniform_int_distribution<int>()(engine_);
}

template <>
float uniform_generator::gen_single<float>()
{
  return std::uniform_real_distribution<float>()(engine_);
}
}
