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

size_t wrapper::total_conditions() const { return 0; }
size_t wrapper::covered_conditions() const { return 0; }
double wrapper::coverage() const { return 0.0; }

} // namespace coverage
