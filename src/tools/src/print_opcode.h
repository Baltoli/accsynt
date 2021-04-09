#pragma once

#include <llvm/IR/Function.h>
#include <llvm/IR/InstVisitor.h>

class PrintOpcodeVisitor : public llvm::InstVisitor<PrintOpcodeVisitor> {
public:
  void visitInstruction(llvm::Instruction&);

private:
  llvm::Function* printer_decl(llvm::Module&) const;
};
