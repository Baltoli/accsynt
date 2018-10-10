#include <props/props.h>
#include <support/dynamic_library.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>

using namespace synth;
using namespace support;
using namespace llvm;

static cl::opt<std::string>
PropertiesPath(
    cl::Positional, cl::Required,
    cl::desc("<properties file>"));

static cl::opt<std::string>
LibraryPath(
    cl::Positional, cl::Required,
    cl::desc("<shared library>"));

// In the future, specifications...

int main(int argc, char **argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto property_set = props::property_set::load(PropertiesPath);
  auto fn_name = property_set.type_signature.name;

  auto lib = dynamic_library(LibraryPath);
  auto sym = lib.raw_symbol(fn_name);
}
