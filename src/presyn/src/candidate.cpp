#include "candidate.h"

using namespace llvm;

namespace presyn {

candidate::candidate(std::unique_ptr<Module>&& mod)
    : module_(std::move(mod))
{
}

} // namespace presyn
