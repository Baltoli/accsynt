#pragma once

#include <props/props.h>
#include <support/traits.h>

#include <llvm/ExecutionEngine/GenericValue.h>

#include <vector>
#include <type_traits>

namespace synth {

namespace detail {

template <typename T>
constexpr uint8_t nth_byte(T val, size_t n)
{
  uint8_t data[sizeof(T)] = { 0 };
  memcpy(data, &val, sizeof(T));
  return data[n];
}

}

class call_builder {
public:
  call_builder(props::signature sig);

  template <typename T>
  void add(T arg);

  props::signature const& signature() const;
  uint8_t const* args() const;

private:

  props::signature signature_;
  std::vector<uint8_t> args_;
};

template <typename T>
void call_builder::add(T arg)
{
  using Base = std::decay_t<T>;
  static_assert(std::is_same_v<Base, int> ||
                std::is_same_v<Base, float> ||
                std::is_pointer_v<Base>,
                "Must be int, float or pointer!");

  for(auto i = 0u; i < sizeof(T); ++i) {
    args_.push_back(detail::nth_byte(arg, sizeof(T) - i - 1));
  }
}

}
