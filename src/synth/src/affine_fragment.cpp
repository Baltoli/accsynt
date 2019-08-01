#include "affine_fragment.h"

#include <support/indent.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace support;
using namespace llvm;

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

void affine_fragment::splice(
    compile_context& ctx, BasicBlock* entry, BasicBlock* exit)
{
  auto& llvm_ctx = entry->getContext();
  auto const& inds = ctx.metadata_.indices;
  auto const& consts = ctx.metadata_.seeds;

  if (inds.empty()) {
    before_->splice(ctx, entry, exit);
    return;
  }

  auto affine_block = BasicBlock::Create(llvm_ctx, "affine", ctx.func_);
  before_->splice(ctx, entry, affine_block);

  auto B = IRBuilder<>(affine_block);
  auto idx = create_affine(B, consts, inds);
  auto ptr = ctx.argument(args_[0].param_val);
  auto gep = B.CreateGEP(ptr, idx, "affine.gep");
  auto load = B.CreateLoad(gep);
  ctx.metadata_.seeds.insert(load);

  B.CreateBr(exit);
  // Now create a block to hold the index computation
  // splice the before block in before it, and at the end splice the new block
  // to the exit
  // in the new block, set the irb location
  // then pass it to the affine sampling above
  // let it do the arithmetic
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

void swap(affine_fragment& a, affine_fragment& b)
{
  using std::swap;
  swap(a.before_, b.before_);
}

} // namespace synth
