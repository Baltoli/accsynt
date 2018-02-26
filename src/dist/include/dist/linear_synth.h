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
    examples_{}
  {}

  void add_example(ret_t ret, args_t args);
  std::unique_ptr<llvm::Module> operator()();

  std::tuple<Args...> arg_types() const { return arg_types_; }

private:
  llvm::FunctionType *llvm_function_type() const;
  bool satisfies_examples(llvm::Function *f) const;

  void clear_functions(llvm::Module& module);

  std::unique_ptr<llvm::Module> generate_candidate(bool&);

  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<io_pair_t> examples_;
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::operator()()
{
  auto ret = std::unique_ptr<llvm::Module>{};
  bool done = false;

  auto work = [&] {
    auto cand = generate_candidate(done);
    if(cand) {
      ret = std::move(cand);
    }
  };

  auto threads = std::forward_list<std::thread>{};
  auto max_threads = std::thread::hardware_concurrency();
  for(auto i = 0; i < max_threads; ++i) {
    threads.emplace_front(work);
  }

  for(auto& t : threads) {
    t.join();
  }

  return ret;
}

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::generate_candidate(bool& done)
{
  auto fn_ty = llvm_function_type();
  auto mod = std::make_unique<llvm::Module>("", ThreadContext::get());
  auto B = llvm::IRBuilder<>{mod->getContext()};

  while(!done) {
    clear_functions(*mod);

    auto sampler = ValueSampler{};
    auto& meta = sampler.metadata();

    auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, 
                                     "cand", mod.get());
    auto bb = llvm::BasicBlock::Create(fn->getContext(), "", fn);
    B.SetInsertPoint(bb);

    auto live = std::vector<llvm::Value *>{};
    for(auto& arg : fn->args()) {
      live.push_back(&arg);
    }

    util::index_for_each(arg_types_, [&](auto&& at, auto idx) {
      if constexpr(is_index(at)) {
        meta.set_index_bound(fn->arg_begin() + idx, at.bound());
      }
    });

    for(auto i = 0; i < 20; ++i) {
      auto v1 = util::uniform_sample(live);
      auto v2 = util::uniform_sample(live);
      
      if(auto next = sampler(B, {v1, v2})) {
        live.push_back(next);
      }
    }

    auto possibles = std::vector<llvm::Value *>{};
    std::copy_if(live.begin(), live.end(), std::back_inserter(possibles), 
        [fn_ty](auto inst) {
          return inst->getType() == fn_ty->getReturnType();
        });

    if(possibles.empty()) {
      return nullptr;
    }

    B.CreateRet(util::uniform_sample(possibles));

    if(satisfies_examples(fn)) {
      done = true;
      return std::move(mod);
    } else {
      fn->eraseFromParent();
    }
  }

  return nullptr;
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
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<ret_t>(f->getParent(), f->getName());
  return std::all_of(std::begin(examples_), std::end(examples_), [f,&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}

template <typename R, typename... Args>
void Linear<R, Args...>::clear_functions(llvm::Module& module)
{
  auto to_clear = std::forward_list<llvm::Function *>{};

  for(auto& f : module) {
    to_clear.push_front(&f);
  }

  for(auto* f : to_clear) {
    f->eraseFromParent();
  }
}

}
