#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <map>

namespace coverage {

namespace detail {

enum branch_visits { None = 0x0, True = 0x1, False = 0x2, All = 0x3 };

} // namespace detail

class wrapper : public support::call_wrapper {
public:
  template <typename... Args>
  explicit wrapper(Args&&... args)
      : support::call_wrapper(std::forward<Args>(args)...)
  {
    instrument();
  }

  /**
   * The number of distinct branch conditions in the function being examined.
   *
   * This is evaluated naively - if both sides of a conditional point to the
   * same basic block, then we still count two separate conditions.
   */
  size_t total_conditions() const;

  /**
   * The number of conditions that have been covered during executions of this
   * wrapper so far.
   */
  size_t covered_conditions() const;

  /**
   * Convenience wrapper to get the coverage metric (covered / total).
   */
  double coverage() const;

  /**
   * Handler to be called back into from instrumented code - calls to it should
   * never be made outside of generated / JIT-compiled LLVM code.
   */
  void handle_branch_event(int id, bool value);

  /**
   * Add additional instrumentation code to the function that allows it to be
   * interrupted when an external flag is changed.
   *
   * The primary motivation for this feature is to allow for timeouts to be
   * enforced by a timer on another thread.
   *
   * To implement the interrupt signal:
   *  - Add an additional exit block to the function that returns a dummy (zero)
   *    constant of the appropriate type.
   *  - Create an externally-mapped pointer-to-bool using the supplied address.
   *  - For every basic block, create an auxiliary block.
   *  - Move the original terminator into the auxiliary block.
   *  - At the end of the original block, test the external bool pointer and
   *    make a conditional branch to either the exit block or the auxiliary one.
   */
  void enable_interrupts(bool*);

  /**
   * Reset the running observations of branches visited.
   *
   * This allows for multiple experiments to be run without the costly step of
   * re-instrumenting the entire function.
   */
  void reset();

private:
  void instrument();

  std::map<llvm::BranchInst*, int> branch_ids_ = {};
  std::map<int, detail::branch_visits> visits_ = {};
};

} // namespace coverage
