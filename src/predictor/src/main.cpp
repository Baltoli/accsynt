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

enum mode { python };

static cl::list<std::string> InputFilenames(
    cl::Positional, cl::desc("<property sets>"), cl::OneOrMore);

static cl::opt<mode> Mode(cl::desc("Execution mode"),
    cl::values(clEnumVal(python, "Dump data for python script")), cl::Required);

int to_python()
{
  auto all_props = std::vector<property_set>{};
  for (auto file : InputFilenames) {
    all_props.push_back(property_set::load(file));
  }

  auto data = dataset(all_props);
  fmt::print("{}\n", data.to_csv());

  return 0;
}

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  switch (Mode) {
  case python:
    return to_python();
  }
}
