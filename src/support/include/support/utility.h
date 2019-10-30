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

namespace detail {

template <typename TIter>
struct enum_iterator
{
    size_t i;
    TIter iter;
    bool operator!= (const enum_iterator<TIter> & other) const { return iter != other.iter; }
    void operator++ () { ++i; ++iter; }
    auto operator* () const { return std::tie(i, *iter); }
};

}

template <typename TIter>
constexpr auto enumerate(TIter b, TIter e)
{
    struct iterable_wrapper
    {
        TIter begin_;
        TIter end_;
        auto begin() { return detail::enum_iterator<TIter>{ 0, begin_ }; }
        auto end() { return detail::enum_iterator<TIter>{ 0, end_ }; }
    };
    return iterable_wrapper{ b, e };
}

template <
  typename T,
  typename TIter = decltype(adl_begin(std::declval<T>())),
  typename = decltype(adl_end(std::declval<T>()))
>
constexpr auto enumerate(T&& iterable)
{
    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return detail::enum_iterator<TIter>{ 0, adl_begin(iterable) }; }
        auto end() { return detail::enum_iterator<TIter>{ 0, adl_end(iterable) }; }
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

}

#define FWD(x) std::forward<decltype(x)>(x)
