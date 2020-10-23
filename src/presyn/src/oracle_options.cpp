#include "oracle_options.h"

using namespace llvm;

namespace presyn::oracle::opts {

cl::opt<std::string> InputFilename(
    "i", cl::desc("Filename containing input data"), cl::value_desc("filename"),
    cl::init("-"));

}
