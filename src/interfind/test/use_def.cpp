#include <catch2/catch.hpp>

#include <interfind/use_def.h>

#include <support/llvm_values.h>
#include <support/load_module.h>

using namespace support;
using namespace interfind;
using namespace llvm;

TEST_CASE("can compute use-def analyses", "[use_def]")
{
  auto mod = load_module(RESOURCE_DIR "adds.bc");
  auto fn = mod->getFunction("adds");
}
