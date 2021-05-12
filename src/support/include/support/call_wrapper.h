#pragma once

#include "call_builder.h"

#include <props/props.h>
#include <support/dynamic_library.h>
#include <support/thread_context.h>

#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <chrono>
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
   * Construct a wrapper for a function by passing the function directly - the
   * parent module and name can be obtained unambiguously from the function.
   */
  call_wrapper(llvm::Function const& func);

  /**
   * Construct a wrapper for an existing function by inferring the type
   * signature from the function's LLVM type.
   *
   * If the function type is incorrect, this will throw an exception.
   */
  call_wrapper(llvm::Module const& mod, llvm::StringRef name);

  /**
   * Construct a wrapper for an existing function contained in a module. The
   * function is looked up by name in the module.
   */
  call_wrapper(
      props::signature sig, llvm::Module const& mod, llvm::StringRef name);

  /**
   * Construct a wrapper for a symbol contained in a dynamic library. The name
   * is looked up using dlsym and registered with the execution engine.
   */
  call_wrapper(
      props::signature sig, llvm::Module const& mod, llvm::StringRef name,
      dynamic_library const& dl);

  /**
   * Construct a wrapper for an arbitrary function pointer. The function pointer
   * is registered with the execution engine just as a dynamically loaded symbol
   * would be.
   */
  template <typename FPtr>
  call_wrapper(
      props::signature sig, llvm::Module const& mod, llvm::StringRef name,
      FPtr ptr);

  /**
   * Construct a call builder with the correct type signature for this wrapper.
   */
  call_builder get_builder() const;

  /**
   * Call the wrapped function with an assembled argument pack, returning the
   * function's return value.
   */
  uint64_t call(call_builder& builder);

  /**
   * Call the wrapped function with an assembled argument pack, returning the
   * function's return value and the time spent executing it.
   */
  std::pair<uint64_t, std::chrono::nanoseconds>
  call_timed(call_builder& builder);

  /**
   * Get the name of the underlying function implementation (if it's not already
   * known, for example if the wrapper was constructed by inferring a candidate
   * function whose name is not known).
   */
  std::string name() const;

protected:
  llvm::Function* implementation() const { return impl_; }
  std::unique_ptr<llvm::ExecutionEngine> const& engine() const
  {
    return engine_;
  }

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
  llvm::Function*
  build_wrapper_function(llvm::Module& mod, llvm::Function* fn) const;

  props::signature signature_;
  llvm::Function* impl_;
  llvm::Function* wrapper_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename FPtr>
call_wrapper::call_wrapper(
    props::signature sig, llvm::Module const& mod, llvm::StringRef name,
    FPtr ptr)
    : call_wrapper(sig, mod, name)
{
  engine_->addGlobalMapping(impl_, (void*)ptr);
}

template <typename Builder>
llvm::Value* call_wrapper::make_vector(Builder& B, size_t size) const
{
  auto vec_ty = llvm::VectorType::get(B.getInt8Ty(), size, false);
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
  } else if (ret->getType()->isPointerTy()) {
    to_extend = B.CreatePtrToInt(ret, B.getInt64Ty());
  }

  auto* return_val = B.CreateZExt(to_extend, B.getInt64Ty());
  return B.CreateRet(return_val);
}
} // namespace support
