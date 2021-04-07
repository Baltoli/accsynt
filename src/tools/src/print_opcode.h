#pragma once

#include <llvm/IR/InstVisitor.h>

class PrintOpcodeVisitor : public llvm::InstVisitor<PrintOpcodeVisitor> {
public:
  void visitInstruction(llvm::Instruction&);
};
