#include "load_module.h"

#include <dist/contexts.h>

#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

std::unique_ptr<llvm::Module> load_module(const std::string& str)
{
  /* const auto str = R"( */
/* @_ZTIl = external constant i8* */
/* declare i8* @__cxa_allocate_exception(i64) */
/* declare void @__cxa_throw(i8*, i8*, i8*) */
/* define void @throw_val(i64) { */
  /* %2 = alloca i64, align 8 */
  /* store i64 %0, i64* %2, align 8 */
  /* %3 = call i8* @__cxa_allocate_exception(i64 8) */
  /* %4 = bitcast i8* %3 to i64* */
  /* %5 = load i64, i64* %2, align 8 */
  /* store i64 %5, i64* %4, align 16 */
  /* call void @__cxa_throw(i8* %3, i8* bitcast (i8** @_ZTIl to i8*), i8* null) */
  /* unreachable */
/* } */
/* )"; */

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
