#include "options.h"

using namespace llvm;

cl::opt<std::string>
    InputFile("input-file", cl::desc("Input bitcode file"), cl::init("-"));

cl::alias
    InputFileA("i", cl::desc("Alias for input-file"), cl::aliasopt(InputFile));
