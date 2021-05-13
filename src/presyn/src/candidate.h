#pragma once

#include "candidate_visitors.h"
#include "filler.h"
#include "sketch_context.h"

#include <support/llvm_types.h>

#include <props/props.h>

#include <llvm/IR/Module.h>

#include <map>
#include <memory>
#include <optional>

namespace presyn {

class sketch;

class candidate {
  friend class filler;

public:
  candidate(sketch&&, std::unique_ptr<filler>);

  bool is_valid();

  llvm::Type* hole_type() const;

  llvm::Function& function();
  llvm::Function const& function() const;

  llvm::Module& module();
  llvm::Module const& module() const;

  sketch_context& ctx();

protected:
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

  // A wrapper around LLVM RAUW that will handle changing types in the
  // instructions we're changing.
  //
  // We need this because RAUW (sensibly) doesn't allow you to change the type
  // of an operand - in our limited domain, we know that the calls to stub
  // declarations are variadic and we don't care about the types. Additionally,
  // we know that this is the only context in which our opaque stub type will
  // appear, so we're free to just change the type.
  //
  // Performing RAUW on a Phi node may create new holes that need to be filled -
  // this is part of the type refinement process. For example, consider a Phi
  // where both "arms" have opaque type. When a type or value is selected for
  // one of the incoming arms, all the other arms receive that type as well.
  std::set<llvm::CallInst*> safe_rauw(llvm::Instruction*, llvm::Value*);

  // This is responsible for creating a new stubbed call with an updated type
  // (but not for replacing the uses - delegate that back to safe_rauw.
  llvm::CallInst* update_type(llvm::CallInst*, llvm::Type*);

private:
  void resolve_names();
  void choose_values();
  void resolve_operators();
  void insert_phis(int n_per_type = 1);
  void hoist_phis();

  std::optional<std::string> arg_name(llvm::Value*) const;

  // The object we're delegating to for hole value selection (i.e. filling the
  // holes in).
  std::unique_ptr<filler> filler_;

  props::signature signature_;
  llvm::Module& module_;

  std::map<std::pair<llvm::Type*, llvm::Type*>, llvm::Function*> converters_
      = {};

  // Operators defined by special functions in sketches - these are things that
  // we know the abstract semantics for ahead of time (e.g. that a value should
  // be a load at a particular offset into a known pointer).
  //
  // Because types are not yet known when these operations are created by sketch
  // compilation, we represent them as named stub functions.
  llvm::Value* create_operation(llvm::CallInst&);

  // The canonical type for holes in this candidate. We always get this on
  // construction from the sketch context.
  llvm::Type* hole_type_;

  support::type_conversions type_convs_;

  sketch_context ctx_;
};

} // namespace presyn
