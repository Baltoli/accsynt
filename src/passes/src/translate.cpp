#include "opcode.h"
#include "translate.h"

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

using namespace llvm;

std::string nth_of(size_t i)
{
  if(i == 0) { return "first"; }
  else if(i == 1) { return "second"; }
  else if(i == 2) { return "third"; }
  else {
    assert(false && "Too many operands");
  }
}

// Base constraint for an instruction - i.e. {I} is add instruction
std::optional<std::string> base_constraint(Instruction const& I)
{
  using namespace fmt::literals;

  if(auto op = idl_opcode(I)) {
    return "({{{result}}} is {op} instruction)"_format(
      "result"_a = I.getName().str(),
      "op"_a = op.value()
    );
  }

  return std::nullopt;
}

// Constraint for the nth argument of I
// i.e. {v0} is first argument of {I}
std::string nth_arg_constraint(Instruction const& I, size_t n)
{
  using namespace fmt::literals;
  assert(n < I.getNumOperands() && 
         "Not enough operands to instruction");

  auto nth_text = nth_of(n);
  return "({{{arg}}} is {nth} argument of {{{instr}}})"_format(
      "arg"_a = I.getOperand(n)->getName().str(),
      "nth"_a = nth_text,
      "instr"_a = I.getName().str()
  );
}

// Combine constraints into one by wrapping them in braces and forming their
// conjunction
template <typename Iterator>
std::string constraint_and(Iterator begin, Iterator end)
{
  using namespace fmt::literals;

  return "({})"_format(fmt::join(begin, end, " and "));
}

// Comvenience overload
template <typename Container>
std::string constraint_and(Container c)
{
  using std::begin;
  using std::end;

  return constraint_and(begin(c), end(c));
}

std::optional<std::string> constraint(Instruction const& I)
{
  auto operands = I.getNumOperands();

  if(auto op_str = base_constraint(I); operands <= 3) {
    auto args = std::vector<std::string>{op_str.value()};

    for(auto n = 0u; n < operands; ++n) {
      args.push_back(nth_arg_constraint(I, n));
    }

    return constraint_and(args);
  }

  return std::nullopt;
}
