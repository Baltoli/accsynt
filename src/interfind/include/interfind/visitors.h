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
  std::set<llvm::Value *> values() const;

  void visitInstruction(llvm::Instruction& inst);

  template <typename Range>
  void visitValues(Range&&);

private:
  llvm::Type *type_;
  std::set<llvm::Value *> vals_;
};

template <typename Range>
void type_collect_visitor::visitValues(Range&& rng)
{
  for(auto& val : rng) {
    if(val.getType() == type_) {
      vals_.insert(&val);
    }
  }
}

std::set<llvm::Value *> values_of_type(llvm::Function&, llvm::Type *);

}
