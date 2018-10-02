#include "opcode.h"

using namespace llvm;

bool is_add(Instruction const& inst)
{
  return inst.getOpcode() == Instruction::Add;
}

std::optional<std::string> idl_opcode(llvm::Instruction const& inst)
{
  if(is_add(inst)) { return "add"; }
  return std::nullopt;
}
