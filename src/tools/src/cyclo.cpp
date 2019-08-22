#include <passes/passes.h>

#include <llvm/Support/CommandLine.h>

using namespace llvm;

static cl::opt<std::string> InputFilename(cl::Positional,
    cl::desc("<input bitcode file>"), cl::init("-"),
    cl::value_desc("filename"));

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  auto pass = createCycloPass();
}
