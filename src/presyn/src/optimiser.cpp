#include "optimiser.h"

#include <llvm/IR/Dominators.h>

#include <support/assert.h>

using namespace support;
using namespace llvm;

namespace presyn {

optimiser::optimiser(holes::provider&& hp)
    : provider_(std::move(hp))
    , live_values_ {}
    , constants_ {}
{
}

void optimiser::run(Function* target, call_wrapper& wrap)
{
  assertion(
      target->getParent() == &provider_.module(),
      "No cross-module optimisation is supported");

  auto initial_holes = provider_.holes();

  for (auto hole : initial_holes) {
    if (hole->getType() == provider_.hole_type()) {
      auto cst = get_constant(0, IntegerType::get(provider_.ctx(), 64));
      provider_.rauw_nt(hole, cst);
    }
  }

  auto dom_tree = DominatorTree(*target);

  // TODO: Naive implementation - fix later
  for (auto& from_bb : *target) {
    for (auto& from_i : from_bb) {
      live_values_.try_emplace(&from_i);

      for (auto& to_bb : *target) {
        for (auto& to_i : to_bb) {
          if (dom_tree.dominates(&from_i, &to_i)) {
            live_values_[&to_i].insert(&from_i);
          }
        }
      }
    }
  }

  for (auto const& [val, cands] : live_values_) {
    fmt::print("Instruction {} could use:\n", *val);
    for (auto const& c : cands) {
      fmt::print("  {}\n", *c);
    }
  }

  provider_.reset();
}

} // namespace presyn
