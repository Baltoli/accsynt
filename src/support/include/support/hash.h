#pragma once

#include <array>
#include <functional>
#include <string>

namespace support::detail {

constexpr std::array lookup = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
  'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
  '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
static_assert(lookup.size() == 64);

std::array<char, 11> to_sextets(size_t n);

} // namespace support::detail

namespace support {

template <typename T>
std::string nice_hash(T const& obj)
{
  size_t hash_val = std::hash<T>()(obj);
  auto chars = detail::to_sextets(hash_val);
  return std::string(chars.begin(), chars.end());
}

} // namespace support
