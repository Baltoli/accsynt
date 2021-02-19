#pragma once

#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

struct klee_decls {
  klee_decls(llvm::Module&);

  llvm::Function* make_symbolic;
  llvm::Function* assume;
  llvm::Function* assert_;
  llvm::Function* main_;

private:
  llvm::Function* create_klee_make_symbolic(llvm::Module&);
  llvm::Function* create_assume(llvm::Module&);
  llvm::Function* create_assert(llvm::Module&);
  llvm::Function* create_main(llvm::Module&);
};

llvm::Type* get_size_ty(llvm::LLVMContext& ctx);
