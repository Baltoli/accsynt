#include <interfind/visitors.h>

#include <llvm/IR/Instruction.h>

using namespace llvm;

namespace interfind {

type_collect_visitor::type_collect_visitor(Type *ty) :
  type_(ty), instrs_()
{
}

std::set<Value *> type_collect_visitor::instructions() const
{
  return instrs_;
}

void type_collect_visitor::visitInstruction(llvm::Instruction& inst)
{
  if(inst.getType() == type_) {
    instrs_.insert(&inst);
  }
}

std::set<Value *> values_of_type(Function &fn, Type *ty)
{
  auto vis = type_collect_visitor(ty);
  vis.visit(fn);
  return vis.instructions();
}

}
