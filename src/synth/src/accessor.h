#pragma once

#include "compile_metadata.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include <map>
#include <memory>
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
  virtual ~accessor() = default;

  std::set<llvm::Value*> create_geps(
      compile_metadata const& meta,
      llvm::Value* index,
      llvm::Value* base,
      llvm::IRBuilder<>& builder,
      std::string const& prefix = "") const;

  private:
  virtual std::set<llvm::Value*> map_index(
      compile_metadata const& meta,
      llvm::Value* index,
      llvm::IRBuilder<>& builder) const;
};

class offset_accessor : public accessor {
  virtual std::set<llvm::Value*> map_index(
      compile_metadata const& meta,
      llvm::Value* index,
      llvm::IRBuilder<>& builder) const override;
};

class paired_accessor : public accessor {
  virtual std::set<llvm::Value*> map_index(
      compile_metadata const& meta,
      llvm::Value* index,
      llvm::IRBuilder<>& builder) const override;
};

/**
 * This class is responsible for mapping names to accessors. Contexts own one of
 * these objects and are responsible for passing through mapping requests when
 * they're made during compilation.
 *
 * Contexts aren't copyable so we don't need these guys to be either - they can
 * validly store their internal state as unique_ptrs to accessors and give out
 * const references as the API.
 */
class accessor_map {
  using backing_map_t = std::map<std::string, std::unique_ptr<accessor>>;

  public:
  accessor_map();
  accessor_map(backing_map_t&&);

  /**
   * This is the mapping interface - contexts pass through a request to it and
   * get back a reference to an accessor (to allow for polymorphism).
   */
  accessor const& operator()(std::string const&) const;

  private:
  backing_map_t backing_map_;
  accessor default_accessor_;
};
}
