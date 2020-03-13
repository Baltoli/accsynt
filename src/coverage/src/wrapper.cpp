#include <coverage/coverage.h>

namespace coverage {

uint64_t wrapper::call(support::call_builder& builder)
{
  if (!instrumented_) {
    instrument();
  }

  return support::call_wrapper::call(builder);
}

void wrapper::instrument() { instrumented_ = true; }

} // namespace coverage
