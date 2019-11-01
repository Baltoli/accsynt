#include <interfind/common.h>

#include <llvm/IR/Value.h>

using namespace llvm;

namespace interfind {

bool is_global(Value* val)
{
  return isa<Constant>(val) || isa<Argument>(val) || isa<GlobalValue>(val);
}
} // namespace interfind
