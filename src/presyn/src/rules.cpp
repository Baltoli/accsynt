#include "rules.h"

using namespace llvm;

namespace presyn::rules {

void do_nothing::match(
    CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
}

void all_of_type::match(
    CallInst* hole, std::vector<Value*> const& choices,
    std::vector<Value*>& generated) const
{
}

} // namespace presyn::rules
