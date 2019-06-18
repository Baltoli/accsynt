#include "fragment.h"

namespace synth {

class loop_fragment : public fragment {
public:
  using fragment::add_child;

  loop_fragment(std::vector<props::value> args, frag_ptr before, frag_ptr body,
      frag_ptr after, bool output);

  loop_fragment(std::vector<props::value> args);
  loop_fragment(std::vector<props::value> args, bool out);

  bool operator==(loop_fragment const& other) const;
  bool operator!=(loop_fragment const& other) const;

  virtual bool add_child(frag_ptr f, size_t idx) override;
  virtual size_t count_holes() const override;

protected:
  std::pair<llvm::Argument*, std::string> get_pointer(
      compile_context&, size_t idx);
  llvm::Argument* get_size(compile_context&);

  fragment::frag_ptr before_;
  fragment::frag_ptr body_;
  fragment::frag_ptr after_;

  size_t num_pointers_;

  bool perform_output_;
};

} // namespace synth
