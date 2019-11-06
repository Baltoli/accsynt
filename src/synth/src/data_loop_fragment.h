#pragma once

#include "fragment.h"
#include "loop_fragment.h"

namespace synth {

class data_loop_fragment : public loop_fragment {
public:
  using fragment::add_child;
  using loop_fragment::loop_fragment;

  bool operator==(data_loop_fragment const& other) const;
  bool operator!=(data_loop_fragment const& other) const;

  bool equal_to(frag_ptr const& other) const override;

  std::string to_str(size_t indent = 0) override;
  void splice(compile_context& ctx, llvm::BasicBlock* entry,
      llvm::BasicBlock* exit) override;

  int get_id() const override;

  friend void swap(data_loop_fragment& a, data_loop_fragment& b);

  static char ID;

private:
  std::pair<llvm::Argument*, std::string> get_pointer(
      compile_context&, size_t idx);

  size_t num_pointers_;
};

} // namespace synth
