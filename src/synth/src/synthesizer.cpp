#include "synthesizer.h"

#include "generator.h"
#include "synth_options.h"

#include <support/llvm_cloning.h>
#include <support/thread_context.h>

#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>

using namespace props;
using namespace support;

using namespace llvm;

static cl::opt<std::string> DebugInput("debug", cl::Optional,
    cl::desc("Use debug input instead of generating"),
    cl::value_desc("filename"), cl::init(""));

namespace synth {

synthesizer::synthesizer(props::property_set ps, call_wrapper& wrap)
    : properties_(ps)
    , reference_(wrap)
    , examples_()
    , mod_("synth", thread_context::get())
{
}

void synthesizer::make_examples(argument_generator gen, size_t n)
{
  for (auto i = 0u; i < n; ++i) {
    auto cb = reference_.get_builder();
    gen.gen_args(cb);
    auto before = cb;
    auto ret = reference_.call(cb);
    examples_.push_back({ before, { ret, cb } });
  }
}

bool synthesizer::satisfies_examples(Function* cand) const
{
  auto wrap = call_wrapper{ properties_.type_signature, *cand->getParent(),
    cand->getName() };

  for (auto [in, out] : examples_) {
    auto ret = wrap.call(in);

    if (ret != out.return_value || in != out.output_args) {
      return false;
    }
  }

  return true;
}

Function* synthesizer::debug_generate()
{
  auto& ctx = thread_context::get();
  SMDiagnostic Err;

  auto&& mod = parseIRFile(DebugInput, Err, ctx, true, "");
  if (!mod) {
    Err.print("synth debug", errs());
    return nullptr;
  }

  auto name = properties_.type_signature.name;
  auto fn = copy_function(mod->getFunction(name), &mod_);

  if (!satisfies_examples(fn)) {
    return nullptr;
  }

  return fn;
}

Function* synthesizer::generate()
{
  if (DebugInput != "") {
    return debug_generate();
  }

  Function* cand = nullptr;

  auto attempts = 0;
  while (!cand) {
    // If we want to count the number of attempts interactively, print the
    // attempt number and clear the cursor back to the start of the line to
    // reprint it.
    if (InteractiveCount) {
      errs() << attempts << '\r';
    }

    cand = candidate();

    if (!cand) {
      return nullptr;
    }

    if (!satisfies_examples(cand)) {
      cand->eraseFromParent();
      cand = nullptr;
    }

    ++attempts;
  }

  outs() << "; synthesized a valid solution\n";
  outs() << "; attempts: " << attempts << '\n';
  return cand;
}

Function* synthesizer::create_stub()
{
  return properties_.type_signature.create_function(mod_);
}

std::string null_synth::name() const { return "Null"; }

Function* null_synth::generate() { return nullptr; }
} // namespace synth
