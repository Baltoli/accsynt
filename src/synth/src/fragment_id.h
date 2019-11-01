#pragma once

#include <algorithm>
#include <set>

namespace {

extern std::set<char*> reg_ptrs_;

}

namespace synth {

template <typename T>
int get_id()
{
  return std::distance(reg_ptrs_.begin(), reg_ptrs_.find(&T::ID));
}

template <typename T>
int get_id(T&& t)
{
  return get_id<T>();
}

} // namespace synth
