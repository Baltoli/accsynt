#include "options.h"

using namespace llvm;

cl::opt<std::string>
    PropertiesPath(cl::Positional, cl::Required, cl::desc("<properties file>"));

cl::opt<std::string>
    LibraryPath(cl::Positional, cl::Required, cl::desc("<shared library>"));

cl::opt<std::string>
    Parameter(cl::Positional, cl::Required, cl::desc("<parameter name>"));
