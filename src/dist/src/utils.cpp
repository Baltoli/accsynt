#include <dist/utils.h>

#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Transforms/Utils/Cloning.h>

using namespace llvm;

namespace util {

Function *copy_function(Function *f, Module *m)
{
  auto func = Function::Create(f->getFunctionType(), f->getLinkage(), f->getName(), m);

  auto v_map = ValueToValueMapTy{};
  auto returns = SmallVector<ReturnInst*, 8>{};

  auto f_arg_it = func->arg_begin();
  for(const auto& I : f->args()) {
    f_arg_it->setName(I.getName());
    v_map[&I] = &*f_arg_it++;
  }

  CloneFunctionInto(func, f, v_map, false, returns);

  return func;
}

std::unique_ptr<Module> copy_module_to(LLVMContext& ctx, Module *m)
{
  if(!m) {
    return nullptr;
  }

  if(&ctx == &m->getContext()) {
    return llvm::CloneModule(m);
  } else {
    std::string str;
    raw_string_ostream stream{str};
    WriteBitcodeToFile(m, stream);

    auto buf = MemoryBuffer::getMemBuffer(stream.str());
    return std::move(parseBitcodeFile(buf->getMemBufferRef(), ctx).get());
  }
}

std::unique_ptr<ExecutionEngine> create_engine(Module* m)
{
  auto&& clone = llvm::CloneModule(m);
  auto eb = EngineBuilder(std::move(clone));
  return std::unique_ptr<ExecutionEngine>{eb.create()};
}

}
