#pragma once

#include <llvm/IR/Instruction.h>

#include <optional>

std::optional<std::string> constraint(llvm::Instruction const& I);
