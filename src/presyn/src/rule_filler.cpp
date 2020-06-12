#include "rule_filler.h"

#include <support/assert.h>

#include <algorithm>

using namespace llvm;

namespace presyn {

/**
 * This is the proper filler implementation that we'll use to drive the
 * synthesizer and therefore needs to be clearly specified before we start to
 * write the implementation.
 *
 * The core idea of this filler is to walk backwards from the hole, collecting
 * values as we go. These values are then used to match against a set of
 * pre-specified rules that govern how a value should be selected.
 *
 * For the moment I think that the iteration order should be such that holes are
 * filled in order from top to bottom; this should mean that we don't have to
 * worry about combining holes to make values for other holes. Instead, the
 * decision at each step is only to select a concrete value.
 *
 * We want to try and maximise locality (i.e. prioritise choosing close
 * values rather than far-away ones). It doesn't make as much sense to be
 * grabbing function arguments late on in a function as it does at the start -
 * instead, we'd be more likely to choose recently-produced values.
 *
 * I think the right abstraction is to have a configurable "pool size" for how
 * many values we want to use for each hole. If we can't get enough preceding
 * instructions, then try constants, then function args etc. We'd then sample
 * among the matching rules from those values. Then, the pool size and the order
 * in which we get the values are configurable parameters.
 *
 * It is possible for no rule to match - I think the best thing to do in this
 * case is for the filler to return nothing, and the calling code is then
 * responsible for dealing with that (i.e. delete the hole instead of throwing
 * an error).
 *
 * The filling process is therefore as follows:
 *   * Collect a pool of values to match rules on (these categories might also
 *     each need their own configured pool sizes).
 *     * Walk backwards in block
 *     * Dominating blocks
 *     * Function params
 *     * Constants
 *   * Establish which rules from a collection match the pooled values
 *   * Choose a rule randomly and apply it to produce a value.
 *
 * The collection mechanism is the right abstraction based on this - it should
 * be possible to come up with a rule-based sampling engine based on smaller
 * pools, as long as for holes with known type we include a constant value in
 * the pool (to make sure that something gets filled in).
 */
Value* rule_filler::fill(CallInst* hole)
{
  auto locals = collect_local(hole);
  return nullptr;
}

std::vector<Value*> rule_filler::collect_local(CallInst* hole) const
{
  auto ret = std::vector<Value*> {};

  for (auto& inst : *hole->getParent()) {
    if (&inst == hole) {
      break;
    }

    if (!inst.getType()->isVoidTy()) {
      ret.push_back(&inst);
    }
  }

  std::reverse(ret.begin(), ret.end());
  return ret;
}

} // namespace presyn
