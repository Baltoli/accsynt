#include "blas_properties.h"

namespace synth {

blas_properties::blas_properties(props::property_set ps)
{
  // TODO: validation of properties

  ps.for_each_named("size", [&, this](auto const& prop) {
    count_++;

    auto ptr_name = prop.values.at(0).param_val;
    auto size_name = prop.values.at(1).param_val;

    auto const& sig = ps.type_signature;
    auto ptr_index = sig.param_index(ptr_name);
    auto size_index = sig.param_index(size_name);

    sizes_.insert({ ptr_index, size_index });
  });

  ps.for_each_named("output", [&, this](auto const& prop) {
    auto ptr_name = prop.values.at(0).param_val;

    auto const& sig = ps.type_signature;
    auto ptr_index = sig.param_index(ptr_name);

    outputs_.insert(ptr_index);
  });

  ps.for_each_named("pack", [&, this](auto const& prop) {
    auto ptr_name = prop.values.at(0).param_val;

    auto const& sig = ps.type_signature;
    auto ptr_index = sig.param_index(ptr_name);

    packing_.insert({ ptr_index, prop.values.at(1).int_val });
  });

  auto i = 0;
  for (auto param : ps.type_signature.parameters) {
    if (param.pointer_depth > 0 && sizes_.find(i) == sizes_.end()) {
      unsized_.insert(i);
    }

    ++i;
  }
}

size_t blas_properties::loop_count() const { return count_; }

std::map<size_t, size_t> const& blas_properties::loop_sizes() const
{
  return sizes_;
}

std::set<size_t> blas_properties::size_indexes() const
{
  auto ret = std::set<size_t>{};
  for (auto [ptr, sz] : sizes_) {
    ret.insert(sz);
  }
  return ret;
}

bool blas_properties::is_output(size_t idx) const
{
  return outputs_.find(idx) != outputs_.end();
}

size_t blas_properties::merged_loop_count() const
{
  return size_indexes().size();
}

std::set<size_t> blas_properties::pointers_with_size(size_t size_idx) const
{
  auto ret = std::set<size_t>{};
  for (auto [ptr, sz] : sizes_) {
    if (size_idx == sz) {
      ret.insert(ptr);
    }
  }
  return ret;
}

std::set<size_t> blas_properties::unsized_pointers() const { return unsized_; }

size_t blas_properties::pack_size(size_t idx) const
{
  if (packing_.find(idx) == packing_.end()) {
    return 1;
  } else {
    return packing_.at(idx);
  }
}
}
