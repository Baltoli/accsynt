#pragma once

#include <props/props.h>

#include <llvm/ExecutionEngine/GenericValue.h>

#include <vector>
#include <type_traits>

namespace synth {

class call_builder {
public:
  call_builder(props::signature sig);

  template <typename T>
  void add(T arg);

  props::signature const& signature() const;
  std::vector<llvm::GenericValue> const& args() const;

private:
  void add_int(int i);
  void add_double(double d);

  template <typename T>
  void add_pointer(T *ptr);

  props::signature signature_;
  std::vector<llvm::GenericValue> args_;
};

template <typename T>
void call_builder::add(T arg)
{
  using Base = std::decay_t<T>;
  if constexpr(std::is_same_v<Base, int>) {
    add_int(arg);
  } else if constexpr(std::is_same_v<Base, float> ||
                      std::is_same_v<Base, double>) {
    add_double(arg);
  } else if constexpr(std::is_pointer_v<Base>) {
    add_pointer(arg);
  } else {
    static_assert(std::is_same_v<Base, int>, "Invalid type!");
  }
}

template <typename T>
void call_builder::add_pointer(T *ptr)
{
  using RPT = std::remove_pointer_t<T>;

  static_assert(std::is_same_v<RPT, int> ||
                std::is_same_v<RPT, float>,
                "Unsupported pointer type");

  auto gv = llvm::GenericValue{ptr};
  args_.push_back(gv);
}

}
