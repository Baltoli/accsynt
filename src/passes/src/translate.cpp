#include "opcode.h"
#include "translate.h"

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

using namespace llvm;

std::string nth_of(int i)
{
  if(i == 0) { return "first"; }
  else if(i == 1) { return "second"; }
  else if(i == 2) { return "third"; }
  else {
    assert(false && "Too many operands");
  }
}

std::optional<std::string> constraint(llvm::Instruction const& I)
{
  auto operands = I.getNumOperands();
  if(operands > 3) {
    return std::nullopt;
  }

  if(auto op = idl_opcode(I)) {
    auto args = std::vector<std::string>{};
    for(auto i = 0u; i < operands; ++i) {
      args.push_back(fmt::format(
        "{{{arg}}} is {nth} argument of {{{result}}}",
        fmt::arg("arg", I.getOperand(i)->getName().str()),
        fmt::arg("nth", nth_of(i)),
        fmt::arg("result", I.getName().str())
      ));
    }

    auto op_str = fmt::format(
      "{{{result}}} is {op} instruction", 
      fmt::arg("result", I.getName().str()),
      fmt::arg("op", op.value())
    );

    if(args.empty()) {
      return fmt::format("( {} )", op_str);
    } else {
      return fmt::format("( {} and ( {} ) )", op_str, fmt::join(args, " and "));
    }
  }

  return std::nullopt;
}
