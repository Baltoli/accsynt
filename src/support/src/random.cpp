#include <support/random.h>

namespace support {

std::random_device& get_random_device()
{
  static std::random_device rd{};
  return rd;
}
}
