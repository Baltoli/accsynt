#pragma once

#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstVisitor.h>

#include <optional>
#include <unordered_map>

class PromoteVisitor : public llvm::InstVisitor<PromoteVisitor> {
public:
  PromoteVisitor();

  void visitAllocaInst(llvm::AllocaInst&);

  void promote() const;

private:
  std::unordered_map<llvm::Function*, std::vector<llvm::AllocaInst*>>
      to_promote_;
};

class PrintOpcodeVisitor : public llvm::InstVisitor<PrintOpcodeVisitor> {
public:
  PrintOpcodeVisitor();
  explicit PrintOpcodeVisitor(std::string);

  void visitBinaryOperator(llvm::BinaryOperator&);
  void visitUnaryOperator(llvm::UnaryOperator&);
  void visitCmpInst(llvm::CmpInst&);
  void visitLoadInst(llvm::LoadInst&);
  void visitStoreInst(llvm::StoreInst&);
  void visitBranchInst(llvm::BranchInst&);
  void visitReturnInst(llvm::ReturnInst&);

private:
  std::optional<std::string> tag_;
  std::unordered_map<std::string, llvm::Value*> string_table_;

  std::string tag_at(llvm::Instruction&) const;

  void instrument(llvm::Instruction&, std::string);

  llvm::Function* printer_decl(llvm::Module&) const;

  template <typename... Params>
  llvm::Value* get_string_constant(llvm::IRBuilder<Params...>&, std::string);
};

template <typename... Params>
llvm::Value* PrintOpcodeVisitor::get_string_constant(
    llvm::IRBuilder<Params...>& b, std::string s)
{
  if (string_table_.find(s) == string_table_.end()) {
    string_table_[s] = b.CreateGlobalStringPtr(s);
  }

  return string_table_.at(s);
}
