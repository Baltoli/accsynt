#include "candidate_visitors.h"

using namespace llvm;

namespace presyn {

bool is_valid_visitor::valid() const { return valid_; }

void is_valid_visitor::visitCallInst(CallInst const& ci)
{
  auto fn = ci.getCalledFunction();
  if (fn->isDeclaration()) {
    valid_ = false;
  }
}

} // namespace presyn
