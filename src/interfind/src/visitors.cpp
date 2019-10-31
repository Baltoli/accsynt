#include <interfind/visitors.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Instruction.h>

using namespace llvm;

namespace interfind {

std::set<Value*> values_of_type(Function& fn, Type* ty)
{
  return values_by_pred(fn, [ty](auto& val) { return val.getType() == ty; });
}
} // namespace interfind
