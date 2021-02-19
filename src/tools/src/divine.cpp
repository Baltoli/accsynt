#include "klee_llvm.h"

#include <props/props.h>

#include <support/llvm_cloning.h>
#include <support/llvm_format.h>
#include <support/options.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string>
    PropertiesPath(cl::Positional, cl::Required, cl::desc("<properties file>"));

static cl::opt<std::string> OutputPath(
    "o", cl::desc("Bitcode output path"), cl::desc("filename"), cl::init("-"));

static cl::list<std::string> InputFilenames(
    cl::Positional, cl::desc("<input bitcode files...>"),
    cl::value_desc("filename"), cl::OneOrMore);

Value* copy_array(IRBuilder<>& irb, Value* array, Value* size)
{
  auto mod = irb.GetInsertBlock()->getParent()->getParent();

  auto elt_ty = cast<PointerType>(array->getType())->getElementType();

  auto copy = irb.CreateAlloca(elt_ty, size);

  auto mem_cpy = Intrinsic::getDeclaration(
      mod, Intrinsic::memcpy,
      {array->getType(), array->getType(), size->getType()});

  irb.CreateCall(
      mem_cpy,
      {copy, array,
       irb.CreateMul(
           size, ConstantInt::get(
                     size->getType(), elt_ty->getScalarSizeInBits() / 8)),
       irb.getFalse()});

  return copy;
}

int main(int argc, char** argv)
{
  hide_llvm_options();

  cl::ParseCommandLineOptions(argc, argv);
  auto& ctx = thread_context::get();
  SMDiagnostic Err;

  auto property_set = props::property_set::load(PropertiesPath);
  auto fn_name = property_set.type_signature.name;

  auto unified_mod = Module("klee_unified", ctx);

  auto fns_to_verify = std::vector<Function*> {};

  for (auto fn : InputFilenames) {
    auto&& mod = parseIRFile(fn, Err, ctx, true, "");
    if (!mod) {
      Err.print(argv[0], errs());
      return 1;
    }

    auto func = mod->getFunction(fn_name);

    fns_to_verify.push_back(copy_function(func, &unified_mod));
  }

  auto decls = klee_decls(unified_mod);

  auto entry = BasicBlock::Create(ctx, "entry", decls.main_);
  auto irb = IRBuilder<>(entry);

  if (!fns_to_verify.empty()) {
    auto args = decls.allocate_symbolic(irb, property_set.type_signature);

    auto ref = irb.CreateCall(fns_to_verify[0], args);

    for (auto arg : args) {
      auto arg_ty = arg->getType();
      if (auto ptr_ty = dyn_cast<PointerType>(arg_ty)) {
        copy_array(irb, arg, irb.CreateCall(decls.array_size));
      }
    }

    for (auto i = 1u; i < fns_to_verify.size(); ++i) {
      auto other = irb.CreateCall(fns_to_verify[i], args);
    }
  }

  irb.CreateRet(irb.getInt32(0));

  verifyModule(unified_mod, &errs());

  if (OutputPath == "-") {
    fmt::print("{}\n", unified_mod);
  } else {
    auto ec = std::error_code {};
    auto os = raw_fd_ostream(OutputPath, ec);
    WriteBitcodeToFile(unified_mod, os);
  }
}
