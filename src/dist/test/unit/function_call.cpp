#include "catch.h"
#include "load_module.h"

#include <dist/function_callable.h>

#include <llvm/IR/Module.h>

TEST_CASE( "LLVM functions can be wrapped and called", "[function]") {
  const auto mod_str = R"(
define i64 @func(i64) {
  %2 = add nsw i64 %0, 1
  ret i64 %2
}
  )";

  auto mod = load_module(mod_str);
  REQUIRE(mod);

  auto fc = FunctionCallable<long>(mod.get(), "func");

  SECTION( "error is not used by default" ) {
    REQUIRE(!fc.get_error());
    fc(0);
    REQUIRE(!fc.get_error());
  }

  SECTION( "callable behaves correctly" ) {
    REQUIRE(fc(0) == 1);
    REQUIRE(fc(-30) == -29);
    REQUIRE(fc(22) == 23);
  }
}
