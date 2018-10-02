#pragma once

#include <llvm/Pass.h>

#include <memory>

std::unique_ptr<llvm::ModulePass> createCleanPass();

std::unique_ptr<llvm::FunctionPass> createNamerPass();
std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass();
std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass(std::string file);
