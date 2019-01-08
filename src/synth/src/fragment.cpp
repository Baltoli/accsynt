#include "fragment.h"
#include "linear_fragment.h"

#include <support/choose.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>

#include <algorithm>
#include <numeric>

using namespace llvm;
using namespace props;

namespace synth {

fragment::frag_set fragment::enumerate(std::vector<frag_ptr>&& fragments,
                                       std::optional<size_t> max_size,
                                       size_t data_blocks)
{
  if(max_size && max_size.value() == 0) {
    return {};
  }

  auto lin_f = linear_fragment{{}};
  auto empty_f = empty_fragment{{}};

  auto control = [&] {
    if(!max_size) {
      return enumerate_all(std::move(fragments), max_size);
    } else {
      auto all = fragment::frag_set{};
      for(auto i = 0u; i < max_size.value(); ++i) {
        auto deep = enumerate_all(std::move(fragments), i + 1);
        all.merge(std::move(deep));
      }
      return all;
    }
  }();

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

fragment::frag_set fragment::enumerate_all(std::vector<frag_ptr>&& fragments,
                                           std::optional<size_t> max_size)
{
  auto ret = fragment::frag_set{};
  auto real_max = std::min(max_size.value_or(fragments.size()), fragments.size());

  ::support::choose(fragments.size(), real_max).for_each([&] (auto idxs) {
      auto perm = std::vector<fragment::frag_ptr>{};
      for(auto idx : idxs) {
        perm.push_back(fragments.at(idx)->clone());
      }

      auto all_for_perm = enumerate_permutation(perm);
      for(auto&& frag : all_for_perm) {
        ret.insert(frag->clone());
      }
  });

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
