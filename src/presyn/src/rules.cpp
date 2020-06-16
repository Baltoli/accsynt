#include "rules.h"

namespace presyn {

void first_of_type::match(
    filler const& fill, llvm::CallInst* hole,
    std::vector<llvm::Value*> const& choices,
    std::vector<llvm::Value*>& ret) const
{
}

} // namespace presyn
