#include "fragment.h"

#include <support/assert.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace support;
using namespace llvm;

namespace presyn {

using namespace fmt::literals;

// Hole

/**
 * Composing anything with the hole fragment produces an hole fragment.
 */
std::unique_ptr<fragment> hole::compose(std::unique_ptr<fragment>&& other)
{
  return std::move(other);
}

bool hole::accepts() const { return true; }

/**
 * An hole fragment doesn't do anything when compiled - it just creates a new
 * block with a jump to the exit, then returns that new block as the fragment
 * entry.
 */
llvm::BasicBlock* hole::compile(sketch_context&, llvm::BasicBlock* exit) const
{
  auto frag_entry = BasicBlock::Create(
      thread_context::get(), "hole", exit->getParent(), exit);

  IRBuilder(frag_entry).CreateBr(exit);

  return frag_entry;
}

std::string hole::to_string() const { return "hole"; }

// Empty

/**
 * Composing anything with the empty fragment produces an empty fragment.
 */
std::unique_ptr<fragment> empty::compose(std::unique_ptr<fragment>&& other)
{
  return std::make_unique<empty>();
}

bool empty::accepts() const { return false; }

/**
 * An empty fragment doesn't do anything when compiled - it just creates a new
 * block with a jump to the exit, then returns that new block as the fragment
 * entry.
 */
llvm::BasicBlock* empty::compile(sketch_context&, llvm::BasicBlock* exit) const
{
  auto frag_entry = BasicBlock::Create(
      thread_context::get(), "empty", exit->getParent(), exit);

  IRBuilder(frag_entry).CreateBr(exit);

  return frag_entry;
}

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

llvm::BasicBlock*
linear::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto frag_entry = BasicBlock::Create(
      thread_context::get(), "linear", exit->getParent(), exit);

  auto build = IRBuilder(frag_entry);

  if (auto const_param = dynamic_cast<constant_int*>(instructions_.get())) {
    for (int i = 0; i < const_param->value(); ++i) {
      build.Insert(ctx.stub());
    }
  }

  build.CreateBr(exit);

  return frag_entry;
}

std::string linear::to_string() const
{
  return fmt::format("linear<{}>", *instructions_);
}

// Seq

seq::seq()
    : first_(std::make_unique<hole>())
    , second_(std::make_unique<hole>())
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

llvm::BasicBlock*
seq::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto second_entry = second_->compile(ctx, exit);
  return first_->compile(ctx, second_entry);
}

std::string seq::to_string() const
{
  assertion(first_ && second_, "Child fragments of seq should not be null");
  return fmt::format("seq({}, {})", *first_, *second_);
}

// Loop

loop::loop()
    : body_(std::make_unique<hole>())
{
}

std::unique_ptr<fragment> loop::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<loop>(std::move(other), body_);
}

bool loop::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
loop::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto frag_entry = BasicBlock::Create(
      thread_context::get(), "loop", exit->getParent(), exit);

  auto build = IRBuilder(frag_entry);
  auto cond = ctx.stub(build.getInt1Ty());
  build.Insert(cond);

  auto body_entry = body_->compile(ctx, frag_entry);
  build.CreateCondBr(cond, body_entry, exit);

  return frag_entry;
}

std::string loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("loop({})", *body_);
}

// Delimiter loop

delimiter_loop::delimiter_loop(std::unique_ptr<parameter>&& param)
    : pointer_(std::move(param))
    , body_(std::make_unique<hole>())
{
}

delimiter_loop::delimiter_loop(std::string name)
    : delimiter_loop(std::make_unique<named>(name))
{
}

std::unique_ptr<fragment>
delimiter_loop::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<delimiter_loop>(std::move(other), body_);
}

bool delimiter_loop::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
delimiter_loop::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto header = BasicBlock::Create(
      thread_context::get(), "delim.header", exit->getParent());

  auto entry = BasicBlock::Create(
      thread_context::get(), "delim.entry", exit->getParent(), header);

  auto tail = BasicBlock::Create(
      thread_context::get(), "delim.tail", exit->getParent());

  auto build = IRBuilder(entry);
  auto name = static_cast<named*>(pointer_.get())->name();
  auto initial_ptr = build.Insert(ctx.stub(name), "delim.initial");
  build.CreateBr(header);

  build.SetInsertPoint(header);
  auto phi = build.CreatePHI(initial_ptr->getType(), 2, "delim.ptr");
  phi->addIncoming(initial_ptr, entry);

  auto value = build.Insert(
      ctx.operation("load", {phi, build.getInt64(0)}), "delim.value");
  auto comp = build.Insert(ctx.stub(value->getType()), "delim.compare");
  auto cond = build.Insert(
      ctx.operation("eq", build.getInt1Ty(), {value, comp}), "delim.cond");

  auto body_entry = body_->compile(ctx, tail);
  build.CreateCondBr(cond, exit, body_entry);

  build.SetInsertPoint(tail);
  auto next_ptr = build.Insert(ctx.operation("inc", {phi}), "delim.next");
  phi->addIncoming(next_ptr, tail);
  build.CreateBr(header);

  return entry;
}

std::string delimiter_loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("delim<{}>({})", *pointer_, *body_);
}

// Fixed loop

fixed_loop_new::fixed_loop_new(
    std::unique_ptr<parameter>&& sz,
    std::vector<std::unique_ptr<parameter>>&& ptrs)
    : size_(std::move(sz))
    , pointers_(std::move(ptrs))
    , body_(std::make_unique<hole>())
{
}

std::unique_ptr<fragment>
fixed_loop_new::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<fixed_loop_new>(std::move(other), body_);
}

bool fixed_loop_new::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
fixed_loop_new::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  unimplemented();
  /* auto header = BasicBlock::Create( */
  /*     thread_context::get(), "fixed.header", exit->getParent()); */

  /* auto pre_header = BasicBlock::Create( */
  /*     thread_context::get(), "fixed.pre-header", exit->getParent(), header);
   */

  /* auto entry = BasicBlock::Create( */
  /*     thread_context::get(), "fixed.entry", exit->getParent(), pre_header);
   */

  /* auto tail = BasicBlock::Create( */
  /*     thread_context::get(), "fixed.tail", exit->getParent()); */

  /* auto build = IRBuilder(entry); */
  /* auto init_idx = build.getInt64(0); */
  /* build.CreateBr(pre_header); */

  /* Value* final_idx = nullptr; */
  /* if (auto cst_ptr = dynamic_cast<constant_int*>(size_.get())) { */
  /*   final_idx = build.getInt64(cst_ptr->value()); */
  /* } else if (auto named_ptr = dynamic_cast<named*>(size_.get())) { */
  /*   final_idx = build.Insert(ctx.stub(build.getInt64Ty(),
   * named_ptr->name())); */
  /* } */
  /* assertion(final_idx != nullptr, "Should be able to get an index"); */

  /* build.SetInsertPoint(pre_header); */
  /* auto idx = build.CreatePHI(init_idx->getType(), 2, "fixed.idx"); */
  /* idx->addIncoming(init_idx, entry); */
  /* auto cond = build.CreateICmpSLT(idx, final_idx); */
  /* build.CreateCondBr(cond, header, exit); */

  /* build.SetInsertPoint(header); */
  /* auto name = static_cast<named*>(pointer_.get())->name(); */
  /* auto ptr = build.Insert(ctx.stub(name), "fixed.ptr"); */
  /* build.Insert(ctx.operation("load", {ptr, idx}), "fixed.value"); */

  /* auto body_entry = body_->compile(ctx, tail); */
  /* build.CreateBr(body_entry); */

  /* build.SetInsertPoint(tail); */
  /* auto next_idx = build.CreateAdd(idx, build.getInt64(1), "fixed.next-idx");
   */
  /* idx->addIncoming(next_idx, tail); */
  /* build.CreateBr(pre_header); */

  /* return entry; */
}

std::string fixed_loop_new::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  if (pointers_.empty()) {
    return fmt::format("fixed<{}>({})", *size_, *body_);
  } else {
    auto strs = std::vector<std::string> {};
    for (auto const& ptr : pointers_) {
      strs.push_back(fmt::format("{}", *ptr));
    }
    return fmt::format(
        "fixed<{}, {}>({})", *size_, fmt::join(strs, ", "), *body_);
  }
}

// If

if_::if_()
    : body_(std::make_unique<hole>())
{
}

std::unique_ptr<fragment> if_::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<if_>(std::move(other), body_);
}

bool if_::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
if_::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto entry = BasicBlock::Create(
      thread_context::get(), "if.entry", exit->getParent());

  auto build = IRBuilder(entry);
  auto body_entry = body_->compile(ctx, exit);

  auto cond = build.Insert(ctx.stub(build.getInt1Ty()), "if.cond");
  build.CreateCondBr(cond, body_entry, exit);

  return entry;
}

std::string if_::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("if({})", *body_);
}

// If-else

if_else::if_else()
    : body_(std::make_unique<hole>())
    , else_body_(std::make_unique<hole>())
{
}

std::unique_ptr<fragment> if_else::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<if_else>(std::move(other), body_, else_body_);
}

bool if_else::accepts() const
{
  return body_->accepts() || else_body_->accepts();
}

llvm::BasicBlock*
if_else::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto entry = BasicBlock::Create(
      thread_context::get(), "if-else.entry", exit->getParent());

  auto build = IRBuilder(entry);
  auto body_entry = body_->compile(ctx, exit);
  auto else_entry = else_body_->compile(ctx, exit);

  auto cond = build.Insert(ctx.stub(build.getInt1Ty()), "if-else.cond");
  build.CreateCondBr(cond, body_entry, else_entry);

  return entry;
}

std::string if_else::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("if_else({}, {})", *body_, *else_body_);
}

// Affine

affine::affine(std::unique_ptr<parameter>&& ptr)
    : pointer_(std::move(ptr))
    , body_(std::make_unique<hole>())
{
}

affine::affine(std::string ptr_n)
    : affine(std::make_unique<named>(ptr_n))
{
}

std::unique_ptr<fragment> affine::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<affine>(std::move(other), body_);
}

bool affine::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
affine::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto entry = BasicBlock::Create(
      thread_context::get(), "affine.entry", exit->getParent(), exit);

  auto build = IRBuilder(entry);

  auto idx = build.Insert(
      ctx.operation("affine", build.getInt64Ty(), {}), "affine.idx");

  auto name = static_cast<named*>(pointer_.get())->name();
  auto ptr = build.Insert(ctx.stub(name), "affine.ptr");

  build.Insert(ctx.operation("load", {ptr, idx}), "affine.value");

  build.CreateBr(body_->compile(ctx, exit));
  return entry;
}

std::string affine::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("affine<{}>({})", *pointer_, *body_);
}

// Index

index::index(std::unique_ptr<parameter>&& ptr)
    : pointer_(std::move(ptr))
    , body_(std::make_unique<hole>())
{
}

index::index(std::string ptr_n)
    : index(std::make_unique<named>(ptr_n))
{
}

std::unique_ptr<fragment> index::compose(std::unique_ptr<fragment>&& other)
{
  return compose_generic<index>(std::move(other), body_);
}

bool index::accepts() const { return body_->accepts(); }

llvm::BasicBlock*
index::compile(sketch_context& ctx, llvm::BasicBlock* exit) const
{
  auto entry = BasicBlock::Create(
      thread_context::get(), "index.entry", exit->getParent(), exit);

  auto build = IRBuilder(entry);

  auto idx = build.Insert(
      ctx.operation("index", build.getInt64Ty(), {}), "index.idx");

  auto name = static_cast<named*>(pointer_.get())->name();
  auto ptr = build.Insert(ctx.stub(name), "index.ptr");

  build.Insert(ctx.operation("load", {ptr, idx}), "index.value");

  build.CreateBr(body_->compile(ctx, exit));
  return entry;
}

std::string index::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("index<{}>({})", *pointer_, *body_);
}

} // namespace presyn
