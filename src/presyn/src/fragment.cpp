#include "fragment.h"

#include <support/assert.h>

#include <fmt/format.h>

namespace presyn {

using namespace fmt::literals;

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

std::string empty::to_string() const { return "empty"; }

// Linear

linear::linear(std::unique_ptr<parameter>&& insts)
    : instructions_(std::move(insts))
{
}

linear::linear(int insts)
    : instructions_(std::make_unique<constant_int>(insts))
{
}

std::unique_ptr<fragment> linear::compose(std::unique_ptr<fragment>&& other)
{
  return std::make_unique<linear>(std::move(instructions_));
}

bool linear::accepts() const { return false; }

std::string linear::to_string() const
{
  return "linear<{}>"_format(instructions_->to_string());
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
  assumes(first_ && second_, "Child fragments of seq should not be null");

  auto ret
      = std::unique_ptr<seq>(new seq(std::move(first_), std::move(second_)));

  if (ret->first_->accepts()) {
    ret->first_ = ret->first_->compose(std::move(other));
  } else if (ret->second_->accepts()) {
    ret->second_ = ret->second_->compose(std::move(other));
  }

  return ret;
}

bool seq::accepts() const
{
  assertion(first_ && second_, "Child fragments of seq should not be null");
  return first_->accepts() || second_->accepts();
}

std::string seq::to_string() const
{
  assertion(first_ && second_, "Child fragments of seq should not be null");
  return "seq({}, {})"_format(first_->to_string(), second_->to_string());
}

// Loop

loop::loop()
    : loop(std::make_unique<empty>())
{
}

loop::loop(std::unique_ptr<fragment>&& body)
    : body_(std::move(body))
{
}

std::unique_ptr<fragment> loop::compose(std::unique_ptr<fragment>&& other)
{
  assumes(body_, "Child fragment should not be null");

  auto ret = std::unique_ptr<loop>(new loop(std::move(body_)));
  if (ret->body_->accepts()) {
    ret->body_ = ret->body_->compose(std::move(other));
  }

  return ret;
}

bool loop::accepts() const { return body_->accepts(); }

std::string loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");

  return "loop({})"_format(body_->to_string());
}

} // namespace presyn
