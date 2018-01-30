#pragma once

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/DerivedTypes.h>

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

template <std::size_t... Idx>
auto make_index_dispatcher(std::index_sequence<Idx...>) {
    return [] (auto&& f) { (f(std::integral_constant<std::size_t,Idx>{}), ...); };
}

template <std::size_t N>
auto make_index_dispatcher() {
    return make_index_dispatcher(std::make_index_sequence<N>{}); 
}

template <typename Tuple, typename Func>
void for_each(Tuple&& t, Func&& f) {
  constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
  auto dispatcher = make_index_dispatcher<n>();
  dispatcher([&f,&t](auto idx) {
    f(std::get<idx>(std::forward<Tuple>(t)));
  });
}

template <typename Tuple, typename Dists, typename Func>
void zip_for_each(Tuple&& t, Dists&& d, Func&& f) {
  static_assert(std::tuple_size_v<std::decay_t<Tuple>> == std::tuple_size_v<std::decay_t<Dists>>);

  constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
  auto dispatcher = make_index_dispatcher<n>();
  dispatcher([&f,&t,&d](auto idx) {
    f(std::get<idx>(std::forward<Tuple>(t)), std::get<idx>(std::forward<Dists>(d))); 
  });
}

template <typename T, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
llvm::IntegerType *get_llvm_type(llvm::LLVMContext& C)
{
  return llvm::IntegerType::get(C, sizeof(T)*8);
}
