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
    : linear(std::make_unique<constant_int>(insts))
{
}

std::unique_ptr<fragment> linear::compose(std::unique_ptr<fragment>&& other)
{
  return std::make_unique<linear>(std::move(*this));
}

bool linear::accepts() const { return false; }

std::string linear::to_string() const
{
  return "linear<{}>"_format(instructions_->to_string());
}

// Seq

seq::seq()
    : first_(std::make_unique<empty>())
    , second_(std::make_unique<empty>())
{
}

std::unique_ptr<fragment> seq::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<seq>(std::move(other), first_, second_);
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
    : body_(std::make_unique<empty>())
{
}

std::unique_ptr<fragment> loop::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<loop>(std::move(other), body_);
}

bool loop::accepts() const { return body_->accepts(); }

std::string loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");

  return "loop({})"_format(body_->to_string());
}

// Delimiter loop

delimiter_loop::delimiter_loop(std::unique_ptr<parameter>&& param)
    : pointer_(std::move(param))
    , body_(std::make_unique<empty>())
{
}

delimiter_loop::delimiter_loop(std::string name)
    : delimiter_loop(std::make_unique<named>(name))
{
}

std::unique_ptr<fragment> delimiter_loop::compose(
    std::unique_ptr<fragment>&& other)
{
  return compose_generic<delimiter_loop>(std::move(other), body_);
}

bool delimiter_loop::accepts() const { return body_->accepts(); }

std::string delimiter_loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");

  return "delim_loop<{}>({})"_format(pointer_->to_string(), body_->to_string());
}

// Fixed loop

fixed_loop::fixed_loop(
    std::unique_ptr<parameter>&& ptr, std::unique_ptr<parameter>&& sz)
    : pointer_(std::move(ptr))
    , size_(std::move(sz))
    , body_(std::make_unique<empty>())
{
}

fixed_loop::fixed_loop(std::string ptr_n, std::string sz_n)
    : fixed_loop(std::make_unique<named>(ptr_n), std::make_unique<named>(sz_n))
{
}

std::unique_ptr<fragment> fixed_loop::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<fixed_loop>(std::move(other), body_);
}

bool fixed_loop::accepts() const { return body_->accepts(); }

std::string fixed_loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");

  return "fixed_loop<{}, {}>({})"_format(
      pointer_->to_string(), size_->to_string(), body_->to_string());
}

} // namespace presyn
