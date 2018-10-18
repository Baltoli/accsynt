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
  std::vector<size_t> pointers_with_size(size_t size_idx) const;

  std::set<size_t> size_indexes() const;

private:
  size_t count_ = 0;
  
  // Stores a mapping from ptr_index -> size_index, where the indexes are into
  // the arguments of the property_set's type signature
  std::map<size_t, size_t> sizes_ = {};
};

}
