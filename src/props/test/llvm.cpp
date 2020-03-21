#include <props/props.h>
#include <support/thread_context.h>

#include <catch2/catch.hpp>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/raw_ostream.h>

using namespace props;
using namespace props::literals;
using namespace support;

using namespace llvm;

TEST_CASE("can get LLVM types from parameters")
{
  SECTION("for integer values")
  {
    auto p = param {"any_name", base_type::integer, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(32));
  }

  SECTION("for character values")
  {
    auto p = param {"name", base_type::character, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(8));
  }

  SECTION("for boolean values")
  {
    auto p = param {"fwe", base_type::boolean, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isIntegerTy(1));
  }

  SECTION("for floating values")
  {
    auto p = param {"name", base_type::floating, 0};
    auto t = p.llvm_type();

    REQUIRE(t->isFloatTy());
  }

  SECTION("for integer pointers")
  {
    auto p = param {"woo", base_type::integer, 1};
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isIntegerTy(32));
  }

  SECTION("for character pointers")
  {
    auto p = param {"niwefj", base_type::character, 1};
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isIntegerTy(8));
  }

  SECTION("for boolean pointers")
  {
    auto p = param {"efji", base_type::boolean, 2};
    auto t = p.llvm_type();

    REQUIRE(t->isPointerTy());

    auto t1 = cast<PointerType>(t)->getElementType();
    REQUIRE(t1->isPointerTy());

    auto t2 = cast<PointerType>(t1)->getElementType();
    REQUIRE(t2->isIntegerTy(1));
  }

  SECTION("for floating pointers")
  {
    auto p = param {"rwe", base_type::floating, 2};
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

TEST_CASE("Can create data types from LLVM types")
{
  auto& ctx = thread_context::get();

  SECTION("Booleans")
  {
    auto ty = Type::getInt1Ty(ctx);
    auto dt = data_type::from_llvm(ty);

    REQUIRE(dt);
    REQUIRE(*dt == data_type {base_type::boolean, 0});
  }

  SECTION("Chars")
  {
    auto ty = Type::getInt8Ty(ctx);
    auto dt = data_type::from_llvm(ty);

    REQUIRE(dt);
    REQUIRE(*dt == data_type {base_type::character, 0});
  }

  SECTION("Ints")
  {
    auto ty = Type::getInt32Ty(ctx);
    auto dt = data_type::from_llvm(ty);

    REQUIRE(dt);
    REQUIRE(*dt == data_type {base_type::integer, 0});
  }

  SECTION("Floats")
  {
    auto ty = Type::getFloatTy(ctx);
    auto dt = data_type::from_llvm(ty);

    REQUIRE(dt);
    REQUIRE(*dt == data_type {base_type::floating, 0});
  }

  SECTION("Pointers")
  {
    auto t1 = Type::getFloatPtrTy(ctx);
    auto d1 = data_type::from_llvm(t1);
    REQUIRE(d1);
    REQUIRE(*d1 == data_type {base_type::floating, 1});

    auto t2 = Type::getInt32PtrTy(ctx);
    auto d2 = data_type::from_llvm(t2);
    REQUIRE(d2);
    REQUIRE(*d2 == data_type {base_type::integer, 1});

    auto t3 = Type::getInt8PtrTy(ctx)->getPointerTo()->getPointerTo();
    auto d3 = data_type::from_llvm(t3);
    REQUIRE(d3);
    REQUIRE(*d3 == data_type {base_type::character, 3});
  }

  SECTION("Others") {}
}

TEST_CASE("Can create signatures from LLVM function types")
{
  auto& ctx = thread_context::get();
  auto void_ty = Type::getVoidTy(ctx);
  auto bool_ty = Type::getInt1Ty(ctx);
  auto char_ty = Type::getInt8Ty(ctx);
  auto int_ty = Type::getInt32Ty(ctx);
  auto float_ty = Type::getFloatTy(ctx);

  SECTION("Simple function type")
  {
    auto func_ty = FunctionType::get(void_ty, {}, false);
    auto sig = signature::from_llvm(func_ty);

    REQUIRE(sig);
    REQUIRE(sig->parameters.empty());
  }

  SECTION("With parameters")
  {
    auto func_ty = FunctionType::get(void_ty, {int_ty, float_ty}, false);
    auto sig = signature::from_llvm(func_ty);

    REQUIRE(sig);
    REQUIRE(sig->parameters.size() == 2);

    REQUIRE(sig->parameters[0].type == base_type::integer);
    REQUIRE(sig->parameters[0].pointer_depth == 0);
    REQUIRE(sig->parameters[1].type == base_type::floating);
    REQUIRE(sig->parameters[1].pointer_depth == 0);
  }

  SECTION("With return type")
  {
    auto func_ty = FunctionType::get(int_ty, {char_ty->getPointerTo()}, false);
    auto sig = signature::from_llvm(func_ty, "woo");

    REQUIRE(sig);
    REQUIRE(sig->name == "woo");
    REQUIRE(sig->parameters.size() == 1);

    REQUIRE(sig->return_type);
    REQUIRE(sig->return_type->base == base_type::integer);
    REQUIRE(sig->return_type->pointers == 0);

    REQUIRE(sig->parameters[0].type == base_type::character);
    REQUIRE(sig->parameters[0].pointer_depth == 1);
  }

  SECTION("More complex")
  {
    auto func_ty = FunctionType::get(
        float_ty->getPointerTo(),
        {bool_ty->getPointerTo()->getPointerTo(), int_ty,
         float_ty->getPointerTo()},
        false);

    auto sig = signature::from_llvm(func_ty, "two");

    REQUIRE(sig);
    REQUIRE(sig->name == "two");
    REQUIRE(sig->parameters.size() == 3);

    REQUIRE(sig->return_type);
    REQUIRE(sig->return_type->base == base_type::floating);
    REQUIRE(sig->return_type->pointers == 1);

    REQUIRE(sig->parameters[0].type == base_type::boolean);
    REQUIRE(sig->parameters[0].pointer_depth == 2);

    REQUIRE(sig->parameters[1].type == base_type::integer);
    REQUIRE(sig->parameters[1].pointer_depth == 0);

    REQUIRE(sig->parameters[2].type == base_type::floating);
    REQUIRE(sig->parameters[2].pointer_depth == 1);
  }
}
