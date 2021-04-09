#include "print_opcode.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

void PrintOpcodeVisitor::visitInstruction(Instruction& inst)
{
  auto mod = inst.getParent()->getParent()->getParent();
  auto decl = printer_decl(*mod);

  auto b = IRBuilder<>(&inst);

  auto format = b.CreateGlobalStringPtr("%s\n");
  auto str = b.CreateGlobalStringPtr("inst");

  b.CreateCall(decl, {format, str});
}

Function* PrintOpcodeVisitor::printer_decl(Module& mod) const
{
  return nullptr;
}
