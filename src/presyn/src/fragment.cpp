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

bool empty::accepts() const { return true; }

std::string empty::to_string() const { return "empty()"; }

// Linear

linear::linear(int insts)
    : instructions_(insts)
{
}

std::unique_ptr<fragment> linear::compose(std::unique_ptr<fragment>&& other)
{
  return std::make_unique<linear>(instructions_);
}

bool linear::accepts() const { return false; }

std::string linear::to_string() const
{
  using namespace fmt::literals;
  return "linear({})"_format(instructions_);
}

// Seq

seq::seq()
    : seq(std::make_unique<empty>(), std::make_unique<empty>())
{
}

seq::seq(std::unique_ptr<fragment>&& fst, std::unique_ptr<fragment>&& snd)
    : first_(std::move(fst))
    , second_(std::move(snd))
{
}

std::unique_ptr<fragment> seq::compose(std::unique_ptr<fragment>&& other)
{
  auto ret
      = std::unique_ptr<seq>(new seq(std::move(first_), std::move(second_)));

  if (!ret->first_) {
    ret->first_ = std::move(other);
  } else if (!ret->second_) {
    ret->second_ = std::move(other);
  } else {
    if (ret->first_->accepts()) {
      ret->first_ = ret->first_->compose(std::move(other));
    } else if (ret->second_->accepts()) {
      ret->second_ = ret->second_->compose(std::move(other));
    }
  }

  return ret;
}

bool seq::accepts() const
{
  return (!first_ || !second_ || first_->accepts() || second_->accepts());
}

std::string seq::to_string() const
{
  using namespace fmt::literals;
  using namespace std::literals::string_literals;

  auto fst = [this] {
    if (first_) {
      return "{}"_format(first_->to_string());
    }
    return ""s;
  }();

  auto snd = [this] {
    if (second_) {
      return ", {}"_format(second_->to_string());
    }
    return ""s;
  }();

  return "seq({}{})"_format(fst, snd);
}

} // namespace presyn
