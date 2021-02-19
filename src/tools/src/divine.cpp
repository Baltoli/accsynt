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

/*
 * The gist of what this tool needs to do is as follows:
 *
 * - Load in multiple bitcode files and a properties file
 * - For each of the modules loaded, rename and then clone the relevant function
 *   into a new module so that they're all in one place.
 * - Either hand-compile or link in testing runtime features (randomly generated
 *   inputs, calls to the divine svcomp features).
 *   - Possibly worth having a loop around this?
 * - Write everything out to a single bitcode file.
 */

Function* create_main(Module& mod)
{
  auto& ctx = mod.getContext();

  auto i32_ty = IntegerType::get(ctx, 32);
  auto char_ty = IntegerType::get(ctx, 8);
  auto argv_ty = char_ty->getPointerTo()->getPointerTo();

  auto fn_ty = FunctionType::get(i32_ty, {i32_ty, argv_ty}, false);

  auto func
      = Function::Create(fn_ty, GlobalValue::ExternalLinkage, "main", &mod);

  return func;
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

  auto main_f = create_main(unified_mod);

  auto entry = BasicBlock::Create(ctx, "entry", main_f);
  auto irb = IRBuilder<>(entry);
  irb.CreateRet(irb.getInt32(5));

  verifyModule(unified_mod, &errs());

  if (OutputPath == "-") {
    fmt::print("{}\n", unified_mod);
  } else {
    auto ec = std::error_code {};
    auto os = raw_fd_ostream(OutputPath, ec);
    WriteBitcodeToFile(unified_mod, os);
  }
}
