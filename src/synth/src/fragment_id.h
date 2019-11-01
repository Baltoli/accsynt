#pragma once

#include <algorithm>
#include <optional>
#include <set>

namespace {

extern std::set<char*> reg_ptrs_;

}

namespace synth {

template <typename T>
struct register_fragment_id {
  register_fragment_id() { reg_ptrs_.insert(&T::ID); }
};

template <typename T>
std::optional<int> get_fragment_id()
{
  auto found = reg_ptrs_.find(&T::ID);
  if (found == reg_ptrs_.end()) {
    return std::nullopt;
  } else {
    return std::distance(reg_ptrs_.begin(), found);
  }
}

template <typename T>
decltype(auto) get_fragment_id(T&& t)
{
  return get_fragment_id<T>();
}

} // namespace synth
