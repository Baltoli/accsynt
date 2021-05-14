#include "oracle_options.h"

using namespace llvm;

namespace presyn::oracle::opts {

cl::opt<std::string> InputFilename(
    "i", cl::desc("Filename containing input data"), cl::value_desc("filename"),
    cl::init("-"));

cl::opt<std::string> SharedLibrary(
    cl::Positional, cl::desc("Shared library containing reference symbol"),
    cl::value_desc("<shared library>"), cl::Required);

} // namespace presyn::oracle::opts
