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

  virtual bool equal_to(frag_ptr const& other) const override;

  virtual std::string to_str(size_t indent = 0) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock* entry,
      llvm::BasicBlock* exit) override;

  friend void swap(loop_to_n_fragment& a, loop_to_n_fragment& b);

private:
  direction direction_;

  std::pair<llvm::Argument*, std::string> get_bound(compile_context&);
};

} // namespace synth
