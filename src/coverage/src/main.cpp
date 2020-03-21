#include "options.h"

#include <coverage/coverage.h>

#include <support/load_module.h>

using namespace llvm;

int main(int argc, char** argv) { cl::ParseCommandLineOptions(argc, argv); }
