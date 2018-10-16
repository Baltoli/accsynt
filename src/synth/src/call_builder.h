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

  call_builder(call_builder const&);
  call_builder& operator=(call_builder);

  void reset();

  template <typename T>
  void add(T arg);

  template <typename T>
  void add(std::vector<T> arg);

  props::signature const& signature() const;
  uint8_t* args();

  bool operator==(call_builder const& other) const;
  bool operator!=(call_builder const& other) const;

  friend void swap(call_builder& left, call_builder& right);

private:
  props::signature signature_;
  std::vector<uint8_t> args_;

  size_t current_arg_ = 0;
  std::vector<std::vector<int>> int_data_ = {};
  std::vector<std::vector<float>> float_data_ = {};
};

struct output_example {
  uint64_t return_value;
  call_builder output_args;
};

template <typename T>
void call_builder::add(T arg)
{
  using Base = std::decay_t<T>;
  static_assert((std::is_same_v<Base, int> ||
                std::is_same_v<Base, float>) &&
                !std::is_pointer_v<Base>,
                "Must be int or float and not pointer!");

  assert(current_arg_ < signature_.parameters.size());

  auto param = signature_.parameters.at(current_arg_);
  assert((std::is_same_v<Base, int> == (param.type == props::data_type::integer)));
  assert((std::is_same_v<Base, float> == (param.type == props::data_type::floating)));
  assert(param.pointer_depth == 0);

  for(auto i = 0u; i < sizeof(T); ++i) {
    args_.push_back(detail::nth_byte(arg, i));
  }

  current_arg_++;
}

template <typename T>
void call_builder::add(std::vector<T> arg)
{
  static_assert(std::is_same_v<T, int> ||
                std::is_same_v<T, float>,
                "Pointed-to data must be of base type");

  assert(current_arg_ < signature_.parameters.size());

  auto param = signature_.parameters.at(current_arg_);
  assert((std::is_same_v<T, int> == (param.type == props::data_type::integer)));
  assert((std::is_same_v<T, float> == (param.type == props::data_type::floating)));
  assert(param.pointer_depth == 1);

  void *data = nullptr;
  if constexpr(std::is_same_v<T, int>) {
    int_data_.push_back(arg);
    data = int_data_.back().data();
  } else if constexpr(std::is_same_v<T, float>) {
    float_data_.push_back(arg);
    data = float_data_.back().data();
  }

  assert((data || arg.empty()) && 
         "Something very wrong inside vector building!");

  for(auto i = 0u; i < sizeof(data); ++i) {
    args_.push_back(detail::nth_byte(data, i));
  }

  current_arg_++;
}

}
