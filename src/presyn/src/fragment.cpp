#include "fragment.h"

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

std::string linear::to_string() const { return "linear()"; }

} // namespace presyn
