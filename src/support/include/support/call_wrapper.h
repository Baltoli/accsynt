#pragma once

#include "call_builder.h"

#include <props/props.h>
#include <support/dynamic_library.h>
#include <support/thread_context.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <memory>

namespace support {

/**
 * Encapsulates a callable object in an LLVM module and provides access to a
 * builder that can be used to pass type-safe arguments at runtime based on the
 * type signature of the object.
 *
 * The objects currently supported by this class are:
 * - Shared library functions loaded using dlsym.
 * - LLVM functions constructed using the LLVM API.
 *
 * A rough overview of how this class works is as follows:
 *
 * On construction, it creates a JIT execution engine. If constructed with a
 * dynamic library, the library is registered with the engine. A reference to
 * the "implementation" (shared library or LLVM function) is stored, and a
 * wrapper function is created.
 *
 * This wrapper function always has the same type signature (returns i64,
 * accepts pointer to i8) so that the builder can assemble arguments
 * byte-by-byte, and the wrapper code can interpret the same. It is responsible
 * for marshalling the bytewise data into values of the correct type and calling
 * the implementation with them.
 */
class call_wrapper {
public:
  /**
   * Construct a wrapper for an existing function contained in a module. The
   * function is looked up by name in the module.
   */
  call_wrapper(
      props::signature sig, llvm::Module const& mod, std::string const& name);

  /**
   * Construct a wrapper for a symbol contained in a dynamic library. The name
   * is looked up using dlsym and registered with the execution engine.
   */
  call_wrapper(props::signature sig, llvm::Module const& mod,
      std::string const& name, dynamic_library const& dl);

  /**
   * Construct a wrapper for an arbitrary function pointer. The function pointer
   * is registered with the execution engine just as a dynamically loaded symbol
   * would be.
   */
  template <typename FPtr>
  call_wrapper(props::signature sig, FPtr ptr);

  /**
   * Construct a call builder with the correct type signature for this wrapper.
   */
  call_builder get_builder() const;

  /**
   * Call the wrapped function with an assembled argument pack, returning the
   * function's return value.
   */
  uint64_t call(call_builder& builder);

private:
  /**
   * Runtime sizeof() for LLVM types - gets the size of a type when it is
   * converted to raw bytes.
   */
  size_t marshalled_size(llvm::Type const* type) const;

  /**
   * Creates a vector of i8 with the given size.
   */
  template <typename Builder>
  llvm::Value* make_vector(Builder& B, size_t size) const;

  /**
   * Create a return instruction from the wrapper function, optionally returning
   * a value if the type signature has a non-void return.
   */
  template <typename Builder>
  llvm::Value* make_return(Builder& B, llvm::Value* ret = nullptr) const;

  /**
   * Build the marshalling and call logic for a function.
   */
  llvm::Function* build_wrapper_function(
      llvm::Module& mod, llvm::Function* fn) const;

  props::signature signature_;
  llvm::Function* impl_;
  llvm::Function* wrapper_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename FPtr>
call_wrapper::call_wrapper(props::signature sig, FPtr ptr)
    : signature_(sig)
{
  engine_->addGlobalMapping(impl_, (void*)ptr);
}

template <typename Builder>
llvm::Value* call_wrapper::make_vector(Builder& B, size_t size) const
{
  auto vec_ty = llvm::VectorType::get(B.getInt8Ty(), size);
  return llvm::Constant::getNullValue(vec_ty);
}

template <typename Builder>
llvm::Value* call_wrapper::make_return(Builder& B, llvm::Value* ret) const
{
  if (!ret) {
    ret = B.getInt64(0);
  }

  auto* to_extend = ret;
  if (ret->getType()->isFloatTy()) {
    to_extend = B.CreateBitCast(ret, B.getInt32Ty());
  }

  auto* return_val = B.CreateZExt(to_extend, B.getInt64Ty());
  return B.CreateRet(return_val);
}
} // namespace support
