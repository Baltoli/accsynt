#pragma once

#include <algorithm>
#include <optional>
#include <type_traits>

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
int get_fragment_id()
{
  if (auto id = detail::get_id(&T::ID)) {
    return id.value();
  } else {
    throw std::runtime_error("Unregistered type");
  }
}

template <typename T>
decltype(auto) get_fragment_id(T&& t)
{
  return get_fragment_id<std::decay_t<T>>();
}

} // namespace synth
