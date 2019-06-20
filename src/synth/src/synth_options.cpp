#include "synth_options.h"

using namespace llvm;

cl::opt<int> MaxFragments(
    "max-fragments", cl::desc("Maximum fragments to combine"), cl::init(-1));

cl::opt<bool> DumpControl("dump-control",
    cl::desc("Dump control flow before synthesis"), cl::init(false));

cl::opt<bool> AllPrograms("all-programs",
    cl::desc(
        "Dump every candidated program to standard error during synthesis"),
    cl::init(false));
