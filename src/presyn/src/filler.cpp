#include "filler.h"

#include <llvm/IR/Constant.h>

using namespace llvm;

namespace presyn {

Value* zero_filler::fill(CallInst* hole)
{
  return Constant::getNullValue(hole->getType());
}

} // namespace presyn
