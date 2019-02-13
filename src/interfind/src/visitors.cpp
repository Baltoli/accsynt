#include <interfind/visitors.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Instruction.h>

using namespace llvm;

namespace interfind {

type_collect_visitor::type_collect_visitor(Type *ty) :
  type_(ty), vals_()
{
}

std::set<Value *> type_collect_visitor::values() const
{
  return vals_;
}

void type_collect_visitor::visitInstruction(llvm::Instruction& inst)
{
  if(inst.getType() == type_) {
    vals_.insert(&inst);
  }

  for(auto& op : inst.operands()) {
    if(auto* cst = dyn_cast<Constant>(&op)) {
      if(cst->getType() == type_) {
        vals_.insert(cst);
      }
    }
  }
}

std::set<Value *> values_of_type(Function &fn, Type *ty)
{
  auto vis = type_collect_visitor(ty);

  vis.visit(fn);
  vis.visitValues(fn.getParent()->globals());
  vis.visitValues(fn.args());

  return vis.values();
}

}
