#pragma once

#include <iterator>
#include <tuple>

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

template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T && iterable)
{
    struct iterator
    {
        size_t i;
        TIter iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () { ++i; ++iter; }
        auto operator * () const { return std::tie(i, *iter); }
    };
    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable) }; }
        auto end() { return iterator{ 0, std::end(iterable) }; }
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

}

#define FWD(x) std::forward<decltype(x)>(x)
