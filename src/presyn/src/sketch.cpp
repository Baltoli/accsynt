#include "sketch.h"

#include "sketch_context.h"

#include <support/thread_context.h>

using namespace support;
using namespace llvm;

namespace presyn {

sketch::sketch(props::signature sig, fragment const& frag)
    : module_("sketch", thread_context::get())
    , ctx_(sig)
{
}

sketch::sketch(props::signature sig, std::unique_ptr<fragment> const& frag)
    : sketch(sig, *frag)
{
}

Module& sketch::module() { return module_; }

Module const& sketch::module() const { return module_; }

} // namespace presyn
