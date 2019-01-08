#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include <set>

namespace synth {

/**
 * The interface through which fragments know how to access memory based on
 * iterators and pointers. An accessor is responsible for mapping a set of
 * iteration variables to a set of memory accesses (GEPs), based on some rules.
 * Typically they will be configured by the rule engine, but the actual
 * mechanism is abstract from that interface.
 *
 * This class presents a virtual interface that can be customised by other
 * implementations to provide different behaviour, but also gives "no-op"
 * default behaviour that maps a set of indices to themselves.
 *
 * Accessors are given the base pointer they're GEP-ing into and a builder
 * reference so they know where to put the GEPs.
 */
class accessor {
public:
  accessor() = default;

  std::set<llvm::Value *> create_geps(
      std::set<llvm::Value *> indices,
      llvm::Value *base, 
      llvm::IRBuilder<>& builder) const;

private:
  virtual std::set<llvm::Value *> map_indices(
      std::set<llvm::Value *> indices) const;
};

}
