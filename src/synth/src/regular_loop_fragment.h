#pragma once

#include "fragment.h"

namespace synth {

class regular_loop_fragment : public fragment {
public:
  using fragment::add_child;

  regular_loop_fragment(std::vector<props::value> args,
                        frag_ptr&& before, frag_ptr&& body, frag_ptr&& after);
  regular_loop_fragment(std::vector<props::value> args);

  regular_loop_fragment(regular_loop_fragment const& other);
  regular_loop_fragment& operator=(regular_loop_fragment other);

  regular_loop_fragment(regular_loop_fragment&& other);
  regular_loop_fragment& operator=(regular_loop_fragment&& other);

  bool operator==(regular_loop_fragment const& other) const;
  bool operator!=(regular_loop_fragment const& other) const;

  virtual bool equal_to(frag_ptr const& other) const override;

  virtual fragment::frag_ptr clone();

  virtual std::string to_str(size_t indent=0) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f, size_t idx);

  virtual size_t count_holes() const override;

  friend void swap(regular_loop_fragment& a, regular_loop_fragment& b);

private:
  llvm::Argument *get_pointer(compile_context&);
  llvm::Argument *get_size(compile_context&);

  fragment::frag_ptr before_;
  fragment::frag_ptr body_;
  fragment::frag_ptr after_;
};

}
