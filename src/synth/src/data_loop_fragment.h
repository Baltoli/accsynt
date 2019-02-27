#pragma once

#include "fragment.h"

namespace synth {

class data_loop_fragment : public fragment {
public:
  using fragment::add_child;

  data_loop_fragment(std::vector<props::value> args, frag_ptr before,
      frag_ptr body, frag_ptr after);

  data_loop_fragment(std::vector<props::value> args);

  bool operator==(data_loop_fragment const& other) const;
  bool operator!=(data_loop_fragment const& other) const;

  virtual bool equal_to(frag_ptr const& other) const override;

  virtual std::string to_str(size_t indent = 0) override;
  virtual void splice(
      compile_context& ctx, llvm::BasicBlock* entry, llvm::BasicBlock* exit);
  virtual bool add_child(frag_ptr&& f, size_t idx);

  virtual size_t count_holes() const override;

  friend void swap(data_loop_fragment& a, data_loop_fragment& b);

private:
  std::pair<llvm::Argument*, std::string> get_pointer(
      compile_context&, size_t idx);

  fragment::frag_ptr before_;
  fragment::frag_ptr body_;
  fragment::frag_ptr after_;

  size_t num_pointers_;
};
}
