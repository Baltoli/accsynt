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
      rauw_nt_proxy(hole, cst);

      provider_.add_hole(cst);
    }
  }

  compute_initial_live_sets(target);

  provider_.reset();
}

void optimiser::rauw_nt_proxy(Instruction* before, Instruction* after)
{
  provider_.rauw_nt(before, after);

  for (auto& [val, cands] : live_values_) {
    if (val == before) {
      live_values_[after] = cands;
      live_values_.erase(before);
    } else {
      if (cands.erase(before) > 0) {
        cands.insert(after);
      }
    }
  }
}

void optimiser::compute_initial_live_sets(Function* target)
{
  auto dom_tree = DominatorTree(*target);

  // TODO: Naive implementation - fix later
  for (auto& from_i : provider_.holes()) {
    live_values_.try_emplace(from_i);

    for (auto& to_bb : *target) {
      for (auto& to_i : to_bb) {
        if (dom_tree.dominates(&to_i, from_i)) {
          live_values_[from_i].insert(&to_i);
        }
      }
    }
  }
}

void optimiser::resolve_undefs()
{
  auto holes = provider_.holes();
  for (auto& hole : holes) {
  }
}

} // namespace presyn
