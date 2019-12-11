#include "fragment.h"

#include <fmt/format.h>

namespace presyn {

// Empty

/**
 * Composing anything with the empty fragment produces the original fragment
 * again - it will be eliminated by any other fragment.
 */
std::unique_ptr<fragment> empty::compose(std::unique_ptr<fragment>&& other)
{
  return std::move(other);
}

bool empty::accepts() const { return false; }

std::string empty::to_string() const { return "empty()"; }

// Linear

linear::linear(int insts)
    : instructions_(insts)
{
}

std::unique_ptr<fragment> linear::compose(std::unique_ptr<fragment>&& other)
{
  return std::move(other);
}

bool linear::accepts() const { return false; }

std::string linear::to_string() const
{
  using namespace fmt::literals;
  return "linear({})"_format(instructions_);
}

} // namespace presyn
