#pragma once

#include <props/props.h>

#include <llvm/ExecutionEngine/GenericValue.h>

#include <vector>
#include <type_traits>

namespace synth {

class call_builder {
public:
  call_builder(props::signature sig);

  void add(int i);
  void add(float f);

  template <typename T>
  void add(T *ptr);

  props::signature const& signature() const;
  std::vector<llvm::GenericValue> const& args() const;

private:
  props::signature signature_;
  std::vector<llvm::GenericValue> args_;
};

template <typename T>
void add(T *ptr)
{
  using RPT = std::remove_pointer_t<T>;

  static_assert(std::is_same_v<RPT, int> ||
                std::is_same_v<RPT, float>,
                "Unsupported pointer type");

  auto gv = GenericValue{ptr};
  args_.push_back(gv);
}

}
