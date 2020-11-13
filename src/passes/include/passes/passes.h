#pragma once

#include <passes/count.h>

#include <llvm/Pass.h>

#include <memory>

std::unique_ptr<llvm::ModulePass> createCleanPass();

std::unique_ptr<llvm::FunctionPass> createNamerPass();
std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass();
std::unique_ptr<llvm::FunctionPass> createConvertToIDLPass(std::string file);

std::unique_ptr<llvm::FunctionPass> createDeduplicatePass();

std::unique_ptr<llvm::FunctionPass> createCycloPass();

std::unique_ptr<Count> createCountPass();
