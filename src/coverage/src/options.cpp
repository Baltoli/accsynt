#include "options.h"

using namespace llvm;

cl::opt<std::string>
    InputFile("input-file", cl::desc("Input bitcode file"), cl::init("-"));

cl::alias
    InputFileA("i", cl::desc("Alias for input-file"), cl::aliasopt(InputFile));

cl::opt<std::string>
    FunctionName("function", cl::desc("Function to test"), cl::init("-"));

cl::opt<std::string> ManifestPath(
    "manifest",
    cl::desc("Manifest path with functions and groups to test coverage for"),
    cl::init("-"));

cl::alias FunctionNameA(
    "f", cl::desc("Alias for function"), cl::aliasopt(FunctionName));

cl::opt<int> NumInputs(
    "num-inputs", cl::desc("The number of distinct inputs to generate"),
    cl::init(10));

cl::alias
    NumInputsA("n", cl::desc("Alias for num-inputs"), cl::aliasopt(NumInputs));

cl::opt<int> Reps(
    "reps", cl::desc("The number of repeated experiments to run at each size"),
    cl::init(1));

cl::opt<bool> Header(
    "header", cl::desc("Print a header for this individual run"),
    cl::init(true));

cl::opt<bool> Single(
    "single", cl::desc("Print only at the last iteration"), cl::init(false));

cl::alias SingleA("s", cl::desc("Alias for single"), cl::aliasopt(Single));

cl::opt<bool>
    Progress("progress", cl::desc("Print progress to stderr"), cl::init(false));
