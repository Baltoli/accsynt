#include "loop_to_n_fragment.h"

#include <support/indent.h>

#include <fmt/format.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

using namespace props;
using namespace llvm;

namespace synth {

std::string loop_to_n_fragment::to_str(size_t ind)
{
  using namespace fmt::literals;

  auto ptr_names = std::vector<std::string> {};
  std::transform(args_.begin() + 1, args_.end(), std::back_inserter(ptr_names),
      [](auto val) { return val.param_val; });

  auto shape = R"({before}
{ind1}loopToN({bound}) {{
{body}
{ind1}}}
{after})";

  return fmt::format(shape, "ind1"_a = ::support::indent { ind },
      "ind2"_a = ::support::indent { ind + 1 },
      "before"_a = string_or_empty(before_, ind),
      "body"_a = string_or_empty(body_, ind + 1),
      "after"_a = string_or_empty(after_, ind),
      "bound"_a = args_.at(0).param_val);
}

void loop_to_n_fragment::splice(
    compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit)
{
}

std::pair<Argument*, std::string> loop_to_n_fragment::get_bound(
    compile_context& ctx)
{
  auto name = args_.at(0).param_val;
  return { ctx.argument(name), name };
}

void swap(loop_to_n_fragment& a, loop_to_n_fragment& b)
{
  using std::swap;
  swap(a.before_, b.before_);
  swap(a.body_, b.body_);
  swap(a.after_, b.after_);
  swap(a.args_, b.args_);
}

bool loop_to_n_fragment::operator==(loop_to_n_fragment const& other) const
{
  return args_ == other.args_ && equal_non_null(before_, other.before_)
      && equal_non_null(body_, other.body_)
      && equal_non_null(after_, other.after_);
}

bool loop_to_n_fragment::operator!=(loop_to_n_fragment const& other) const
{
  return !(*this == other);
}

bool loop_to_n_fragment::equal_to(frag_ptr const& other) const
{
  return other->equal_as(*this);
}

} // namespace synth
