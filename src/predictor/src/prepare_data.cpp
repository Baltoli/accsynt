#include "prepare_data.h"

#include <fmt/format.h>

#include <llvm/Support/Commandline.h>

#include <algorithm>

using namespace llvm;
using namespace props;

namespace predict {

int dataset::encode(base_type bt) const
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
  
/* int dataset::encode(std::string const& pn) const */
/* { */
/*   auto found = prop_names_.find(pn); */
/*   return std::distance(prop_names_.begin(), found); */
/* } */

}
