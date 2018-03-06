#include "load_module.h"

#include <dist/contexts.h>

#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

using namespace accsynt;
using namespace llvm;

std::unique_ptr<llvm::Module> load_module(const std::string& str)
{
  auto sm = SMDiagnostic{};
  auto buf = MemoryBuffer::getMemBuffer(str);
  auto mod = parseIR(*buf, sm, ThreadContext::get());

  if(!mod) {
    sm.print(nullptr, llvm::errs());
    std::exit(1);
  }

  llvm::verifyModule(*mod, &llvm::errs());
  return mod;
}
