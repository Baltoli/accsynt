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

}
