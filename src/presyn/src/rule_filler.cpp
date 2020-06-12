#include "rule_filler.h"

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
 * We want to try and maximise locality
 *
 * It is possible for no rule to match - I think the best thing to do in this
 * case is for the filler to return nothing, and the calling code is then
 * responsible for dealing with that (i.e. delete the hole instead of throwing
 * an error).
 */
Value* rule_filler::fill(CallInst* hole) { return nullptr; }

} // namespace presyn
