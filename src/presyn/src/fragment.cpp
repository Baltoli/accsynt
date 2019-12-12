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

// Seq

seq::seq()
    : seq(nullptr, nullptr)
{
}

seq::seq(std::unique_ptr<fragment>&& fst, std::unique_ptr<fragment>&& snd)
    : first_(std::move(fst))
    , second_(std::move(snd))
{
}

std::unique_ptr<fragment> seq::compose(std::unique_ptr<fragment>&& other)
{
  auto ret = std::unique_ptr<fragment>(
      new seq(std::move(first_), std::move(second_)));
  return ret;
}

bool seq::accepts() const { return false; }

std::string seq::to_string() const { return "Seq()"; }

} // namespace presyn
