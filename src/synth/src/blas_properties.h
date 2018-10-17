#pragma once

#include <props/props.h>

#include <map>

namespace synth {

class blas_properties {
public:
  blas_properties(props::property_set ps);

  size_t loop_count() const;
  std::map<size_t, size_t> const& loop_sizes() const;

private:
  size_t count_ = 0;
  std::map<size_t, size_t> sizes_ = {};
};

}
