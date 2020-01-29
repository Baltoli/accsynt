#pragma once

#include "candidate_visitors.h"

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

  llvm::Module& module();
  llvm::Module const& module() const;

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

  // A wrapper around LLVM RAUW that will handle changing types in the
  // instructions we're changing.
  //
  // We need this because RAUW (sensibly) doesn't allow you to change the type
  // of an operand - in our limited domain, we know that the calls to stub
  // declarations are variadic and we don't care about the types. Additionally,
  // we know that this is the only context in which our opaque stub type will
  // appear, so we're free to just change the type.
  void safe_rauw(llvm::CallInst*, llvm::Value*);

  // Operators defined by special functions in sketches - these are things that
  // we know the abstract semantics for ahead of time (e.g. that a value should
  // be a load at a particular offset into a known pointer).
  //
  // Because types are not yet known when these operations are created by sketch
  // compilation, we represent them as named stub functions.
  llvm::Value* create_operation(llvm::StringRef, llvm::Value*, llvm::Value*);
};

} // namespace presyn
