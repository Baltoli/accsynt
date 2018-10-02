#pragma once

#include <llvm/Pass.h>

llvm::ModulePass *createCleanPass();
llvm::ModulePass *createNamerPass();

llvm::FunctionPass *createConvertToIDLPass();
