#include "sketch_context.h"

#include "stub.h"

#include <support/assert.h>

using namespace llvm;

namespace presyn {

sketch_context::sketch_context(Module& mod, props::signature sig)
    : module_(mod)
    , sig_(sig)
{
}

llvm::Function* sketch_context::stub() { unimplemented(); }

llvm::Function* sketch_context::stub_for(llvm::Type*) { unimplemented(); }

} // namespace presyn
