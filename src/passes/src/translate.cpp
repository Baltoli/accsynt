#include "opcode.h"
#include "translate.h"

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

#include <map>

using namespace llvm;

namespace convert::detail {

static std::map<Value const*, std::string> names{};
static int const_count = 0;
static int instr_count = 0;

std::string next_const_name()
{
  using namespace fmt::literals;

  return "const_v{}"_format(const_count++);
}

std::string next_instr_name()
{
  using namespace fmt::literals;

  return "instr_{}"_format(instr_count++);
}

std::string get_name(Value const& v)
{
  if(isa<Constant>(v)) {
    if(names.find(&v) == names.end()) {
      names.insert({&v, next_const_name()});
    }

    return names.at(&v);
  } else if(isa<Instruction>(v)) {
    if(names.find(&v) == names.end()) {
      names.insert({&v, next_instr_name()});
    }

    return names.at(&v);
  } else {
    return v.getName().str();
  }
}

std::string nth_of(size_t i)
{
  if(i == 0) { return "first"; }
  else if(i == 1) { return "second"; }
  else if(i == 2) { return "third"; }
  else {
    assert(false && "Too many operands");
  }
}

std::string title_case(std::string in)
{
  in[0] = std::toupper(in[0]);
  return in;
}

// Base constraint for an instruction - i.e. {I} is add instruction
std::optional<std::string> base_constraint(Instruction const& I)
{
  using namespace fmt::literals;

  if(auto op = idl_opcode(I)) {
    return "({{{result}}} is {op} instruction)"_format(
      "result"_a = get_name(I),
      "op"_a = op.value()
    );
  }

  return std::nullopt;
}

std::vector<std::string> const_constraints(Value const& v)
{
  using namespace fmt::literals;

  auto atoms = std::vector<std::string>{};

  if(auto* cv = dyn_cast<Constant>(&v)) {
    auto name = get_name(*cv);
    atoms.push_back("({{{}}} is preexecution)"_format(name));

    if(cv->isZeroValue()) {
      auto type = cv->getType();
      if(type->isFloatingPointTy()) {
        atoms.push_back("({{{}}} is floating point zero)"_format(name));
      } else if(type->isIntegerTy()) {
        atoms.push_back("({{{}}} is integer zero)"_format(name));
      }
    }
  }

  return atoms;
}

// Constraint for the nth argument of I
// i.e. {v0} is first argument of {I}
std::string nth_arg_constraint(Instruction const& I, size_t n)
{
  using namespace fmt::literals;
  assert(n < I.getNumOperands() && 
         "Not enough operands to instruction");

  auto& operand = *I.getOperand(n);
  auto atoms = const_constraints(operand);

  atoms.push_back(
      "({{{arg}}} is {nth} argument of {{{instr}}})"_format(
      "arg"_a = get_name(operand),
      "nth"_a = nth_of(n),
      "instr"_a = get_name(I)
  ));

  return constraint_and(atoms);
}

std::optional<std::string> constraint(Instruction const& I)
{
  auto operands = I.getNumOperands();
  auto op_str = base_constraint(I);

  if(op_str && operands <= 3) {
    auto args = std::vector<std::string>{op_str.value()};

    for(auto n = 0u; n < operands; ++n) {
      args.push_back(nth_arg_constraint(I, n));
    }

    return constraint_and(args);
  }

  return std::nullopt;
}

std::optional<std::string> constraint(Function const& F)
{
  auto atoms = std::vector<std::string>{};

  for(auto const& BB : F) {
    for(auto const& I : BB) {
      if(auto con = constraint(I)) {
        atoms.push_back(con.value());
      }
    }
  }

  if(!atoms.empty()) {
    return constraint_and(atoms);
  }

  return std::nullopt;
}

}

namespace convert {

std::optional<std::string> to_idl(Function const& F)
{
  using namespace fmt::literals;

  if(auto con = detail::constraint(F)) {
    return "Constraint {name}\n{constraint}\nEnd"_format(
      "name"_a = detail::title_case(F.getName().str()),
      "constraint"_a = con.value()
    );
  }

  return std::nullopt;
}

}
