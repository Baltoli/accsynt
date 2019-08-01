#pragma once

#include <array>
#include <functional>
#include <string>

static constexpr std::array lookup = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
  'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
static_assert(lookup.size() == 64);

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

namespace support {

template <typename T>
std::string nice_hash(T const& obj)
{
  size_t hash_val = std::hash<T>()(obj);
  auto chars = to_sextets(hash_val);
  return std::string(chars.begin(), chars.end());
}

} // namespace support
