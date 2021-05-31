#include <support/options.h>

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

cl::opt<std::string> SpecFile(
    cl::Positional, cl::desc("<spec file>"),
    cl::value_desc("File containing replacement specification"), cl::Required);

cl::opt<std::string> Bitcode(
    cl::Positional, cl::desc("<bitcode file>"), cl::value_desc("Input bitcode"),
    cl::Required);

int main(int argc, char** argv)
{
  hide_llvm_options();
  cl::ParseCommandLineOptions(argc, argv);
}
