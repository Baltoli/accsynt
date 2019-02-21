#include <support/argument_generator.h>
#include <support/random.h>

namespace support {

// Wrapper methods
argument_generator::argument_generator(argument_generator& other) :
  strategy_(other.strategy_->clone())
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


// Uniform generator implementation
uniform_generator::uniform_generator() :
  engine_(get_random_device()())
{
}

uniform_generator::uniform_generator(std::random_device::result_type seed) :
  engine_(seed)
{
}

int uniform_generator::gen_int(int min, int max)
{
  return std::uniform_int_distribution<int>(min, max)(engine_);
}

float uniform_generator::gen_float(float min, float max)
{
  return std::uniform_real_distribution<float>(min, max)(engine_);
}

}
