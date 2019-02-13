#pragma once

#include <llvm/IR/InstVisitor.h>

#include <set>

namespace llvm {
  class Function;
  class Instruction;
  class Type;
  class Value;
}

namespace interfind {

class type_collect_visitor : public llvm::InstVisitor<type_collect_visitor> {
public:
  type_collect_visitor(llvm::Type *);
  std::set<llvm::Value *> instructions() const;

  void visitInstruction(llvm::Instruction& inst);

private:
  llvm::Type *type_;
  std::set<llvm::Value *> instrs_;
};

std::set<llvm::Value *> values_of_type(llvm::Function&, llvm::Type *);

}
