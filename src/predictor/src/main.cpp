#include "prepare_data.h"

#include <props/props.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

using namespace llvm;
using namespace predict;
using namespace props;

int main()
{
  auto all_props = std::vector<property_set>{};
  auto summary = summarise_props(all_props);
}
