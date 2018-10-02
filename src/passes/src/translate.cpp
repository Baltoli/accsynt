#include "opcode.h"
#include "translate.h"

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

using namespace llvm;

std::optional<std::string> constraint(llvm::Instruction const& I)
{
  if(auto op = idl_opcode(I)) {
    return fmt::format(
      "( {{{result}}} is {op} instruction and {{{left}}} is first argument of {{{result}}} )",
      fmt::arg("result", I.getName().str()),
      fmt::arg("op", op.value()),
      fmt::arg("left", "left")
    );             
  }

  return std::nullopt;
}
