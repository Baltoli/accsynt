#pragma once

#include <props/props.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include <vector>

struct klee_decls {
  klee_decls(llvm::Module&);

  llvm::Value* check_all_equal(
      llvm::IRBuilder<>&, llvm::Value*, std::vector<llvm::Value*> const&,
      std::vector<llvm::Value*> const&);

  std::vector<llvm::Value*>
  allocate_symbolic(llvm::IRBuilder<>&, props::signature const&);

  llvm::Function* make_symbolic;
  llvm::Function* assume;
  llvm::Function* assert_;
  llvm::Function* main_;
  llvm::Function* array_size;

private:
  llvm::Function* create_klee_make_symbolic(llvm::Module&);
  llvm::Function* create_assume(llvm::Module&);
  llvm::Function* create_assert(llvm::Module&);
  llvm::Function* create_main(llvm::Module&);
  llvm::Function* create_array_size(llvm::Module&);

  std::map<llvm::Type*, llvm::Function*> array_equals_;
};

llvm::Type* get_size_ty(llvm::LLVMContext& ctx);
llvm::Value* create_eq(llvm::IRBuilder<>& irb, llvm::Value* a, llvm::Value* b);