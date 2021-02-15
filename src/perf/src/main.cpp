#include "options.h"

#include <props/props.h>

#include <support/call_wrapper.h>
#include <support/dynamic_library.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

int main(int argc, char** argv)
try {
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto property_set = props::property_set::load(PropertiesPath);
  auto lib = dynamic_library(LibraryPath);

  /* auto mod = Module("test_mod", thread_context::get()); */

  /* auto ref = call_wrapper(property_set.type_signature, mod, fn_name, lib); */
} catch (props::parse_error& perr) {
  errs() << perr.what() << '\n';
  errs() << "  when parsing property set " << PropertiesPath << '\n';
  return 2;
} catch (dyld_error& derr) {
  errs() << derr.what() << '\n';
  errs() << "  when loading dynamic library " << LibraryPath << '\n';
  return 3;
}
