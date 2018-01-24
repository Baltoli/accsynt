#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

#include <tuple>
#include <type_traits>

template<typename T, typename = void>
struct is_tuple : std::false_type {};

template<typename T>
struct is_tuple<T, decltype(std::tuple_size<T>::value, void())> : std::true_type {};

template<typename I>
llvm::IntegerType *get_llvm_int(llvm::LLVMContext& c) {
  return llvm::IntegerType::get(c, sizeof(I)*8);
}
