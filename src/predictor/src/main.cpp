#include "prepare_data.h"

#include <props/props.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

#include <string>
#include <vector>

using namespace llvm;
using namespace predict;
using namespace props;

static cl::list<std::string> InputFilenames(
    cl::Positional, 
    cl::desc("<property sets>"), 
    cl::OneOrMore);

int main(int argc, char **argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto all_props = std::vector<property_set>{};
  for(auto file : InputFilenames) {
    all_props.push_back(property_set::load(file));
  }

  auto sum = summary(all_props);
}
