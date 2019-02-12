#pragma once

#include <vector>

namespace llvm {
  class Function;
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

  // TODO: should really be unordered_set
  /**
   * Compute all the possible combinations of instructions that could represent
   * regions in the given function.
   */
  std::vector<region> all_candidates() const;

private:
  llvm::Function& function_;
  llvm::Type *return_type_;
  std::vector<llvm::Type *> argument_types_;
};

}
