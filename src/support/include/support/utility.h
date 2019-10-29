#pragma once

#include <iterator>

namespace support {

template <typename T>
decltype(auto) begin(T&& t)
{
  using std::begin;
  return begin(std::forward<T>(t));
}

template <typename T>
decltype(auto) end(T&& t)
{
  using std::end;
  return end(std::forward<T>(t));
}

}
