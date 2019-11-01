#pragma once

#include <algorithm>
#include <optional>

namespace synth {

namespace detail {

void register_frag(char* ptr);
std::optional<int> get_id(char* ptr);

} // namespace detail

template <typename T>
struct register_fragment_id {
  register_fragment_id() { detail::register_frag(&T::ID); }
};

template <typename T>
std::optional<int> get_fragment_id()
{
  return get_id(&T::ID);
}

template <typename T>
decltype(auto) get_fragment_id(T&& t)
{
  return get_fragment_id<T>();
}

} // namespace synth
