#include "options.h"

using namespace llvm;

cl::opt<std::string>
    PropertiesPath(cl::Positional, cl::Required, cl::desc("<properties file>"));

cl::opt<std::string>
    LibraryPath(cl::Positional, cl::Required, cl::desc("<shared library>"));

cl::opt<std::string>
    Parameter(cl::Positional, cl::Required, cl::desc("<parameter name>"));

cl::OptionCategory Experiments(
    "Experimental options",
    "These control parameters for an individual experimental run");

cl::opt<int> Start(
    "start", cl::desc("Variation starting point"), cl::value_desc("integer"),
    cl::init(0), cl::cat(Experiments));

cl::opt<int>
    End("end", cl::desc("Variation ending point"), cl::value_desc("integer"),
        cl::init(10'000), cl::cat(Experiments));

cl::opt<int> Step(
    "step", cl::desc("Variation step"), cl::value_desc("integer"),
    cl::init(100), cl::cat(Experiments));

cl::opt<int> Reps(
    "reps", cl::desc("Number of repetitions to execute for each step"),
    cl::value_desc("integer"), cl::init(5), cl::cat(Experiments));

cl::OptionCategory
    Memory("Memory options", "Fine-tuning memory allocation sizes and checks");

cl::opt<int> MemSize(
    "memsize", cl::desc("Cube-root of maximum physical memory allocation size"),
    cl::value_desc("integer"), cl::init(32), cl::cat(Memory));