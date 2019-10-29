#pragma once

#include <iterator>

namespace support {

namespace detail {

using std::begin;
template <typename T>
auto adl_begin(T&& t) -> decltype(begin(std::forward<T>(t)))
{
  return begin(std::forward<T>(t));
}

using std::end;
template <typename T>
auto adl_end(T&& t) -> decltype(end(std::forward<T>(t)))
{
  return end(std::forward<T>(t));
}

}

template <typename T>
auto adl_begin(T&& t) -> decltype(detail::adl_begin(std::forward<T>(t)))
{
  return detail::adl_begin(std::forward<T>(t));
}

template <typename T>
auto adl_end(T&& t) -> decltype(detail::adl_end(std::forward<T>(t)))
{
  return detail::adl_end(std::forward<T>(t));
}

}

#define FWD(x) std::forward<decltype(x)>(x)
