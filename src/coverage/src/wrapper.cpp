#include <coverage/coverage.h>

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstVisitor.h>

#include <numeric>

namespace {

void handle_branch_event_trampoline(int id, bool val, char* inst)
{
  auto wrapper = reinterpret_cast<coverage::wrapper*>(inst);
  wrapper->handle_branch_event(id, val);
}

class instrument_visitor : public llvm::InstVisitor<instrument_visitor> {
public:
  instrument_visitor(
      std::map<llvm::BranchInst*, int>& ids, llvm::Value* inst,
      llvm::Function* tram)
      : next_id_(0)
      , ids_(ids)
      , instance_ptr_(inst)
      , trampoline_(tram)
  {
  }

  void visitBranchInst(llvm::BranchInst& inst)
  {
    auto build = llvm::IRBuilder<>(&inst);

    if (inst.isConditional()) {
      build.CreateCall(
          trampoline_,
          {build.getInt32(next_id_), inst.getCondition(), instance_ptr_});

      ids_[&inst] = next_id_;
      ++next_id_;
    }
  }

private:
  int next_id_;
  std::map<llvm::BranchInst*, int>& ids_;

  llvm::Value* instance_ptr_;
  llvm::Function* trampoline_;
};

} // namespace

namespace coverage {

uint64_t wrapper::call(support::call_builder& builder)
{
  if (!instrumented_) {
    instrument();
  }

  return support::call_wrapper::call(builder);
}

void wrapper::instrument()
{
  using namespace std::placeholders;

  auto& ctx = support::thread_context::get();
  auto mod = implementation()->getParent();

  auto i8_t = llvm::IntegerType::get(ctx, 8);
  auto p_i8_t = llvm::PointerType::getUnqual(i8_t);

  // Add pointer back to this instance of the wrapper class so that we can call
  // the trampoline properly.
  auto instance_ptr = new llvm::GlobalVariable(
      *mod, i8_t, true, llvm::GlobalValue::ExternalLinkage, nullptr,
      "instance");
  engine()->addGlobalMapping(instance_ptr, (void*)this);

  // Create another global mapping for the trampoline function. The visitor then
  // receives this external function as its callback to insert.
  auto i32_t = llvm::IntegerType::get(ctx, 32);
  auto bool_t = llvm::IntegerType::get(ctx, 1);
  auto void_t = llvm::Type::getVoidTy(ctx);
  auto trampoline_t
      = llvm::FunctionType::get(void_t, {i32_t, bool_t, p_i8_t}, false);

  auto func = llvm::Function::Create(
      trampoline_t, llvm::GlobalValue::ExternalLinkage, "trampoline", *mod);
  engine()->addGlobalMapping(func, (void*)handle_branch_event_trampoline);

  instrument_visitor(branch_ids_, instance_ptr, func).visit(implementation());

  for (auto [branch, id] : branch_ids_) {
    visits_[id] = detail::branch_visits::None;
  }

  instrumented_ = true;
}

void wrapper::handle_branch_event(int id, bool value)
{
  visits_[id] = detail::branch_visits(
      visits_[id]
      | (value ? detail::branch_visits::True : detail::branch_visits::False));
}

size_t wrapper::total_conditions() const { return branch_ids_.size() * 2; }

size_t wrapper::covered_conditions() const
{
  return std::accumulate(
      branch_ids_.begin(), branch_ids_.end(), 0, [this](auto acc, auto p) {
        auto val = visits_.at(p.second);

        if (val == detail::branch_visits::None) {
          return acc;
        } else if (
            val == detail::branch_visits::True
            || val == detail::branch_visits::False) {
          return acc + 1;
        } else {
          return acc + 2;
        }
      });
}

double wrapper::coverage() const
{
  if (!instrumented_) {
    return 0;
  }

  return static_cast<double>(covered_conditions())
         / static_cast<double>(total_conditions());
}

} // namespace coverage
