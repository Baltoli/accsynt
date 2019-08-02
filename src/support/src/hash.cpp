#include <support/hash.h>

namespace support::detail {

std::array<char, 11> to_sextets(size_t n)
{
  // masks off all but the rightmost 6 bits
  // interprets the rightmost 8 bits (high-order are zero)
  // then shifts by more and repeats

  auto ret = std::array<char, 11>{};
  for (auto i = 0; i < 11; ++i) {
    char c = (n >> (6 * i)) & 0b111111;
    ret[i] = lookup[c];
  }
  return ret;
}

} // namespace support::detail
