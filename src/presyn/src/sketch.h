#pragma once

#include "candidate.h"
#include "fragment.h"

#include <props/props.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include <map>

namespace presyn {

/**
 * A sketch is an incomplete program. More concretely, a sketch represents a
 * program where some instructions have not yet been concretised. By choosing
 * concrete values for these instructions, sketches can be used to synthesise
 * executable programs.
 *
 * Sketches are created from a composition of fragments and a function
 * signature. Individual fragments within a composition know how to attach
 * themselves to an exit block given contextual information, but nothing more.
 * The sketch initiates this process at the root of the fragment tree and
 * connects the fragment code to the rest of the function.
 */
class sketch {
  friend class candidate;

public:
  sketch(props::signature sig, fragment const&);
  sketch(props::signature sig, std::unique_ptr<fragment> const&);

  llvm::Module& module();
  llvm::Module const& module() const;

protected:
  // Allow these members to be accessed by the candidate constructor
  std::unique_ptr<llvm::Module> module_;
  sketch_context ctx_;

private:
  llvm::Value* create_return_stub(llvm::BasicBlock*);

  std::map<llvm::Type*, llvm::Function*> stubs_;
};

} // namespace presyn
