#include <fmt/format.h>

#include <llvm/Pass.h>
#include <llvm/PassRegistry.h>
#include <llvm/PassSupport.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/PluginLoader.h>

using namespace llvm;

struct pass_finder : public PassRegistrationListener {
  pass_finder(std::string pn) :
    pass_name(pn)
  {
  }

  void passEnumerate(PassInfo const* pi)
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
  auto d = pass_finder{"detect"};

  reg.enumerateWith(&d);
  if(d.pass_info) {
    auto impl = d.pass_info->createPass();
    auto pm = legacy::PassManager{};

    pm.add(impl);
  }
}
