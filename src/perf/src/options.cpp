#include "options.h"

using namespace llvm;

cl::opt<std::string>
    PropertiesPath(cl::Positional, cl::Required, cl::desc("<properties file>"));

cl::opt<std::string>
    LibraryPath(cl::Positional, cl::Required, cl::desc("<shared library>"));

cl::list<std::string> Parameters(
    cl::Positional, cl::ZeroOrMore, cl::desc("<parameter names...>"));

cl::opt<std::string>
    Tag("tag", cl::desc("Tag for example in dataset"), cl::value_desc("string"),
        cl::init(""));

cl::alias TagA("t", cl::desc("Alias for -tag"), cl::aliasopt(Tag));

cl::OptionCategory Experiments(
    "Experimental options",
    "These control parameters for an individual experimental run");

cl::opt<PerfMode> Mode(
    cl::desc("Experiment mode:"),
    cl::values(
        clEnumValN(LinearSpace, "linear", "Sample from a uniform linear space"),
        clEnumValN(
            Random, "random", "Sample randomly (baseline implementation)"),
        clEnumValN(
            Single, "single", "Run a single randomly-sampled experiment")),
    cl::init(LinearSpace), cl::cat(Experiments));

cl::opt<int> Start(
    "start", cl::desc("Variation starting point"), cl::value_desc("integer"),
    cl::init(0), cl::cat(Experiments));

cl::opt<int>
    End("end", cl::desc("Variation ending point"), cl::value_desc("integer"),
        cl::init(10'000), cl::cat(Experiments));

cl::opt<int> Step(
    "step", cl::desc("Variation step"), cl::value_desc("integer"),
    cl::init(100), cl::cat(Experiments));

cl::opt<int> Values(
    "values", cl::desc("Number of values to try"), cl::value_desc("integer"),
    cl::init(20), cl::cat(Experiments));

cl::opt<int> Reps(
    "reps", cl::desc("Number of repetitions to execute for each step"),
    cl::value_desc("integer"), cl::init(5), cl::cat(Experiments));

cl::opt<int>
    Min("min", cl::desc("Minimum bounding value for random generation"),
        cl::value_desc("integer"), cl::init(-64), cl::cat(Experiments));

cl::opt<int>
    Max("max", cl::desc("Maximum bounding value for random generation"),
        cl::value_desc("integer"), cl::init(64), cl::cat(Experiments));

cl::opt<int> Independent(
    "independent", cl::desc("Fixed value for parameters held independent"),
    cl::value_desc("integer"), cl::init(4096), cl::cat(Experiments));

cl::alias IndependentA(
    "i", cl::desc("Alias for -independent"), cl::aliasopt(Independent),
    cl::cat(Experiments));

cl::OptionCategory
    Memory("Memory options", "Fine-tuning memory allocation sizes and checks");

cl::opt<int> MemSize(
    "memsize", cl::desc("Cube-root of maximum physical memory allocation size"),
    cl::value_desc("integer"), cl::init(32), cl::cat(Memory));

cl::opt<bool> Quiet(
    "quiet", cl::desc("Don't print timing values"), cl::value_desc("boolean"),
    cl::init(false));

cl::alias QuietA("q", cl::desc("Alias for -quiet"), cl::aliasopt(Quiet));
