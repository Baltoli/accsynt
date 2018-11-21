#pragma once

#include <props/props.h>

#include <llvm/IR/Module.h>

#include <vector>

namespace synth {

/**
 * Information and helper methods for compiling fragments. Responsible for
 * interfacing with an LLVM function, keeping track of a signature etc.
 */
class compile_context {
public:
  compile_context(llvm::Module& mod,
                  props::signature sig);
 
private:
  llvm::Module& mod_;
  props::signature sig_;
};

class fragment {
public:
  using frag_ptr = std::unique_ptr<fragment>;

  /**
   * Instantiate a fragment based on matched arguments from an inference rule.
   * This doesn't receive a signature because the compilation context is
   * responsible for that - means that fragments are portable across functions
   * with differently ordered parameters etc.
   */
  fragment(std::vector<props::value> args);

  /**
   * Print this fragment to an ostream, with an overload for indentation to
   * allow for printing children nested as appropriate.
   */
  virtual void print(std::ostream& os) = 0;
  virtual void print(std::ostream& os, size_t indent) = 0;

  /**
   * Compile this fragment to LLVM using ctx, which contains all the information
   * needed to do so (attachment blocks, signature for parameter index mapping,
   * etc).
   */
  virtual llvm::Function* compile(compile_context&& ctx) = 0;

  /**
   * Recursive primitive that makes up compilation - insert this fragment
   * between two basic blocks.
   */
  virtual void splice(llvm::BasicBlock *entry, llvm::BasicBlock *exit) = 0;

  /**
   * Adds a new child fragment to this one - will recurse into existing children
   * if necessary in order to achieve the "first empty hole" part of the
   * semantics.
   *
   * Returns true if the child was added, and false if not. Subclasses are
   * responsible for managing their own insertion logic (i.e. keeping track of
   * how many children they have).
   *
   * The child pointer passed into this one is moved from even if insertion
   * fails.
   */
  virtual bool add_child(frag_ptr&& f) = 0;

protected:
  std::vector<props::value> args_;
  std::vector<frag_ptr> children_ = {};
};

}
