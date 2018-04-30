/**
 * \file function_callable.h
 */

#pragma once

#include <dist/contexts.h>
#include <dist/output_collector.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <memory>
#include <vector>

namespace llvm {
  class Function;
  class Module;
}

namespace accsynt {

template <typename> struct gv_to_val;

template <typename T>
struct gv_to_val<Output<T>> {
  decltype(auto) operator()(Output<T> arg, llvm::GenericValue gv)
  {
    auto ch = gv_to_val<T>{};
    return ch(arg.type(), gv);
  }
};

template <typename T>
struct gv_to_val<Array<T>> {
  decltype(auto) operator()(Array<T> arg, llvm::GenericValue gv)
  {
    using element_type = typename T::example_t;
    auto size = arg.array_size();
    auto ptr = static_cast<element_type *>(gv.PointerVal);
    return std::vector<element_type>(ptr, ptr + size);
  }
};

template <>
struct gv_to_val<Integer> {
  decltype(auto) operator()(Integer i, llvm::GenericValue gv)
  {
    return long{gv.IntVal.getSExtValue()};
  }
};

static constexpr struct with_error_code_tag{} with_error_code = {};
static constexpr struct no_error_code_tag{} no_error_code = {};

template <typename R, typename... Args>
class FunctionCallable {
public:
  using return_type = typename all_outputs<R, Args...>::type;

  template <typename Tag>
  FunctionCallable(Tag, llvm::Module *m, llvm::StringRef name, R r, Args... as);

  template <typename Tag>
  FunctionCallable(Tag, llvm::Function *f, R r, Args... as);

  return_type operator()(typename Args::example_t... args);

  std::optional<long> get_error() const { return error_code_; }

private:
  output_collector<gv_to_val, R, Args...> collector_;

  bool uses_error_ = false;
  std::optional<long> error_code_ = {};

  std::unique_ptr<llvm::Module> module_;
  llvm::Function *func_;
  std::unique_ptr<llvm::ExecutionEngine> engine_;
};

template <typename R, typename... Args>
template <typename Tag>
FunctionCallable<R, Args...>::FunctionCallable(
    Tag,
    llvm::Module *m, llvm::StringRef name,
    R r, Args... args) :
  collector_(r, args...),
  module_{copy_module_to(ThreadContext::get(), m)},
  func_{module_->getFunction(name)}
{
  static_assert(
    std::is_same_v<Tag, no_error_code_tag> ||
    std::is_same_v<Tag, with_error_code_tag>,
    "Unsupported tag type for function callable");

  uses_error_ = std::is_same_v<Tag, with_error_code_tag>;

  auto eb = llvm::EngineBuilder{std::move(module_)};
  engine_.reset(eb.create());
}

template <typename R, typename... Args>
template <typename Tag>
FunctionCallable<R, Args...>::FunctionCallable(
    Tag t,
    llvm::Function *f,
    R r, Args... args) :
  FunctionCallable(t, f->getParent(), f->getName(), r, args...)
{
}

template <typename R, typename... Args>
typename FunctionCallable<R, Args...>::return_type
FunctionCallable<R, Args...>::operator()(typename Args::example_t... args)
{
  assert(func_->arg_size() == sizeof...(args) + uses_error_ && "Argument count mismatch");

  auto func_args = std::array<llvm::GenericValue, sizeof...(args)>{
    { make_generic(args)... }
  };

  if(uses_error_) {
    auto args_with_err = std::array<llvm::GenericValue, sizeof...(args) + 1>{};
    std::copy(std::begin(func_args), std::end(func_args), std::next(std::begin(args_with_err)));

    auto err = int64_t{0};
    auto err_v = llvm::GenericValue{};
    err_v.PointerVal = &err;

    args_with_err[0] = err_v;
    auto ret = engine_->runFunction(func_, args_with_err);
    
    if(err != 0) {
      error_code_ = err;
      return return_type{};
    } else {
      error_code_ = {};
      auto args_no_err = std::array<llvm::GenericValue, sizeof...(args)>{};
      std::copy(std::next(args_with_err.begin()), args_with_err.end(), args_no_err.begin());
      return collector_.collect(ret, args_no_err);
    }
  } else {
    auto ret = engine_->runFunction(func_, func_args);
    return collector_.collect(ret, func_args);
  }
}

}
