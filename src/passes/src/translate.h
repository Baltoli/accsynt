#pragma once

#include <fmt/format.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>

#include <optional>

namespace convert {

std::optional<std::string> to_idl(llvm::Function const& F);
}

namespace convert::detail {

std::string nth_of(size_t i);
std::string title_case(std::string in);

std::optional<std::string> base_constraint(llvm::Instruction const& I);
std::string nth_arg_constraint(llvm::Instruction const& I, size_t n);

std::optional<std::string> constraint(llvm::Instruction const& I);
std::optional<std::string> constraint(llvm::Function const& F);

// Combine constraints into one by wrapping them in braces and forming their
// conjunction
template <typename Iterator>
std::string constraint_and(Iterator begin, Iterator end)
{
  using namespace fmt::literals;
  assert(begin != end && "Cannot handle empty conjunctions");

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
} // namespace convert::detail
