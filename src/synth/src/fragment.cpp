#include "fragment.h"

using namespace llvm;
using namespace props;

namespace synth {

fragment::fragment(std::vector<value> args) :
  args_(args)
{
}

/**
 * From what I've thought about, I think the best thing to do is to have a
 * context "own" / manage a single function which is created when we create a
 * context object - then we can also keep track of the appropriate basic blocks
 * with the context object as well.
 */
compile_context::compile_context(Module& mod, signature sig) :
  mod_(mod), sig_(sig)
{
  // TODO: this should set up the function we're compiling into, and assign the
  // basic blocks for entry and exit. Need to check return type.
}

}
