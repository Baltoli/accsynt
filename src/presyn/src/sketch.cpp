#include "sketch.h"

#include "sketch_context.h"

namespace presyn {

sketch::sketch(props::signature sig, fragment const& frag)
    : ctx_(sig)
{
}

} // namespace presyn
