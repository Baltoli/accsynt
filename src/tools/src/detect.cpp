#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/PluginLoader.h>

using namespace llvm;

int main(int argc, char **argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  fmt::print("{}\n", PluginLoader::getNumPlugins());
}
