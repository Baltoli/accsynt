#include "opcode.h"
#include "translate.h"

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

using namespace llvm;

std::optional<std::string> constraint(llvm::Instruction const& I)
{
  if(auto op = idl_opcode(I)) {
    return fmt::format(
      "( {{{}}} is {} instruction )",
      I.getName().str(), op.value()
    );             
  }

  return std::nullopt;
}
