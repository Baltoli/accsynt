#include "prepare_data.h"

#include <fmt/format.h>

#include <llvm/Support/Commandline.h>

#include <algorithm>

using namespace llvm;
using namespace props;

namespace predict::detail {

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
