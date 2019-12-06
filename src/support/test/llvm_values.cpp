#include <catch2/catch.hpp>

#include <support/llvm_values.h>
#include <support/load_module.h>

using namespace support;
using namespace llvm;

#define VALUE(name)                                                            \
  auto name = get_by_name(fn, #name);                                          \
  REQUIRE(name);

TEST_CASE("can collect uses of values")
{
  auto mod = load_module(RESOURCE_DIR "deps.ll");
  auto& fn = *mod->begin();

  VALUE(v2);
  VALUE(v3);
  VALUE(v4);
  VALUE(v5);

  auto v4_uses = all_uses(v4);
  REQUIRE(v4_uses.size() == 2);
  REQUIRE(v4_uses.find(v5) != v4_uses.end());
  REQUIRE(v4_uses.find(v3) == v4_uses.end());

  auto v2_uses = all_uses(v2);
  REQUIRE(v2_uses.size() == 3);
  REQUIRE(v2_uses.find(v3) != v2_uses.end());
  REQUIRE(v2_uses.find(v4) == v2_uses.end());
  REQUIRE(v2_uses.find(v5) != v2_uses.end());
}

TEST_CASE("can collect dependencies of values")
{
  auto mod = load_module(RESOURCE_DIR "deps.ll");
  auto& fn = *mod->begin();

  VALUE(arg0);
  VALUE(arg1);
  VALUE(arg2);
  VALUE(v0);
  VALUE(v1);
  VALUE(v2);
  VALUE(v3);
  VALUE(v4);
  VALUE(v5);

  SECTION("full tracing")
  {
    auto v5_deps = all_deps(v5);
    REQUIRE(v5_deps.size() == 8);
    REQUIRE(v5_deps.find(arg0) != v5_deps.end());
    REQUIRE(v5_deps.find(arg1) != v5_deps.end());
    REQUIRE(v5_deps.find(arg2) != v5_deps.end());
    REQUIRE(v5_deps.find(v0) != v5_deps.end());
    REQUIRE(v5_deps.find(v1) != v5_deps.end());
    REQUIRE(v5_deps.find(v2) != v5_deps.end());
    REQUIRE(v5_deps.find(v3) != v5_deps.end());
    REQUIRE(v5_deps.find(v4) != v5_deps.end());

    auto arg0_deps = all_deps(arg0);
    REQUIRE(arg0_deps.empty());

    auto v4_deps = all_deps(v4);
    REQUIRE(v4_deps.size() == 2);
    REQUIRE(v4_deps.find(arg0) != v4_deps.end());
    REQUIRE(v4_deps.find(arg1) != v4_deps.end());
    REQUIRE(v4_deps.find(arg2) == v4_deps.end());
    REQUIRE(v4_deps.find(v0) == v4_deps.end());
    REQUIRE(v4_deps.find(v1) == v4_deps.end());
    REQUIRE(v4_deps.find(v2) == v4_deps.end());
    REQUIRE(v4_deps.find(v3) == v4_deps.end());
    REQUIRE(v4_deps.find(v4) == v4_deps.end());
  }

  SECTION("tracing to roots")
  {
    auto v5_deps = all_deps(v5, { v3 });
    REQUIRE(v5_deps.size() == 4);
    REQUIRE(v5_deps.find(arg0) != v5_deps.end());
    REQUIRE(v5_deps.find(arg1) != v5_deps.end());
    REQUIRE(v5_deps.find(arg2) == v5_deps.end());
    REQUIRE(v5_deps.find(v0) == v5_deps.end());
    REQUIRE(v5_deps.find(v1) == v5_deps.end());
    REQUIRE(v5_deps.find(v2) == v5_deps.end());
    REQUIRE(v5_deps.find(v3) != v5_deps.end());
    REQUIRE(v5_deps.find(v4) != v5_deps.end());

    auto v2_deps = all_deps(v2, { v1, arg1 });
    REQUIRE(v2_deps.size() == 2);
    REQUIRE(v2_deps.find(arg0) == v2_deps.end());
    REQUIRE(v2_deps.find(arg1) != v2_deps.end());
    REQUIRE(v2_deps.find(arg2) == v2_deps.end());
    REQUIRE(v2_deps.find(v0) == v2_deps.end());
    REQUIRE(v2_deps.find(v1) != v2_deps.end());
    REQUIRE(v2_deps.find(v2) == v2_deps.end());
    REQUIRE(v2_deps.find(v3) == v2_deps.end());
    REQUIRE(v2_deps.find(v4) == v2_deps.end());

    auto v4_deps = all_deps(v4, { v0, v1, v2, v3 });
    REQUIRE(v4_deps.size() == 2);
    REQUIRE(v4_deps.find(arg0) != v4_deps.end());
    REQUIRE(v4_deps.find(arg1) != v4_deps.end());
    REQUIRE(v4_deps.find(arg2) == v4_deps.end());
    REQUIRE(v4_deps.find(v0) == v4_deps.end());
    REQUIRE(v4_deps.find(v1) == v4_deps.end());
    REQUIRE(v4_deps.find(v2) == v4_deps.end());
    REQUIRE(v4_deps.find(v3) == v4_deps.end());
    REQUIRE(v4_deps.find(v4) == v4_deps.end());
  }
}

TEST_CASE("can topologically sort collections of values")
{
  auto mod = load_module(RESOURCE_DIR "deps.ll");
  auto& fn = *mod->begin();

  VALUE(arg0);
  VALUE(arg1);
  VALUE(arg2);
  VALUE(v0);
  VALUE(v1);
  VALUE(v2);
  VALUE(v3);
  VALUE(v4);
  VALUE(v5);

  SECTION("values aren't lost or created")
  {
    for (auto v : { arg0, arg1, arg2, v0, v1, v2, v3, v4, v5 }) {
      auto deps = all_deps(v);
      auto s_deps = topo_sort(deps);

      REQUIRE(deps.size() == s_deps.size());
    }
  }

  SECTION("sorting is correct")
  {
#define LOC(v) std::find(beg, end, v)

    auto v5_sort = topo_sort(all_deps(v5));

    auto beg = v5_sort.begin();
    auto end = v5_sort.end();

    for (auto v : { arg0, arg1, arg2, v0, v1, v2, v3, v4 }) {
      REQUIRE(std::find(beg, end, v) != end);
    }

    REQUIRE(LOC(v0) > LOC(arg0));
    REQUIRE(LOC(v0) > LOC(arg1));

    REQUIRE(LOC(v1) > LOC(v0));
    REQUIRE(LOC(v1) > LOC(arg2));

    REQUIRE(LOC(v2) > LOC(v1));
    REQUIRE(LOC(v2) > LOC(arg1));

    REQUIRE(LOC(v3) > LOC(v2));
    REQUIRE(LOC(v3) > LOC(arg2));

    REQUIRE(LOC(v4) > LOC(arg0));
    REQUIRE(LOC(v4) > LOC(arg1));

    REQUIRE(LOC(v5) > LOC(v3));
    REQUIRE(LOC(v5) > LOC(v4));
#undef LOC
  }
}
