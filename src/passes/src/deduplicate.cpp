#include <passes/passes.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <llvm/Pass.h>

#include <memory>
#include <set>

using namespace llvm;

namespace {

struct Deduplicate : public FunctionPass {
  static char ID;
  Deduplicate()
      : FunctionPass(ID)
  {
  }

  bool runOnFunction(Function& F) override;
};

std::set<int> duplicated_operands(Instruction* instr)
{
  auto seen = std::set<Value*>{};
  auto idxs = std::set<int>{};

  for (auto i = 0u; i < instr->getNumOperands(); ++i) {
    auto operand = instr->getOperand(i);

    if (seen.find(operand) != seen.end()) {
      idxs.insert(i);
    }

    seen.insert(operand);
  }

  return idxs;
}

Value* create_noop_from(Instruction* instr, size_t idx)
{
  auto val = instr->getOperand(idx);

  auto ty = val->getType();
  auto cast = CastInst::Create(Instruction::BitCast, val, ty, "nop", instr);

  return cast;
}

bool Deduplicate::runOnFunction(Function& F)
{
  for (auto& bb : F) {
    for (auto& inst : bb) {
      for (auto idx : duplicated_operands(&inst)) {
        auto noop = create_noop_from(&inst, idx);
        inst.setOperand(idx, noop);
      }
    }
  }

  return false;
}

char Deduplicate::ID = 0;
static RegisterPass<Deduplicate> X(
    "dedup", "Remove duplicated instruction operands", false, false);
} // namespace

std::unique_ptr<llvm::FunctionPass> createDeduplicatePass()
{
  return std::make_unique<Deduplicate>();
}
