#include "constants.h"

#include <llvm/IR/Constant.h>

using namespace llvm;

namespace presyn {

std::vector<llvm::Value*> small_constants(llvm::Type* ty)
{
  return {Constant::getNullValue(ty)};
}

} // namespace presyn
