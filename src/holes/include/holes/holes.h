#pragma once

namespace llvm {
class LLVMContext;
class Function;
class Instruction;
class Module;
class Type;
class Value;
} // namespace llvm

#include <unordered_map>
#include <unordered_set>

namespace holes {

class provider {
public:
  provider(llvm::LLVMContext&, llvm::Module&);

  llvm::Module const& module() const;
  llvm::Module& module();

  llvm::LLVMContext& ctx();

  llvm::Type* hole_type() const;

  void rauw_nt(llvm::Instruction* before, llvm::Value* after);

  llvm::Instruction* create_hole();
  llvm::Instruction* create_hole(llvm::Type* ty);

  void reset();
  std::unordered_set<llvm::Instruction*> const& holes() const;
  void add_hole(llvm::Instruction*);

private:
  void rauw_nt_helper(
      llvm::Instruction* before, llvm::Value* after,
      std::unordered_map<llvm::Instruction*, llvm::Value*>& replacements);

  llvm::Function* get_identity(llvm::Type*);

  llvm::LLVMContext& ctx_;
  llvm::Module& mod_;

  llvm::Type* hole_type_;
  std::unordered_map<llvm::Type*, llvm::Function*> identities_;

  std::unordered_set<llvm::Instruction*> holes_;
};

} // namespace holes
