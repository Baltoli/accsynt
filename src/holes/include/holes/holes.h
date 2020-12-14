#pragma once

namespace llvm {
class LLVMContext;
class Function;
class Instruction;
class Module;
class Type;
} // namespace llvm

#include <unordered_map>

namespace holes {

class provider {
public:
  provider(llvm::LLVMContext&, llvm::Module&);

  llvm::Type* hole_type() const;

  llvm::Instruction* create_hole();

private:
  llvm::Function* get_identity(llvm::Type*);

  llvm::LLVMContext& ctx_;
  llvm::Module& mod_;

  llvm::Type* hole_type_;
  std::unordered_map<llvm::Type*, llvm::Function*> identities_;
};

} // namespace holes
