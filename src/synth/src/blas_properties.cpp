#include "blas_properties.h"

namespace synth {

blas_properties::blas_properties(props::property_set ps)
{
  ps.for_each_named("size", [&,this] (auto const& prop) {
    count_++;

    auto ptr_name = prop.values.at(0).param_val;
    auto size_name = prop.values.at(1).param_val;

    auto const& sig = ps.type_signature;
    auto ptr_index = sig.param_index(ptr_name);
    auto size_index = sig.param_index(size_name);

    sizes_.insert({ptr_index, size_index});
  });
}

size_t blas_properties::loop_count() const
{
  return count_;
}

std::map<size_t, size_t> const& blas_properties::loop_sizes() const
{
  return sizes_;
}

}
