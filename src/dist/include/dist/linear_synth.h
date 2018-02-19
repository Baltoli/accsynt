#pragma once

#include <dist/function_callable.h>
#include <dist/synth_op.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <forward_list>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <type_traits>

namespace llvm {
  class Function;
  class Module;
}

namespace synth {

template <typename R, typename... Args>
class Linear {
public:
  using ret_t = typename R::example_t;
  using args_t = std::tuple<typename Args::example_t...>;
  using io_pair_t = std::pair<ret_t, args_t>;

  Linear(R r, Args... args) :
    return_type_{r}, arg_types_{args...},
    examples_{},
    module_{std::make_unique<llvm::Module>("", ThreadContext::get())}
  {}

  void add_example(ret_t ret, args_t args);
  llvm::Function *operator()(bool clear = true);

private:
  llvm::FunctionType *llvm_function_type() const;
  size_t value_count(llvm::Function *f) const;
  bool satisfies_examples(llvm::Function *f) const;
  llvm::Value *sample(llvm::Function *f);

  void clear_functions();

  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<io_pair_t> examples_;

  std::unique_ptr<llvm::Module> module_;
};

template <typename R, typename... Args>
llvm::Function *Linear<R, Args...>::operator()(bool clear)
{
  if(clear) {
    clear_functions();
  }

  auto fn_ty = llvm_function_type();
  auto B = llvm::IRBuilder<>{ThreadContext::get()};

  while(true) {
    auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, "", module_.get());

    auto bb = llvm::BasicBlock::Create(ThreadContext::get(), "", fn);
    B.SetInsertPoint(bb);

    for(auto i = 0; i < 10; ++i) {
      auto v1 = sample(fn);
      auto v2 = sample(fn);
      Ops::sample(B, {v1, v2});
    }

    B.CreateRet(sample(fn));

    if(satisfies_examples(fn)) {
      return fn;
    } else {
      fn->eraseFromParent();
    }
  }
}

template <typename R, typename... Args>
void Linear<R, Args...>::add_example(Linear::ret_t r, Linear::args_t args)
{
  examples_.push_back({r, args});
}

template <typename R, typename... Args>
llvm::FunctionType *Linear<R, Args...>::llvm_function_type() const
{
  auto llvm_arg_tys = std::array<llvm::Type*, sizeof...(Args)>{};
  util::zip_for_each(arg_types_, llvm_arg_tys, [] (auto a, auto& ll) {
    ll = a.llvm_type();
  });
  return llvm::FunctionType::get(return_type_.llvm_type(), llvm_arg_tys, false);
}

template <typename R, typename... Args>
size_t Linear<R, Args...>::value_count(llvm::Function *f) const
{
  auto instrs = std::accumulate
    (std::begin(*f), std::end(*f), 0, [f](auto sum, auto& bb) {
      return sum + bb.size();
    });
  return instrs + f->arg_size();
}

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<ret_t>(f);
  return std::all_of(std::begin(examples_), std::end(examples_), [&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}

template <typename R, typename... Args>
llvm::Value *Linear<R, Args...>::sample(llvm::Function *f)
{
  auto rd = std::random_device{};

  auto range = value_count(f) - 1;

  auto dist = std::uniform_int_distribution<decltype(range)>{0, range};
  auto index = dist(rd);

  if(index < f->arg_size()) {
    return f->arg_begin() + index;
  } else {
    auto count = f->arg_size();
    for(auto& BB : *f) {
      for(auto& I : BB) {
        if(count++ == index) {
          return &I;
        }
      }
    }
  }

  // Exceptional case here - correct way to handle it?
  return nullptr;
}

template <typename R, typename... Args>
void Linear<R, Args...>::clear_functions()
{
  auto to_clear = std::forward_list<llvm::Function *>{};

  for(auto& f : *module_) {
    to_clear.push_front(&f);
  }

  for(auto* f : to_clear) {
    f->eraseFromParent();
  }
}

}
