#include <props/props.h>

#include <catch2/catch.hpp>

#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace props;

TEST_CASE("can get LLVM types from parameters") {
  SECTION("for integer values") {
    auto p = param{"any_name", data_type::integer, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(32));
  }

  SECTION("for floating values") {
    auto p = param{"name", data_type::floating, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isFloatTy());
  }

  SECTION("for integer pointers") {
    auto p = param{"woo", data_type::integer, 1};
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isIntegerTy(32));
  }

  SECTION("for floating pointers") {
    auto p = param{"rwe", data_type::floating, 2};
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isPointerTy());

    auto t2 = cast<PointerType>(t1)->getElementType();
    REQUIRE(t2->isFloatTy());
  }
}

TEST_CASE("can get LLVM types from signatures") {
  SECTION("with return") {
    auto sig = signature::parse("int func()");
    auto ft = sig.function_type();

    REQUIRE(!ft->isVarArg());

    auto rt = ft->getReturnType();
    REQUIRE(rt->isIntegerTy(32));

    REQUIRE(ft->getNumParams() == 0);
  }

  SECTION("with void return") {
    auto sig = signature::parse("void fj_io(int *x, float y, float **z)");
    auto ft = sig.function_type();

    REQUIRE(!ft->isVarArg());

    auto rt = ft->getReturnType();
    REQUIRE(rt->isVoidTy());

    REQUIRE(ft->getNumParams() == 3);
    auto p0 = ft->getParamType(0);
    auto p1 = ft->getParamType(1);
    auto p2 = ft->getParamType(2);

    REQUIRE(p0->isPointerTy());
    REQUIRE(p1->isFloatTy());
    REQUIRE(p2->isPointerTy());

    auto p0_t = cast<PointerType>(p0)->getElementType();
    auto p2_t = cast<PointerType>(p2)->getElementType();

    REQUIRE(p0_t->isIntegerTy(32));
    REQUIRE(p2_t->isPointerTy());

    auto p2_t_t = cast<PointerType>(p2_t)->getElementType();
    
    REQUIRE(p2_t_t->isFloatTy());
  }
}
