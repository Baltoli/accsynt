#pragma once

llvm::ModulePass *createCleanPass();
llvm::ModulePass *createNamerPass();

llvm::FunctionPass *createConvertToIDLPass();
