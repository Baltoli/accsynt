#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <llvm/IR/Value.h>

#include <map>

namespace coverage {

namespace detail {

enum branch_visits { None = 0x0, True = 0x1, False = 0x2, All = 0x3 };

} // namespace detail

class wrapper : public support::call_wrapper {
public:
  using support::call_wrapper::call_wrapper;

  /**
   * Shadow the base class call method, ensuring when we call through this
   * implementation that we have already instrumented the function with branch
   * checks.
   */
  uint64_t call(support::call_builder& builder);

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

private:
  bool instrumented_ = false;
  void instrument();

  std::map<llvm::Value*, int> value_ids_ = {};
  std::map<int, detail::branch_visits> visits_ = {};
};

} // namespace coverage
