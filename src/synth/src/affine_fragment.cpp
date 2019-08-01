#include "affine_fragment.h"

#include <support/indent.h>
#include <support/random.h>

#include <fmt/format.h>

using namespace support;

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

// Takes by value so that we can shuffle and sample without replacement - means
// less random sampling I think, and more just getting the right information.
llvm::Value* affine_fragment::create_affine(
    std::set<llvm::Value*> const& constants,
    std::set<llvm::Value*> const& indices) const
{
  constexpr auto is_int = [](auto v) { return v->getType()->isIntegerTy(); };

  auto affine_len = std::min(indices.size(), constants.size() + 1);

  auto c_shuf = std::vector<llvm::Value*>{};
  std::copy(constants.begin(), constants.end(), std::back_inserter(c_shuf));

  auto i_shuf = std::vector<llvm::Value*>{};
  std::copy(indices.begin(), indices.end(), std::back_inserter(i_shuf));

  auto engine = get_random_engine();
  std::shuffle(i_shuf.begin(), i_shuf.end(), engine);
  std::shuffle(c_shuf.begin(), c_shuf.end(), engine);

  auto summands = std::vector<llvm::Value*>{};

  auto i_prod = i_shuf.begin();
  auto c_prod = c_shuf.begin();

  summands.push_back(*i_prod++);

  for (auto i = 1u; i < affine_len; ++i) {
  }

  return nullptr;
}

void affine_fragment::splice(
    compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit)
{
  auto& llvm_ctx = entry->getContext();
  auto& inds = ctx.metadata_.indices;

  if (inds.empty()) {
    before_->splice(ctx, entry, exit);
    return;
  }

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
