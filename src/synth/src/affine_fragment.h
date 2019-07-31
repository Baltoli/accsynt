#pragma once

#include "fragment.h"

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
};

} // namespace synth
