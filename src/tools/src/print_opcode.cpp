#include "print_opcode.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/PromoteMemToReg.h>

using namespace llvm;

PromoteVisitor::PromoteVisitor()
    : to_promote_()
{
}

void PromoteVisitor::promote() const
{
  for (auto& [f, as] : to_promote_) {
    auto tree = DominatorTree(*f);
    PromoteMemToReg(as, tree);
  }
}

void PromoteVisitor::visitAllocaInst(llvm::AllocaInst& inst)
{
  auto func = inst.getParent()->getParent();
  to_promote_.try_emplace(func);

  if (isAllocaPromotable(&inst)) {
    to_promote_.at(func).push_back(&inst);
  }
}

PrintOpcodeVisitor::PrintOpcodeVisitor()
    : tag_(std::nullopt)
    , string_table_()
{
}

PrintOpcodeVisitor::PrintOpcodeVisitor(std::string tag)
    : tag_(tag)
    , string_table_()
{
}

std::string PrintOpcodeVisitor::tag_at(llvm::Instruction& inst) const
{
  if (auto ot = tag_) {
    return *ot;
  } else {
    return std::string(inst.getParent()->getParent()->getName());
  }
}

void PrintOpcodeVisitor::instrument(llvm::Instruction& inst, std::string str)
{
  auto mod = inst.getParent()->getParent()->getParent();
  auto decl = printer_decl(*mod);

  auto b = IRBuilder<>(&inst);

  auto format = get_string_constant(b, "%s,%s\n");
  auto str_v = get_string_constant(b, str);
  auto tag_v = get_string_constant(b, tag_at(inst));

  b.CreateCall(decl, {format, str_v, tag_v});
}

void PrintOpcodeVisitor::visitBinaryOperator(llvm::BinaryOperator& inst)
{
  instrument(inst, inst.getOpcodeName());
}

void PrintOpcodeVisitor::visitUnaryOperator(llvm::UnaryOperator& inst)
{
  instrument(inst, inst.getOpcodeName());
}

void PrintOpcodeVisitor::visitCmpInst(llvm::CmpInst& inst)
{
  instrument(inst, inst.getOpcodeName());
}

void PrintOpcodeVisitor::visitLoadInst(llvm::LoadInst& inst)
{
  instrument(inst, "load");
}

void PrintOpcodeVisitor::visitStoreInst(llvm::StoreInst& inst)
{
  instrument(inst, "store");
}

void PrintOpcodeVisitor::visitBranchInst(llvm::BranchInst& inst)
{
  instrument(inst, "branch");
}

void PrintOpcodeVisitor::visitReturnInst(llvm::ReturnInst& inst)
{
  instrument(inst, "return");
}

Function* PrintOpcodeVisitor::printer_decl(Module& mod) const
{
  auto& ctx = mod.getContext();

  auto int_ty = IntegerType::get(ctx, 32);
  auto str_ty = IntegerType::get(ctx, 8)->getPointerTo();
  auto fn_ty = FunctionType::get(int_ty, {str_ty}, true);

  auto callee = mod.getOrInsertFunction("printf", fn_ty);

  return cast<Function>(callee.getCallee());
}
