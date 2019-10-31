#include <support/llvm_cloning.h>

#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Transforms/Utils/Cloning.h>

using namespace llvm;

namespace support {

Function* copy_function(Function* f, Module* m)
{
  auto func = Function::Create(
      f->getFunctionType(), f->getLinkage(), f->getName(), m);

  auto v_map = ValueToValueMapTy{};
  auto returns = SmallVector<ReturnInst*, 8>{};

  auto f_arg_it = func->arg_begin();
  for (const auto& I : f->args()) {
    f_arg_it->setName(I.getName());
    v_map[&I] = &*f_arg_it++;
  }

  CloneFunctionInto(func, f, v_map, false, returns);

  return func;
}

std::unique_ptr<Module> copy_module_to(LLVMContext& ctx, Module const& m)
{
  llvm::verifyModule(m, &llvm::errs());

  if (&ctx == &m.getContext()) {
    return llvm::CloneModule(m);
  } else {
    std::string str;
    raw_string_ostream stream{ str };
    WriteBitcodeToFile(m, stream);

    auto buf = MemoryBuffer::getMemBuffer(stream.str());
    auto expect = parseBitcodeFile(buf->getMemBufferRef(), ctx);

    if (auto err = expect.takeError()) {
      m.print(llvm::errs(), nullptr);
      llvm::logAllUnhandledErrors(std::move(err), llvm::errs(), "");
      std::exit(1);
    }

    return std::move(expect.get());
  }
}
} // namespace support
