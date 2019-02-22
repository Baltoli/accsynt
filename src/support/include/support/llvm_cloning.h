#pragma once

#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace support {

llvm::Function* copy_function(llvm::Function* f, llvm::Module* m);
std::unique_ptr<llvm::Module> copy_module_to(
    llvm::LLVMContext& ctx, llvm::Module const& m);
}
