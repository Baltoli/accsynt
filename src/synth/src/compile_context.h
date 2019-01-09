#pragma once

#include "accessor.h"
#include "compile_metadata.h"

#include <props/props.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <set>

namespace synth {

/**
 * Information and helper methods for compiling fragments. Responsible for
 * interfacing with an LLVM function, keeping track of a signature etc.
 */
class compile_context {
public:
  compile_context(llvm::Module& mod,
                  props::signature sig,
                  accessor_map&& accessor_map = {});

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
  llvm::Argument *argument(std::string const& name) const;

  accessor const& accessor_for(std::string const& name) const;

  std::set<llvm::Value *> create_geps_for(
      std::string const& name, llvm::Value *base, llvm::Value *ptr,
      llvm::IRBuilder<>& builder, std::string const& prefix = "") const;

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

private:
  accessor_map accessor_map_;
};

}
