#include "options.h"

using namespace llvm;

namespace presyn::opt {

cl::opt<std::string> SigFile("s",
    cl::desc("Specify the file containing the function signature"),
    cl::value_desc("filename"));

}
