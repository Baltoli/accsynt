#include <support/load_module.h>
#include <support/thread_context.h>

#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

namespace support {

std::unique_ptr<llvm::Module> parse_module(const std::string& str)
{
  auto sm = SMDiagnostic{};
  auto buf = MemoryBuffer::getMemBuffer(str);
  auto mod = parseIR(*buf, sm, thread_context::get());

  if(!mod) {
    sm.print(nullptr, llvm::errs());
    std::exit(1);
  }

  llvm::verifyModule(*mod, &llvm::errs());
  return mod;
}

}
