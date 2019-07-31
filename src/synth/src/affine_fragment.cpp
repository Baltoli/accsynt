#include "affine_fragment.h"

#include <support/indent.h>

#include <fmt/format.h>

namespace synth {

affine_fragment::affine_fragment(
    std::vector<props::value> args, frag_ptr before)
    : fragment(args)
    , before_(before)
{
}

affine_fragment::affine_fragment(std::vector<props::value> args)
    : affine_fragment(args, nullptr)
{
}

bool affine_fragment::operator==(affine_fragment const& other) const
{
  return args_ == other.args_
      && (before_ ? before_->equal_to(other.before_) : !other.before_);
}

bool affine_fragment::operator!=(affine_fragment const& other) const
{
  return !(*this == other);
}

bool affine_fragment::equal_to(frag_ptr const& other) const
{
  return other->equal_as(*this);
}

void affine_fragment::splice(
    compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit)
{
  // TODO
}

bool affine_fragment::add_child(frag_ptr f, size_t idx)
{
  auto max = count_or_empty(before_);
  if (idx < max) {
    if (before_) {
      before_->add_child(f, idx);
    } else {
      before_ = f;
    }

    return true;
  } else {
    idx -= max;
  }

  throw std::invalid_argument("Too few holes in fragment");
}

std::string affine_fragment::to_str(size_t indent)
{
  using namespace fmt::literals;

  auto shape = R"({before}
{ind}affine({name}))";

  return fmt::format(shape, "before"_a = string_or_empty(before_, indent),
      "ind"_a = ::support::indent{ indent }, "name"_a = args_.at(0).param_val);
}

size_t affine_fragment::count_holes() const { return count_or_empty(before_); }

void swap(affine_fragment& a, affine_fragment& b)
{
  using std::swap;
  swap(a.before_, b.before_);
}

} // namespace synth
