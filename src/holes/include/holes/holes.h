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

  llvm::Type* hole_type() const;

  llvm::Instruction* create_hole();
  llvm::Instruction* create_hole(llvm::Type* ty);

private:
  llvm::Function* get_identity(llvm::Type*);

  llvm::LLVMContext& ctx_;
  llvm::Module& mod_;

  llvm::Type* hole_type_;
  std::unordered_map<llvm::Type*, llvm::Function*> identities_;

  std::unordered_set<llvm::Value*> holes_;
};

} // namespace holes
