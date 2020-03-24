#pragma once

#include <chrono>
#include <thread>

namespace support {

// Note when calling a timed-out operation, the timeout function needs to cause
// some kind of action that kills or interrupts the main thread's work (e.g.
// setting a flag somewhere).
template <typename Rep, typename Period, typename Operation, typename Timeout>
void timeout(
    std::chrono::duration<Rep, Period> const& d, Operation&& op, Timeout&& time)
{
  auto run_cleanup = true;

  std::thread([&] {
    std::this_thread::sleep_for(d);

    if (run_cleanup) {
      std::forward<Timeout>(time)();
    }
  }).detach();

  std::forward<Operation>(op)();
  run_cleanup = false;
}

} // namespace support
