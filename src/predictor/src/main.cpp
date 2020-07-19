#include "prepare_data.h"

#include <support/filesystem.h>

#include <props/props.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

#include <cstdio>
#include <string>
#include <vector>

using namespace fmt::literals;
using namespace llvm;
using namespace predict;
using namespace props;

namespace fs = filesystem;

enum mode { python };

static cl::list<std::string>
    InputFilenames(cl::Positional, cl::desc("<property sets>"), cl::OneOrMore);

static cl::opt<std::string> OutputDirectory(
    "output-dir", cl::desc("Directory to output generated CSV files"),
    cl::init("-"));

static cl::alias OutputDirectoryA(
    "o", cl::desc("Alias for output-dir"), cl::aliasopt(OutputDirectory));

static cl::opt<mode> Mode(
    cl::desc("Execution mode"),
    cl::values(clEnumVal(python, "Dump data for python script")), cl::Required);

int to_python()
{
  auto all_props = std::vector<property_set> {};
  for (auto file : InputFilenames) {
    all_props.push_back(property_set::load(file));
  }

  auto data = dataset(all_props);

  if (OutputDirectory == "-") {
    fmt::print("{}\n", data.to_csv());
    /* fmt::print("{}\n", data.name_map_csv()); */
  } else {
    auto out_dir = fs::path(OutputDirectory.getValue());

    if (!fs::exists(out_dir)) {
      fmt::print("{} does not exist\n", out_dir.string());
      return 1;
    }

    if (!fs::is_directory(out_dir)) {
      fmt::print("{} is not a directory\n", out_dir.string());
      return 1;
    }

    auto data_path = out_dir / "data.csv";
    /* auto names_path = out_dir / "names.csv"; */

    auto data_f = std::fopen(data_path.c_str(), "w");
    /* auto names_f = std::fopen(names_path.c_str(), "w"); */

    fmt::print(data_f, "{}\n", data.to_csv());
    /* fmt::print(names_f, "{}\n", data.name_map_csv()); */

    std::fclose(data_f);
    /* std::fclose(names_f); */
  }

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
