#include "affine_fragment.h"

#include "fragment_id.h"

#include <support/indent.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace support;
using namespace llvm;

namespace synth {

affine_fragment::affine_fragment(std::vector<props::value> args, frag_ptr after)
    : fragment(args)
    , after_(after)
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
    after_->splice(ctx, entry, exit);
    return;
  }

  auto affine_block = BasicBlock::Create(llvm_ctx, "affine", ctx.func_);
  auto B = IRBuilder<>(entry);
  B.CreateBr(affine_block);

  B.SetInsertPoint(affine_block);
  auto idx = create_affine(B, consts, inds);
  auto ptr = ctx.argument(args_[0].param_val);
  auto gep = B.CreateGEP(ptr, idx, "affine.gep");
  auto load = B.CreateLoad(gep);
  ctx.metadata_.seeds.insert(load);

  after_->splice(ctx, affine_block, exit);
  // Now create a block to hold the index computation
  // splice the before block in before it, and at the end splice the new block
  // to the exit
  // in the new block, set the irb location
  // then pass it to the affine sampling above
  // let it do the arithmetic
}

bool affine_fragment::add_child(frag_ptr f, size_t idx)
{
  auto max = count_or_empty(after_);
  if (idx < max) {
    if (after_) {
      after_->add_child(f, idx);
    } else {
      after_ = f;
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

  auto shape = R"({ind}affine({name})
{after})";

  return fmt::format(shape, "after"_a = string_or_empty(after_, indent),
      "ind"_a = ::support::indent { indent }, "name"_a = args_.at(0).param_val);
}

int affine_fragment::get_id() const { return get_fragment_id(*this); }

size_t affine_fragment::count_holes() const { return count_or_empty(after_); }

bool affine_fragment::operator==(affine_fragment const& other) const
{
  return args_ == other.args_
      && (after_ ? after_->equal_to(other.after_) : !other.after_);
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
  swap(a.after_, b.after_);
}

char affine_fragment::ID = 0;
static register_fragment_id<affine_fragment> X;

} // namespace synth
