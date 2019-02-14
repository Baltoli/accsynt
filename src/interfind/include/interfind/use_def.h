#pragma once

#include <llvm/IR/InstVisitor.h>

#include <map>
#include <set>

namespace llvm {
  class Function;
  class Instruction;
  class Value;
}

namespace interfind {

/**
 * Computes use-def analysis queries for a function - for example, does an
 * instruction appear in another's use-def chain?
 */
class use_def_analysis {
public:
  /**
   * Maps instructions onto the set of values on which they depend (i.e. every value
   * that appears in the SSA DAG with the key value as a leaf).
   *
   * The reason that the key type is Instruction rather than value is that only
   * instructions depend on other values - the functions wrapping accesses to
   * this type handle function arguments, global values etc.
   */
  using use_def_map = std::map<llvm::Instruction *, std::set<llvm::Value *>>;

  /**
   * Construct the analysis for the given function, computing the map of
   * instructions to dependencies.
   */
  use_def_analysis(llvm::Function&);

  /**
   * Does the value `use` depend on the value `def`?
   */
  bool depends(llvm::Value *use, llvm::Value *def) const;

  /**
   * Is it the case that the dependency graph of `use` can be rooted at the
   * values contained in `roots` without any improper cutting of edges? That is,
   * can `use` be expressed purely in terms of the values in `roots`?
   */
  bool is_root_set(llvm::Value *use, std::set<llvm::Value *> roots) const;

private:
  /**
   * Internal map of dependencies.
   */
  use_def_map deps_;

  /**
   * Function over which this analysis is being computed. Used to check for
   * validity when queries are made.
   */
  llvm::Function *function_;
};

}
