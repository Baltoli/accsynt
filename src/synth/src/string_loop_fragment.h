#pragma once

#include "fragment.h"
#include "loop_fragment.h"

#include <utility>

namespace synth {

class string_loop_fragment : public loop_fragment {
public:
  using fragment::add_child;
  using loop_fragment::loop_fragment;

  bool operator==(string_loop_fragment const& other) const;
  bool operator!=(string_loop_fragment const& other) const;

  bool equal_to(frag_ptr const& other) const override;

  std::string to_str(size_t indent = 0) override;
  void splice(compile_context& ctx, llvm::BasicBlock* entry,
      llvm::BasicBlock* exit) override;

  int get_id() const override;

  friend void swap(string_loop_fragment& a, string_loop_fragment& b);

  static char ID;

private:
  std::pair<llvm::Argument*, std::string> get_pointer(
      compile_context&, size_t idx);
};

} // namespace synth
