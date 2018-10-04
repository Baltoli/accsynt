#include "opcode.h"

using namespace llvm;

std::optional<std::string> idl_opcode(llvm::Instruction const& inst)
{
  switch(inst.getOpcode()) {
    /* case Instruction::Br: */
    /*   return "branch"; */
    case Instruction::GetElementPtr: 
      return "gep";
    case Instruction::Shl:
      return "lshift";
    case Instruction::LShr:
    case Instruction::AShr:
      return "rshift";
    case Instruction::Add:
    case Instruction::FAdd:
    case Instruction::Sub:
    case Instruction::FSub:
    case Instruction::Mul:
    case Instruction::FMul:
    case Instruction::UDiv:
    case Instruction::SDiv:
    case Instruction::FDiv:
    case Instruction::PHI:
    case Instruction::And:
    case Instruction::Or:
    case Instruction::ICmp:
    case Instruction::FCmp:
    case Instruction::Load:
    case Instruction::Store:
      return inst.getOpcodeName(inst.getOpcode());
    default: 
      return std::nullopt;
  }
}
