#include <support/random.h>

namespace support {

std::random_device& get_random_device()
{
  static std::random_device rd{};
  return rd;
}

std::mt19937 get_random_engine() { return std::mt19937(get_random_device()()); }

} // namespace support
