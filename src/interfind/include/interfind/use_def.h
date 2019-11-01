#pragma once

#include <llvm/IR/Constant.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Value.h>

#include <support/traits.h>
#include <support/utility.h>

#include <map>
#include <queue>
#include <set>

namespace llvm {
class Function;
class Instruction;
class Value;
} // namespace llvm

namespace interfind {

/**
 * Computes use-def analysis queries for a function - for example, does an
 * instruction appear in another's use-def chain?
 */
class use_def_analysis {
public:
  /**
   * Maps instructions onto the set of values on which they depend (i.e. every
   * value that appears in the SSA DAG with the key value as a leaf).
   *
   * The reason that the key type is Instruction rather than value is that only
   * instructions depend on other values - the functions wrapping accesses to
   * this type handle function arguments, global values etc.
   */
  using use_def_map = std::map<llvm::Instruction*, std::set<llvm::Value*>>;

  /**
   * Construct the analysis for the given function, computing the map of
   * instructions to dependencies.
   */
  use_def_analysis(llvm::Function&);

  /**
   * Does the value `use` depend on the value `def`?
   */
  bool depends(llvm::Value* use, llvm::Value* def) const;

  /**
   * Is it the case that the dependency graph of `use` can be rooted at the
   * values contained in `roots` without any improper cutting of edges? That is,
   * can `use` be expressed purely in terms of the values in `roots`?
   */
  template <typename Container>
  bool is_root_set(llvm::Value* use, Container&& roots) const;

private:
  /**
   * Internal map of dependencies.
   */
  use_def_map deps_;

  /**
   * Function over which this analysis is being computed. Used to check for
   * validity when queries are made.
   */
  llvm::Function* function_;
};

/**
 * Member function implementations.
 */

template <typename Container>
bool use_def_analysis::is_root_set(llvm::Value* use, Container&& roots) const
{
  using std::end;

  auto queue = std::queue<llvm::Value*>{ { use } };
  auto visited = std::set<llvm::Value*>{};

  while (!queue.empty()) {
    auto work = queue.front();
    queue.pop();

    if (visited.find(work) != visited.end()) {
      continue;
    }
    visited.insert(work);

    auto&& found = support::container_find(FWD(roots), work);
    if (found != end(roots)) {
      // If the value we're looking at is in the query set, then we don't
      // recurse into it.
      continue;
    }

    if (auto inst = llvm::dyn_cast<llvm::Instruction>(work)) {
      // If we find an instruction that isn't in the query set, we need to
      // recurse into its operands.
      for (auto& op : inst->operands()) {
        queue.push(op);
      }

      // Handle PHI nodes by ensuring that their branch dependencies are tracked
      // properly - what this means is that we iterate over all the incoming
      // blocks to find conditional branches that lead to them. For each one, we
      // then add the branch and associated condition to the queue as well.
      // TODO: make sure that PHI handling code can also track selects if we
      // ever come across any code that uses them.
      if (auto phi = llvm::dyn_cast<llvm::PHINode>(inst)) {
        for (auto bb : phi->blocks()) {
          for (auto label_use : bb->users()) {
            if (auto branch = llvm::dyn_cast<llvm::BranchInst>(label_use);
                branch->isConditional()) {
              queue.push(branch);
              queue.push(branch->getCondition());
            }
          }
        }
      }
    } else if (!llvm::isa<llvm::Constant>(work)) {
      // If we find something that isn't an instruction, but isn't in the query
      // set, then it's an extra root and the query set isn't valid.
      return false;
    }
  }

  return true;
}
} // namespace interfind
