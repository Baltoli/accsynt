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
      in_keys.insert("{}"_format(k));
    }

    for(auto const& [k, v] : e.output()) {
      out_keys.insert("{}"_format(k));
    }
  }

  // Make a header
  auto header = "{},{}"_format(
    fmt::join(in_keys, ","), 
    fmt::join(out_keys, ",")
  );

  // Then print each row using the collected keys

  auto rows = std::vector<std::string>{};

  for(auto const& e : examples_) {
    auto row = std::vector<int>{};

    for(auto const& i_k : in_keys) {
      if(e.input().find(i_k) != e.input().end()) {
        row.push_back(e.input().at(i_k));
      } else {
        row.push_back(missing_);
      }
    }

    for(auto const& o_k : out_keys) {
      if(e.output().find(o_k) != e.output().end()) {
        row.push_back(e.output().at(o_k));
      } else {
        row.push_back(missing_);
      }
    }

    rows.push_back(fmt::format("{}", fmt::join(row, ",")));
  }

  return "{}\n{}"_format(header, fmt::join(rows, "\n"));
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
