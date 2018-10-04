#pragma once

#include <fmt/format.h>

#include <llvm/IR/Instruction.h>

#include <optional>

namespace convert {

std::string nth_of(size_t i);
std::optional<std::string> base_constraint(llvm::Instruction const& I);
std::string nth_arg_constraint(llvm::Instruction const& I, size_t n);

std::optional<std::string> constraint(llvm::Instruction const& I);

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

}
