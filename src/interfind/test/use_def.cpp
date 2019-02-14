#include <catch2/catch.hpp>

#include <interfind/use_def.h>

#include <support/llvm_values.h>
#include <support/load_module.h>

using namespace support;
using namespace interfind;
using namespace llvm;

#define VALUE(name) \
  auto name = get_by_name(fn, #name); \
  REQUIRE(name);

TEST_CASE("can compute use-def analyses", "[use_def]")
{
  auto mod = load_module(RESOURCE_DIR "deps.bc");
  auto& fn = *mod->begin();

  auto analysis = use_def_analysis(fn);

  VALUE(arg0); VALUE(arg1); VALUE(arg2);
  VALUE(v0); VALUE(v1); VALUE(v2);
  VALUE(v3); VALUE(v4); VALUE(v5);

  SECTION("basic dependency queries") {
    REQUIRE(!analysis.depends(arg0, v5));
    REQUIRE(!analysis.depends(arg1, v3));
    REQUIRE(!analysis.depends(arg2, v1));

    REQUIRE(analysis.depends(v0, arg0));
    REQUIRE(analysis.depends(v0, arg1));
    REQUIRE(!analysis.depends(v0, arg2));

    REQUIRE(analysis.depends(v1, v0));
    REQUIRE(analysis.depends(v1, arg0));
    REQUIRE(analysis.depends(v1, arg1));
    REQUIRE(analysis.depends(v1, arg2));
  }
}
