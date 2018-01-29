#pragma once

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include <memory>

namespace llvm {
  class ExecutionEngine;
  class Function;
  class Module;
}

/**
 * Create a function "shell" into which we can copy the body of another
 * function using LLVM cloning transforms. This method copies the type
 * signature, name and linkage from f.
 */
llvm::Function *function_copy(llvm::Function *f, llvm::Module *m);

llvm::ExecutionEngine *create_engine(llvm::Module* m);

template<class T>
llvm::GenericValue make_generic(T t)
{
  llvm::GenericValue gv;
  gv.IntVal = llvm::APInt(sizeof(T)*8, t, std::is_signed_v<T>);
  return gv;
}
