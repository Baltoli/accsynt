#pragma once

#include <props/props.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <set>

namespace synth {

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
  std::set<llvm::Instruction *> outputs = {};
  std::set<llvm::Value *> indices = {};

  explicit compile_metadata(llvm::Function *fn);
};

/**
 * Information and helper methods for compiling fragments. Responsible for
 * interfacing with an LLVM function, keeping track of a signature etc.
 */
class compile_context {
public:
  compile_context(llvm::Module& mod,
                  props::signature sig);

  ~compile_context();
 
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

}
