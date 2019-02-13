#pragma once

#include <llvm/IR/Dominators.h>

#include <map>
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
  region(llvm::Value *, std::vector<llvm::Value *>, 
         llvm::Function &, llvm::FunctionType *);

  /**
   * Extract this region from its containing function and create a new function
   * that behaves equivalently to the region, taking care to map inputs /
   * outputs etc. properly.
   */
  llvm::Function *extract() const;

private:
  llvm::Value *output_;
  std::vector<llvm::Value *> inputs_;

  llvm::Function &original_;
  llvm::FunctionType *function_type_;
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
  using partition = std::map<llvm::Type *, std::set<llvm::Value *>>;

  /**
   * Returns true if arg could be an argument to a function-like region that
   * returns the value ret.
   *
   * In detail:
   *  - if either is global, then true - globals are always available to pass or
   *    return from a region.
   *  - if neither is global, then they must be instructions, and we delegate to
   *    the LLVM dominance analysis.
   */
  bool available(llvm::Value *ret, llvm::Value *arg) const;

  /**
   * Compute the set of values dominated by this value. This can then be used to
   * work out which values could be function arguments to a function that
   * returns this value.
   */
  std::set<llvm::Value *> available_set(llvm::Value *) const;

  /**
   * Partition a set of available values by type, such that all the values of a
   * particular type are in the same entry in the map (indexed by their type).
   */
  partition type_partition(std::set<llvm::Value *> const&) const;

  /**
   * Check whether a generated partition is able to satisfy the type signature
   * we're looking for - all we need is for there to be at least one value of
   * each argument type available to generate regions.
   */
  bool partition_is_valid(partition const&) const;

  llvm::Function& function_;
  llvm::Type *return_type_;
  std::vector<llvm::Type *> argument_types_;

  llvm::DominatorTree dom_tree_;
};

}
