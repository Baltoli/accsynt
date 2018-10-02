#pragma once

#include <llvm/IR/Instruction.h>

#include <optional>

std::optional<std::string> idl_opcode(llvm::Instruction const& inst);
