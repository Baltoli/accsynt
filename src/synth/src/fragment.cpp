#include "fragment.h"
#include "linear_fragment.h"

#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>

#include <algorithm>
#include <numeric>

using namespace llvm;
using namespace props;

namespace synth {

fragment::frag_set fragment::enumerate(std::vector<frag_ptr>&& fragments, size_t data_blocks)
{
  auto lin_f = linear_fragment{{}};
  auto empty_f = empty_fragment{{}};

  auto control = enumerate_all(std::move(fragments));
  auto results = fragment::frag_set{};

  for(auto&& cf : control) {
    auto holes = cf->count_holes();
    auto vec = std::vector<fragment::frag_ptr>{};

    for(auto i = 0u; i < holes; ++i) {
      if(i < data_blocks) {
        vec.push_back(lin_f.clone());
      } else {
        vec.push_back(empty_f.clone());
      }
    }

    std::sort(vec.begin(), vec.end());

    do {
      auto clone = cf->clone();

      for(auto i = 0u; i < holes; ++i) {
        clone->add_child(vec.at(i)->clone(), 0);
      }

      results.insert(std::move(clone));
    } while(std::next_permutation(vec.begin(), vec.end()));
  }

  return std::move(results);
}

fragment::frag_set fragment::enumerate_all(std::vector<frag_ptr>&& fragments)
{
  auto ret = fragment::frag_set{};

  std::sort(fragments.begin(), fragments.end());
  do {
    auto all_for_perm = enumerate_permutation(fragments);
    for(auto&& frag : all_for_perm) {
      ret.insert(frag->clone());
    }
  } while(std::next_permutation(fragments.begin(), fragments.end()));

  return std::move(ret);
}

fragment::frag_set fragment::enumerate_permutation(std::vector<frag_ptr> const& perm)
{
  if(perm.empty()) {
    return {};
  }

  auto ret = fragment::frag_set{};

  auto begin = std::next(perm.begin());
  auto end = perm.end();
  auto accum = perm.at(0)->clone();

  enumerate_recursive(ret, std::move(accum), begin, end);
  return std::move(ret);
}

fragment::fragment(std::vector<value> args) :
  args_(args)
{
}

compile_metadata fragment::compile(compile_context& ctx)
{
  splice(ctx, ctx.entry_, ctx.exit_);
  return ctx.metadata_;
}

size_t fragment::count_or_empty(fragment::frag_ptr const& frag)
{
  if(frag) {
    return frag->count_holes();
  } else {
    return 1;
  }
}

std::string fragment::string_or_empty(frag_ptr const& frag, size_t ind)
{
  if(frag) {
    return frag->to_str(ind);
  } else {
    return fmt::format("{}[?]", ::support::indent{ind});
  }
}

/**
 * From what I've thought about, I think the best thing to do is to have a
 * context "own" / manage a single function which is created when we create a
 * context object - then we can also keep track of the appropriate basic blocks
 * with the context object as well.
 */
compile_context::compile_context(Module& mod, signature sig) :
  sig_(sig), mod_(mod), 
  func_(sig_.create_function(mod_)),
  entry_(BasicBlock::Create(mod_.getContext(), "entry", func_)),
  exit_(BasicBlock::Create(mod_.getContext(), "exit", func_)),
  metadata_(func_)
{
  auto& ctx = mod_.getContext();

  auto rt = func_->getFunctionType()->getReturnType();
  if(rt->isVoidTy()) {
    return_ = ReturnInst::Create(ctx, exit_);
  } else {
    auto zero = Constant::getNullValue(rt);
    return_ = ReturnInst::Create(ctx, zero, exit_);
  }
}

compile_context::~compile_context()
{
  // Don't actually do this - we want the function to outlive the context
  // because the erasure happens elsewhere in the process.
  /* func_->eraseFromParent(); */
}

llvm::Argument *compile_context::argument(std::string const& name)
{
  return std::next(func_->arg_begin(), sig_.param_index(name));
}

compile_metadata::compile_metadata(llvm::Function *fn)
  : function(fn)
{
}

bool fragment_equal::operator()(std::unique_ptr<fragment> const& a,
                                std::unique_ptr<fragment> const& b) const
{
  return a->to_str() == b->to_str();
  /* return a->equal_to(b); */
}

}

size_t std::hash<std::unique_ptr<synth::fragment>>::operator()(
    std::unique_ptr<synth::fragment> const& frag) const noexcept
{
  return std::hash<std::string>{}(frag->to_str());
}
