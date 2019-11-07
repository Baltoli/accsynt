#include "data_loop_fragment.h"

#include "fragment_id.h"

using namespace props;

namespace synth {

std::string data_loop_fragment::to_str(size_t ind)
{
  using namespace fmt::literals;

  auto ptr_names = std::vector<std::string> {};
  std::transform(args_.begin(), args_.end(), std::back_inserter(ptr_names),
      [](auto val) { return val.param_val; });

  auto shape = R"({before}
{ind1}dataLoop({ptrs}) {{
{body}
{ind1}}}
{after})";

  return fmt::format(shape, "ind1"_a = ::support::indent { ind },
      "ind2"_a = ::support::indent { ind + 1 },
      "before"_a = string_or_empty(before_, ind),
      "body"_a = string_or_empty(body_, ind + 1),
      "after"_a = string_or_empty(after_, ind),
      "ptrs"_a = fmt::join(ptr_names.begin(), ptr_names.end(), ", "));
}

void data_loop_fragment::splice(
    compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit)
{
  // TODO: throw if any children null - empty fragments fill this role

  /* auto& llvm_ctx = entry->getContext(); */

  /* auto inter_first = BasicBlock::Create(llvm_ctx, "reg-loop.inter0",
   * ctx.func_); */
  /* auto inter_second = BasicBlock::Create(llvm_ctx, "reg-loop.inter1",
   * ctx.func_); */

  /* auto last_exit = entry; */

  /* // Before */

  /* before_->splice(ctx, last_exit, inter_first); */
  /* last_exit = inter_first; */

  /* // Body */

  /* auto size = get_size(ctx); */

  /* auto header = BasicBlock::Create(llvm_ctx, "reg-loop.header", ctx.func_);
   */
  /* auto pre_body = BasicBlock::Create(llvm_ctx, "reg-loop.pre-body",
   * ctx.func_); */
  /* auto post_body = BasicBlock::Create(llvm_ctx, "reg-loop.post-body",
   * ctx.func_); */

  /* auto B = IRBuilder<>(inter_first); */
  /* B.CreateBr(header); */

  /* B.SetInsertPoint(header); */
  /* auto iter = B.CreatePHI(size->getType(), 2, "reg-loop.iter"); */
  /* iter->addIncoming(ConstantInt::get(iter->getType(), 0), inter_first); */
  /* auto cond = B.CreateICmpSLT(iter, size, "reg-loop.cond"); */
  /* B.CreateCondBr(cond, pre_body, inter_second); */

  /* B.SetInsertPoint(pre_body); */
  /* for(auto i = 0u; i < num_pointers_; ++i) { */
  /*   auto [ptr, name] = get_pointer(ctx, i); */
  /*   auto geps = ctx.create_geps_for(name, iter, ptr, B, "reg-loop.gep"); */

  /*   for(auto gep : geps) { */
  /*     auto load = B.CreateLoad(gep, "reg-loop.load"); */
  /*     ctx.metadata_.seeds.insert(load); */
  /*   } */
  /* } */

  /* B.SetInsertPoint(post_body); */
  /* auto next = B.CreateAdd(iter, ConstantInt::get(iter->getType(), 1),
   * "reg-loop.next-iter"); */
  /* iter->addIncoming(next, post_body); */

  /* if(perform_output_) { */
  /*   auto [ptr, name] = get_pointer(ctx, 0); */
  /*   auto geps = ctx.create_geps_for(name, iter, ptr, B, "out-loop.gep"); */

  /*   for(auto gep : geps) { */
  /*     ctx.metadata_.outputs.insert(cast<Instruction>(gep)); */
  /*   } */
  /* } */

  /* B.CreateBr(header); */

  /* body_->splice(ctx, pre_body, post_body); */
  /* last_exit = inter_second; */

  /* // After */

  /* after_->splice(ctx, last_exit, exit); */
}

void swap(data_loop_fragment& a, data_loop_fragment& b)
{
  using std::swap;
  swap(a.before_, b.before_);
  swap(a.body_, b.body_);
  swap(a.after_, b.after_);
  swap(a.args_, b.args_);
}

bool data_loop_fragment::operator==(data_loop_fragment const& other) const
{
  return args_ == other.args_ && equal_non_null(before_, other.before_)
      && equal_non_null(body_, other.body_)
      && equal_non_null(after_, other.after_);
}

bool data_loop_fragment::operator!=(data_loop_fragment const& other) const
{
  return !(*this == other);
}

bool data_loop_fragment::equal_to(frag_ptr const& other) const
{
  return other->equal_as(*this);
}

int data_loop_fragment::get_id() const { return get_fragment_id(*this); }

char data_loop_fragment::ID = 0;
static register_fragment_id<data_loop_fragment> X;

} // namespace synth
