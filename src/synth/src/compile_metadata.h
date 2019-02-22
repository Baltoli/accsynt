#pragma once

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
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
  llvm::Function* function;
  std::set<llvm::Value*> seeds = {};
  std::set<llvm::BasicBlock*> data_blocks = {};
  std::set<llvm::Instruction*> outputs = {};
  std::set<llvm::Value*> indices = {};

  explicit compile_metadata(llvm::Function* fn);
};
}
