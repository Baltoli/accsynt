#include "loop_fragment.h"

using namespace props;
using namespace llvm;

namespace synth {

loop_fragment::loop_fragment(std::vector<props::value> args, frag_ptr before,
    frag_ptr body, frag_ptr after, bool output)
    : fragment(args)
    , before_(before)
    , body_(body)
    , after_(after)
    , num_pointers_(args_.size() - 1)
    , perform_output_(output)
{
  if (args_.size() < 2) {
    throw std::invalid_argument("Regular loop requires at least 2 arguments");
  }

  auto all_params = std::all_of(args_.begin(), args_.end(),
      [](auto arg) { return arg.value_type == value::type::parameter; });

  if (!all_params) {
    throw std::invalid_argument(
        "Regular loop arguments must all be parameter references");
  }
}

loop_fragment::loop_fragment(std::vector<value> args)
    : loop_fragment(args, nullptr, nullptr, nullptr, false)
{
}

loop_fragment::loop_fragment(std::vector<value> args, bool out)
    : loop_fragment(args, nullptr, nullptr, nullptr, out)
{
}

bool loop_fragment::add_child(frag_ptr f, size_t idx)
{
  auto children = children_ref(before_, body_, after_);

  for (frag_ptr& ch : children) {
    auto max = count_or_empty(ch);
    if (idx < max) {
      if (ch) {
        ch->add_child(f, idx);
      } else {
        ch = f;
      }

      return true;
    } else {
      idx -= max;
    }
  }

  throw std::invalid_argument("Too few holes in fragment");
}

size_t loop_fragment::count_holes() const
{
  return count_or_empty(before_) + count_or_empty(body_)
      + count_or_empty(after_);
}

std::pair<Argument*, std::string> loop_fragment::get_pointer(
    compile_context& ctx, size_t idx)
{
  auto name = args_.at(idx + 1).param_val;
  return { ctx.argument(name), name };
}

Argument* loop_fragment::get_size(compile_context& ctx)
{
  return ctx.argument(args_.at(0).param_val);
}

} // namespace synth
