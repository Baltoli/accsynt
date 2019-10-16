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

  auto ptr_names = std::vector<std::string>{};
  std::transform(args_.begin() + 1, args_.end(), std::back_inserter(ptr_names),
      [](auto val) { return val.param_val; });

  auto shape = R"({before}
{ind1}loopToN({bound}) {{
{body}
{ind1}}}
{after})";

  return fmt::format(shape, "ind1"_a = ::support::indent{ ind },
      "ind2"_a = ::support::indent{ ind + 1 },
      "before"_a = string_or_empty(before_, ind),
      "body"_a = string_or_empty(body_, ind + 1),
      "after"_a = string_or_empty(after_, ind),
      "bound"_a = args_.at(0).param_val);
}

/* void regular_loop_fragment::splice( */
/*     compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit) */
/* { */
/* } */

/* std::pair<Argument*, std::string> regular_loop_fragment::get_pointer( */
/*     compile_context& ctx, size_t idx) */
/* { */
/* } */

/* void swap(regular_loop_fragment& a, regular_loop_fragment& b) {} */

/* bool regular_loop_fragment::operator==(regular_loop_fragment const& other)
 * const */

/* bool regular_loop_fragment::operator!=(regular_loop_fragment const& other)
 * const */

/* bool regular_loop_fragment::equal_to(frag_ptr const& other) const */

} // namespace synth
