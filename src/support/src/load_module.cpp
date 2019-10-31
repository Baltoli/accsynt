#include <support/load_module.h>
#include <support/thread_context.h>

#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

namespace support {

std::unique_ptr<Module> parse_module(std::string const& str)
{
  auto sm = SMDiagnostic{};
  auto buf = MemoryBuffer::getMemBuffer(str);
  auto mod = parseIR(*buf, sm, thread_context::get());

  if (!mod) {
    sm.print(nullptr, llvm::errs());
    std::exit(1);
  }

  verifyModule(*mod, &errs());
  return mod;
}

std::unique_ptr<Module> load_module(std::string const& path)
{
  auto& ctx = thread_context::get();
  auto err = SMDiagnostic{};

  auto mod = parseIRFile(path, err, ctx, true, "");
  if (!mod) {
    err.print("load_module", errs());
    throw std::runtime_error("Error loading module: " + path);
  }

  return mod;
}
} // namespace support
