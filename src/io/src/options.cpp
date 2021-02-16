#include "options.h"

using namespace llvm;

cl::opt<std::string>
    PropertiesPath(cl::Positional, cl::Required, cl::desc("<properties file>"));

cl::opt<std::string>
    LibraryPath(cl::Positional, cl::Required, cl::desc("<shared library>"));

cl::OptionCategory
    Memory("Memory options", "Fine-tuning memory allocation sizes and checks");

cl::opt<int> MemSize(
    "memsize", cl::desc("Cube-root of maximum physical memory allocation size"),
    cl::value_desc("integer"), cl::init(32), cl::cat(Memory));
