#include "synth_options.h"

using namespace llvm;

cl::opt<int> MaxFragments(
    "max-fragments", cl::desc("Maximum fragments to combine"), cl::init(-1));

cl::opt<bool> DumpControl("dump-control",
    cl::desc("Dump control flow before synthesis"), cl::init(false));

cl::opt<bool> CountControl("count-control",
    cl::desc("Print the total number of control fragments before synthesis"),
    cl::init(false));

cl::opt<std::string> ControlOutputFile("control-output",
    cl::desc("Output file for control-flow output if it is enabled"),
    cl::init("-"));

cl::opt<bool> AllPrograms("all-programs",
    cl::desc(
        "Dump every candidated program to standard error during synthesis"),
    cl::init(false));

cl::opt<std::string> FragmentHash("hash",
    cl::desc("Only try programs that have the following hash"), cl::init("-"));

cl::opt<bool> InteractiveCount("count",
    cl::desc("Interactively print the running program count"), cl::init(false));
