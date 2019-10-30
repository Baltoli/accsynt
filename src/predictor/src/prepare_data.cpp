#include "prepare_data.h"

#include <fmt/format.h>

#include <llvm/Support/Commandline.h>

#include <algorithm>
#include <set>

using namespace llvm;
using namespace props;

namespace predict {

std::string dataset::to_csv() const
{
  using namespace fmt::literals;

  auto in_keys = std::set<std::string>{};
  auto out_keys = std::set<std::string>{};

  // First pass to collect the full set of keys to use
  for(auto const& e : examples_) {
    for(auto const& [k, v] : e.input()) {
      in_keys.insert("in_{}"_format(k));
    }

    for(auto const& [k, v] : e.output()) {
      out_keys.insert("out_{}"_format(k));
    }
  }

  // Make a header
  auto header = "{},{}"_format(
    fmt::join(in_keys, ","), 
    fmt::join(out_keys, ",")
  );

  return header;
}
  
namespace detail {

int encode(base_type bt)
{
  switch(bt) {
    case base_type::character:
      return 1;
    case base_type::boolean:
      return 2;
    case base_type::integer:
      return 3;
    case base_type::floating:
      return 4;
  }

  return 0;
}

}

}
