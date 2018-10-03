#include <fmt/format.h>

#include <llvm/Pass.h>
#include <llvm/PassRegistry.h>
#include <llvm/PassSupport.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/PluginLoader.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input bitcode file>"),
    cl::init("-"), cl::value_desc("filename"));

struct pass_finder : public PassRegistrationListener {
  pass_finder(std::string pn, PassRegistry& reg) :
    pass_name(pn)
  {
    reg.enumerateWith(this);
  }

  void passEnumerate(PassInfo const* pi) override
  {
    if(pi->getPassArgument() == pass_name) {
      pass_info = pi;
    }
  }

  PassInfo const* pass_info = nullptr;

private:
  std::string pass_name;
};

int main(int argc, char **argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto& reg = *PassRegistry::getPassRegistry();
  auto d = pass_finder{"detect", reg};

  if(!d.pass_info) {
    fmt::print(stderr, 
        "Could not load detection pass - make sure it is loaded with -load\n");
    return 1;
  }

  auto impl = d.pass_info->createPass();
  auto pm = legacy::PassManager{};
  pm.add(impl);

  LLVMContext Context;
  SMDiagnostic Err;

  auto&& mod = parseIRFile(InputFilename, Err, Context, true, "");
  if(!mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  pm.run(*mod);
}
