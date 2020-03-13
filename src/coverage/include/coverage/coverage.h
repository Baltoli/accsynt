#pragma once

#include <support/call_wrapper.h>

namespace coverage {

class wrapper : public support::call_wrapper {
  using support::call_wrapper::call_wrapper;
};

} // namespace coverage
