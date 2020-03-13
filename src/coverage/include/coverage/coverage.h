#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

namespace coverage {

class wrapper : public support::call_wrapper {
public:
  using support::call_wrapper::call_wrapper;

  uint64_t call(support::call_builder& builder);

private:
  bool instrumented_ = false;
  void instrument();
};

} // namespace coverage
