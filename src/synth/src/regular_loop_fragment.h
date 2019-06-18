#pragma once

#include "fragment.h"
#include "loop_fragment.h"

#include <utility>

namespace synth {

class regular_loop_fragment : public loop_fragment {
public:
  using fragment::add_child;
  using loop_fragment::loop_fragment;

  bool operator==(regular_loop_fragment const& other) const;
  bool operator!=(regular_loop_fragment const& other) const;

  virtual bool equal_to(frag_ptr const& other) const override;

  virtual std::string to_str(size_t indent = 0) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock* entry,
      llvm::BasicBlock* exit) override;

  friend void swap(regular_loop_fragment& a, regular_loop_fragment& b);
};

} // namespace synth
