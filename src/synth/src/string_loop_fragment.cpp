#include "string_loop_fragment.h"

#include <support/indent.h>

#include <fmt/format.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

using namespace props;
using namespace llvm;

namespace synth {

std::string string_loop_fragment::to_str(size_t ind)
{
  using namespace fmt::literals;

  auto ptr_names = std::vector<std::string>{};
  std::transform(args_.begin() + 1, args_.end(), std::back_inserter(ptr_names),
      [](auto val) { return val.param_val; });

  auto shape = R"({before}
{ind1}{name}({sz}, {ptrs}) {{
{body}
{ind1}}}
{after})";

  return fmt::format(shape,
      "name"_a = perform_output_ ? "stringOutputLoop" : "stringLoop",
      "ind1"_a = ::support::indent{ ind },
      "ind2"_a = ::support::indent{ ind + 1 },
      "before"_a = string_or_empty(before_, ind),
      "body"_a = string_or_empty(body_, ind + 1),
      "after"_a = string_or_empty(after_, ind),
      "ptrs"_a = fmt::join(
          ptr_names.begin(), ptr_names.end(), ", "), // args_.at(0).param_val,
      "sz"_a = args_.at(0).param_val);
}

void string_loop_fragment::splice(
    compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit)
{
  auto& llvm_ctx = entry->getContext();

  auto inter_first = BasicBlock::Create(llvm_ctx, "str-loop.inter0", ctx.func_);
  auto inter_second
      = BasicBlock::Create(llvm_ctx, "str-loop.inter1", ctx.func_);

  auto last_exit = entry;

  // Before

  before_->splice(ctx, last_exit, inter_first);
  last_exit = inter_first;

  // Body

  auto size = get_size(ctx);

  auto header = BasicBlock::Create(llvm_ctx, "str-loop.header", ctx.func_);
  auto pre_body = BasicBlock::Create(llvm_ctx, "str-loop.pre-body", ctx.func_);
  auto post_body
      = BasicBlock::Create(llvm_ctx, "str-loop.post-body", ctx.func_);

  auto B = IRBuilder<>(inter_first);
  B.CreateBr(header);

  B.SetInsertPoint(header);
  auto iter = B.CreatePHI(size->getType(), 2, "str-loop.iter");
  iter->addIncoming(ConstantInt::get(iter->getType(), 0), inter_first);
  auto cond = B.CreateICmpSLT(iter, size, "str-loop.cond");
  B.CreateCondBr(cond, pre_body, inter_second);

  B.SetInsertPoint(pre_body);
  for (auto i = 0u; i < num_pointers_; ++i) {
    auto [ptr, name] = get_pointer(ctx, i);
    auto geps = ctx.create_geps_for(name, iter, ptr, B, "str-loop.gep");

    for (auto gep : geps) {
      auto load = B.CreateLoad(gep, "str-loop.load");
      ctx.metadata_.seeds.insert(load);
    }
  }

  B.SetInsertPoint(post_body);
  auto next = B.CreateAdd(
      iter, ConstantInt::get(iter->getType(), 1), "str-loop.next-iter");
  iter->addIncoming(next, post_body);

  if (perform_output_) {
    auto [ptr, name] = get_pointer(ctx, 0);
    auto geps = ctx.create_geps_for(name, iter, ptr, B, "out-loop.gep");

    for (auto gep : geps) {
      ctx.metadata_.outputs.insert(cast<Instruction>(gep));
    }
  }

  B.CreateBr(header);

  body_->splice(ctx, pre_body, post_body);
  last_exit = inter_second;

  // After

  after_->splice(ctx, last_exit, exit);
}

void swap(string_loop_fragment& a, string_loop_fragment& b)
{
  using std::swap;
  swap(a.before_, b.before_);
  swap(a.body_, b.body_);
  swap(a.after_, b.after_);
  swap(a.args_, b.args_);
  swap(a.perform_output_, b.perform_output_);
}

bool string_loop_fragment::operator==(string_loop_fragment const& other) const
{
  auto equal_non_null = [](auto const& a, auto const& b) {
    if (!a && !b) {
      return true;
    } else if (!a || !b) {
      return false;
    } else {
      return a->equal_to(b);
    }
  };

  return args_ == other.args_ && equal_non_null(before_, other.before_)
      && equal_non_null(body_, other.body_)
      && equal_non_null(after_, other.after_)
      && perform_output_ == other.perform_output_;
}

bool string_loop_fragment::operator!=(string_loop_fragment const& other) const
{
  return !(*this == other);
}

bool string_loop_fragment::equal_to(frag_ptr const& other) const
{
  return other->equal_as(*this);
}

} // namespace synth
