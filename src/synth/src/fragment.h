#pragma once

#include <props/props.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <set>
#include <vector>

namespace synth {

class fragment;

/**
 * The metadata we collect during compilation is:
 *  * The function itself will be returned as part of this object.
 *  * A set of seed values.
 *  * A set of blocks to use as data blocks.
 *  * A set of output locations to be stored to.
 */
struct compile_metadata {
  llvm::Function *function;
  std::set<llvm::Value *> seeds = {};
  std::set<llvm::BasicBlock *> data_blocks = {};
  std::set<llvm::Value *> outputs = {};

  explicit compile_metadata(llvm::Function *fn);
};

/**
 * Information and helper methods for compiling fragments. Responsible for
 * interfacing with an LLVM function, keeping track of a signature etc.
 */
class compile_context {
  friend class fragment;

public:
  compile_context(llvm::Module& mod,
                  props::signature sig);
 
  /**
   * Don't want these to be copyable - once used to compile they are done as we
   * create the function and fill it up.
   */
  compile_context(compile_context const&) = delete;
  compile_context& operator=(compile_context const&) = delete;

  // TODO: define these and add a flag to the object that checks for
  // use-after-move?
  compile_context(compile_context&&) = default;
  compile_context& operator=(compile_context&&) = default;

  /**
   * Get the LLVM arg for the parameter name passed in. This lives in the
   * context because it depends on the signature.
   */
  llvm::Argument *argument(std::string const& name);

// TODO: work out encapsulation for context - need to make information available
// to derived fragment classes?
/* protected: */
  props::signature sig_;

  llvm::Module& mod_;

  llvm::Function *func_;
  llvm::BasicBlock *entry_;
  llvm::BasicBlock *exit_;
  llvm::ReturnInst *return_;

  compile_metadata metadata_;
};

class fragment {
public:
  using frag_ptr = std::unique_ptr<fragment>;

  /**
   * Instantiate a fragment based on matched arguments from an inference rule.
   * This doesn't receive a signature because the compilation context is
   * responsible for that - means that fragments are portable across functions
   * with differently ordered parameters etc.
   *
   * TODO: Do we want to check arguments somehow? Virtual validation method or
   * just let subclasses do their own thing?
   */
  fragment(std::vector<props::value> args);

  /**
   * Default virtual destructor to allow for polymorphic usage.
   */
  virtual ~fragment() = default;

  /**
   * Virtual clone to allow for polymorphic copying of fragment objects.
   */
  virtual frag_ptr clone() = 0;

  /**
   * Print this fragment to an ostream, with an overload for indentation to
   * allow for printing children nested as appropriate.
   */
  virtual void print(std::ostream& os, size_t indent) = 0;
  void print(std::ostream& os);

  /**
   * Compile this fragment to LLVM using ctx, which contains all the information
   * needed to do so (attachment blocks, signature for parameter index mapping,
   * etc). This probably doesn't need to be virtual in that case - public
   * interface knows how to compile in terms of managing a context and splicing,
   * given knowledge of how to splice (virtual).
   */
  compile_metadata compile(compile_context& ctx);

  /**
   * Recursive primitive that makes up compilation - insert this fragment
   * between two basic blocks. Will expect the entry block not to be terminated?
   */
  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit) = 0;

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

  template <typename T>
  bool add_child(T frag);

  /**
   * Counts the number of holes left in this fragment that can be instantiated
   * with something else. Default implementation makes sure to recurse properly,
   * but needs to make a virtual call to get the immediate number.
   */
  size_t count_holes() const;

protected:
  void print_indent(std::ostream& os, size_t indent);

  virtual size_t count_immediate_holes() const = 0;

  std::vector<props::value> args_;
  std::vector<frag_ptr> children_ = {};

  template <typename T>
  std::unique_ptr<T> clone_as();
};

template <typename T>
bool fragment::add_child(T frag)
{
  return add_child(frag_ptr{frag.clone()});
}

template <typename T>
std::unique_ptr<T> fragment::clone_as()
{
  auto new_frag = std::make_unique<T>(args_);
  for(auto const& child : children_) {
    new_frag->add_child(frag_ptr{child->clone()});
  }
  return new_frag;
}

}
