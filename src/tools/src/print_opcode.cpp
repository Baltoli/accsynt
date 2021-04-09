#include "print_opcode.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

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
    return inst.getParent()->getParent()->getName();
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

void PrintOpcodeVisitor::visitInstruction(Instruction& inst) { }

Function* PrintOpcodeVisitor::printer_decl(Module& mod) const
{
  auto& ctx = mod.getContext();

  auto int_ty = IntegerType::get(ctx, 32);
  auto str_ty = IntegerType::get(ctx, 8)->getPointerTo();
  auto fn_ty = FunctionType::get(int_ty, {str_ty}, true);

  auto callee = mod.getOrInsertFunction("printf", fn_ty);

  return cast<Function>(callee.getCallee());
}
