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

llvm::BasicBlock* loop::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
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
delimiter_loop::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
}

std::string delimiter_loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("delim<{}>({})", *pointer_, *body_);
}

// Fixed loop

fixed_loop::fixed_loop(
    std::unique_ptr<parameter>&& ptr, std::unique_ptr<parameter>&& sz)
    : pointer_(std::move(ptr))
    , size_(std::move(sz))
    , body_(std::make_unique<hole>())
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

llvm::BasicBlock* fixed_loop::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
}

std::string fixed_loop::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("fixed<{}, {}>({})", *pointer_, *size_, *body_);
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

llvm::BasicBlock* if_::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
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

llvm::BasicBlock* if_else::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
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

llvm::BasicBlock* affine::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
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

llvm::BasicBlock* index::compile(sketch_context&, llvm::BasicBlock*) const
{
  unimplemented();
}

std::string index::to_string() const
{
  assumes(body_, "Child fragment should not be null");
  return fmt::format("index<{}>({})", *pointer_, *body_);
}

} // namespace presyn
