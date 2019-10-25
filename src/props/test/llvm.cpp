#include <props/props.h>
#include <support/thread_context.h>

#include <catch2/catch.hpp>

#include <llvm/Support/raw_ostream.h>

using namespace props;
using namespace props::literals;
using namespace support;

using namespace llvm;

TEST_CASE("can get LLVM types from parameters")
{
  SECTION("for integer values")
  {
    auto p = param{ "any_name", base_type::integer, 0 };
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(32));
  }

  SECTION("for character values")
  {
    auto p = param{ "name", base_type::character, 0 };
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(8));
  }

  SECTION("for boolean values")
  {
    auto p = param{ "fwe", base_type::boolean, 0 };
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(1));
  }

  SECTION("for floating values")
  {
    auto p = param{ "name", base_type::floating, 0 };
    auto t = p.llvm_type();

    REQUIRE(t->isFloatTy());
  }

  SECTION("for integer pointers")
  {
    auto p = param{ "woo", base_type::integer, 1 };
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isIntegerTy(32));
  }

  SECTION("for character pointers")
  {
    auto p = param{ "niwefj", base_type::character, 1 };
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isIntegerTy(8));
  }

  SECTION("for boolean pointers")
  {
    auto p = param{ "efji", base_type::boolean, 2 };
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isPointerTy());

    auto t2 = cast<PointerType>(t1)->getElementType();
    REQUIRE(t2->isIntegerTy(1));
  }

  SECTION("for floating pointers")
  {
    auto p = param{ "rwe", base_type::floating, 2 };
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isPointerTy());

    auto t2 = cast<PointerType>(t1)->getElementType();
    REQUIRE(t2->isFloatTy());
  }
}

TEST_CASE("can get LLVM types from signatures")
{
  SECTION("with return")
  {
    auto sig = "int func()"_sig;
    /* auto ft = sig.function_type(); */

    /* REQUIRE(!ft->isVarArg()); */

    /* auto rt = ft->getReturnType(); */
    /* REQUIRE(rt->isIntegerTy(32)); */

    /* REQUIRE(ft->getNumParams() == 0); */
  }

  SECTION("with void return")
  {
    auto sig = "void fj_io(int *x, char cad, float y, float **z, bool b)"_sig;
    auto ft = sig.function_type();

    REQUIRE(!ft->isVarArg());

    auto rt = ft->getReturnType();
    REQUIRE(rt->isVoidTy());

    REQUIRE(ft->getNumParams() == 5);
    auto p0 = ft->getParamType(0);
    auto p1 = ft->getParamType(1);
    auto p2 = ft->getParamType(2);
    auto p3 = ft->getParamType(3);
    auto p4 = ft->getParamType(4);

    REQUIRE(p0->isPointerTy());
    REQUIRE(p1->isIntegerTy(8));
    REQUIRE(p2->isFloatTy());
    REQUIRE(p3->isPointerTy());
    REQUIRE(p4->isIntegerTy(1));

    auto p0_t = cast<PointerType>(p0)->getElementType();
    auto p3_t = cast<PointerType>(p3)->getElementType();

    REQUIRE(p0_t->isIntegerTy(32));
    REQUIRE(p3_t->isPointerTy());

    auto p3_t_t = cast<PointerType>(p3_t)->getElementType();

    REQUIRE(p3_t_t->isFloatTy());
  }
}

TEST_CASE("can create functions from signatures")
{
  auto mod = Module("test-mod", thread_context::get());
  auto sig = signature::parse("void test(int x, char *d, float *y, bool *b)");
  auto fn = sig.create_function(mod);

  REQUIRE(fn);

  auto ft = fn->getFunctionType();
  REQUIRE(ft->getReturnType()->isVoidTy());

  REQUIRE(ft->getNumParams() == 4);
  auto p0 = ft->getParamType(0);
  auto p1 = ft->getParamType(1);
  auto p2 = ft->getParamType(2);
  auto p3 = ft->getParamType(3);

  REQUIRE(p0->isIntegerTy(32));
  REQUIRE(p1->isPointerTy());
  REQUIRE(p2->isPointerTy());
  REQUIRE(p3->isPointerTy());

  auto p1_t = cast<PointerType>(p1)->getElementType();
  REQUIRE(p1_t->isIntegerTy(8));

  auto p2_t = cast<PointerType>(p2)->getElementType();
  REQUIRE(p2_t->isFloatTy());

  auto p3_t = cast<PointerType>(p3)->getElementType();
  REQUIRE(p3_t->isIntegerTy(1));
}
