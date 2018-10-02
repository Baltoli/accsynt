#pragma once

#include <llvm/Pass.h>

#include <memory>

llvm::ModulePass *createCleanPass();
llvm::ModulePass *createNamerPass();

std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass();
std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass(std::string file);
