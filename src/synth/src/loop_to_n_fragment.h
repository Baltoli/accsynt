#include "fragment.h"
#include "loop_fragment.h"

namespace synth {

class loop_to_n_fragment : public loop_fragment {
public:
  enum class direction { upwards, downwards };

  using fragment::add_child;

  loop_to_n_fragment(std::vector<props::value> args);
  loop_to_n_fragment(std::vector<props::value> args, direction dir);

  bool operator==(loop_to_n_fragment const& other) const;
  bool operator!=(loop_to_n_fragment const& other) const;

  bool equal_to(frag_ptr const& other) const override;
  int get_id() const override;

  std::string to_str(size_t indent = 0) override;
  void splice(compile_context& ctx, llvm::BasicBlock* entry,
      llvm::BasicBlock* exit) override;

  friend void swap(loop_to_n_fragment& a, loop_to_n_fragment& b);

  static char ID;

private:
  direction direction_;

  std::pair<llvm::Argument*, std::string> get_bound(compile_context&);
};

} // namespace synth
