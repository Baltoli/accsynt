#pragma once

#include <props/props.h>

#include <map>
#include <set>

namespace synth {

class blas_properties {
public:
  blas_properties(props::property_set ps);

  size_t loop_count() const;
  std::map<size_t, size_t> const& loop_sizes() const;

  // The merged loop count is the number of unique loop sizes in this
  // property set
  size_t merged_loop_count() const;
  std::set<size_t> pointers_with_size(size_t size_idx) const;

  std::set<size_t> unsized_pointers() const;

  std::set<size_t> size_indexes() const;

  bool is_output(size_t idx) const;

  size_t pack_size(size_t idx) const;

private:
  size_t count_ = 0;

  // Stores a mapping from ptr_index -> size_index, where the indexes are into
  // the arguments of the property_set's type signature
  std::map<size_t, size_t> sizes_ = {};

  // Store which argument indices are outputs
  std::set<size_t> outputs_ = {};

  std::set<size_t> unsized_ = {};

  // Stores a mapping of ptr_index -> packing size, where the packing size
  // indicates how many elements are packed / should be accessed at each
  // iteration
  std::map<size_t, size_t> packing_ = {};
};
} // namespace synth
