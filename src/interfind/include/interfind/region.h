#pragma once

#include <llvm/IR/Dominators.h>

#include <vector>

namespace llvm {
  class Function;
  class FunctionType;
  class Type;
  class Value;
}

namespace interfind {

/**
 * Represents a separable region of code that can be extracted into a function.
 */
class region {
public:
  /**
   * Direct constructor from the values comprising this region.
   */
  region(llvm::Value *, std::vector<llvm::Value *>);

private:
  llvm::Value *output_;
  std::vector<llvm::Value *> inputs_;
};

/**
 * Responsible for searching a function for candidate regions with the given
 * type.
 */
class region_finder {
public:
  /**
   * Construct a region with the given return and argument types, as well as a
   * function to search in.
   */
  region_finder(llvm::Function &, llvm::Type *, std::vector<llvm::Type *>);
  region_finder(llvm::Function &, llvm::FunctionType *);

  // TODO: should really be unordered_set but needs boilerplate on the region
  //       class to support this.
  /**
   * Compute all the possible combinations of instructions that could represent
   * regions in the given function.
   */
  std::vector<region> all_candidates() const;

private:
  /**
   * Returns true if value a must have been reached by the time value b is
   * reached. This function is a generalisation of the analysis provided by the
   * built in dominance tree to extend to global values, constants and
   * arguments to functions.
   *
   * Any such "global" value can be seen as dominating any other value, even if
   * the other is also global. If both a and b are actually instructions, then
   * the logic delegates to the dominance tree for the function associated with
   * this finder.
   */
  bool dominates(llvm::Value *a, llvm::Value *b) const;

  /**
   * Compute the set of values dominated by this value. This can then be used to
   * work out which values could be function arguments to a function that
   * returns this value.
   */
  std::set<llvm::Value *> dominated_set(llvm::Value *) const;

  llvm::Function& function_;
  llvm::Type *return_type_;
  std::vector<llvm::Type *> argument_types_;

  llvm::DominatorTree dom_tree_;
};

}
