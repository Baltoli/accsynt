#pragma once

#include <props/props.h>

#include <llvm/IR/Module.h>

#include <map>
#include <memory>
#include <optional>

namespace presyn {

class candidate {
public:
  candidate(props::signature, std::unique_ptr<llvm::Module>&&);

  bool is_valid() const;

  llvm::Function& function() const;

private:
  void resolve_names();
  void choose_values();
  void resolve_operators();

  std::optional<std::string> arg_name(llvm::Value*) const;

  props::signature signature_;
  std::unique_ptr<llvm::Module> module_;

  // A converter is essentially the identity function, but one that performs
  // sensible conversions as well.
  //
  // For example, this is useful to go from parameters (always simple i32 /
  // floats) to the internal types used, which are wider.
  //
  // Additionally, it preserves locality and allows the correct representation
  // of arbitrary values as instructions - this is important because we're often
  // working at a level earlier than LLVM's own RAUW supports.
  llvm::Function* converter(llvm::Type*, llvm::Type*);
  std::map<std::pair<llvm::Type*, llvm::Type*>, llvm::Function*> converters_
      = {};
};

} // namespace presyn
