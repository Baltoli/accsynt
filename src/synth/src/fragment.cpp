#include "fragment.h"

using namespace llvm;
using namespace props;

namespace synth {

fragment::fragment(std::vector<value> args) :
  args_(args)
{
}

compile_context::compile_context(Module& mod, signature sig) :
  mod_(mod), sig_(sig)
{
}

function_harness compile_context::get_new_harness()
{
  // TODO: make a new function, check the signature for a return type, create
  // entry and exit blocks.
  return { nullptr, nullptr, nullptr };
}

}
