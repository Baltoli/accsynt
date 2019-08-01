#pragma once

#include "fragment.h"

#include <support/llvm_utils.h>
#include <support/random.h>

namespace synth {

class affine_fragment : public fragment {
public:
  affine_fragment(std::vector<props::value> args, frag_ptr before);
  affine_fragment(std::vector<props::value> args);

  affine_fragment(affine_fragment const&) = default;
  affine_fragment& operator=(affine_fragment&) = default;

  affine_fragment(affine_fragment&&) = default;
  affine_fragment& operator=(affine_fragment&&) = default;

  bool operator==(affine_fragment const& other) const;
  bool operator!=(affine_fragment const& other) const;

  virtual bool equal_to(frag_ptr const& other) const override;

  virtual void splice(
      compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit);
  virtual bool add_child(frag_ptr f, size_t idx);

  virtual std::string to_str(size_t indent = 0) override;

  virtual size_t count_holes() const override;

  friend void swap(affine_fragment& a, affine_fragment& b);

protected:
  // Restrict this fragment to having things after it for simplicity - will help
  // to implement all the member functions that are awkward for multiple
  // children.
  fragment::frag_ptr before_;

private:
  template <typename Builder>
  llvm::Value* create_affine(Builder& b,
      std::set<llvm::Value*> const& constants,
      std::set<llvm::Value*> const& indices) const;
};

template <typename Builder>
llvm::Value* affine_fragment::create_affine(Builder& b,
    std::set<llvm::Value*> const& constants,
    std::set<llvm::Value*> const& indices) const
{
  constexpr auto is_int = [](auto v) { return v->getType()->isIntegerTy(); };

  auto affine_len = std::min(indices.size(), constants.size() + 1);

  auto c_shuf = std::vector<llvm::Value*>{};
  std::copy_if(
      constants.begin(), constants.end(), std::back_inserter(c_shuf), is_int);

  auto i_shuf = std::vector<llvm::Value*>{};
  std::copy_if(
      indices.begin(), indices.end(), std::back_inserter(i_shuf), is_int);

  auto engine = support::get_random_engine();
  std::shuffle(i_shuf.begin(), i_shuf.end(), engine);
  std::shuffle(c_shuf.begin(), c_shuf.end(), engine);

  auto summands = std::vector<llvm::Value*>{};

  auto i_prod = i_shuf.begin();
  auto c_prod = c_shuf.begin();

  summands.push_back(*i_prod++);

  for (auto i = 1u; i < affine_len; ++i) {
    summands.push_back(b.CreateMul(*i_prod++, *c_prod++, "affine.mul"));
  }

  return support::create_sum(b, summands.begin(), summands.end(), "affine.sum");
}

} // namespace synth
