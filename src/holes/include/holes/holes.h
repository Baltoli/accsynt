#pragma once

namespace llvm {
class LLVMContext;
class Instruction;
class Module;
class Type;
} // namespace llvm

namespace holes {

class provider {
public:
  provider(llvm::Module&, llvm::LLVMContext&);

  llvm::Type* hole_type() const;

  llvm::Instruction* create_hole() const;

private:
  llvm::Module& mod_;
  llvm::LLVMContext& ctx_;

  llvm::Type* hole_type_;
};

} // namespace holes
