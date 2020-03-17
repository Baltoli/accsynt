#include <coverage/coverage.h>

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InstVisitor.h>

namespace {

void handle_branch_event_trampoline(int id, bool val, char* inst)
{
  auto wrapper = reinterpret_cast<coverage::wrapper*>(inst);
  wrapper->handle_branch_event(id, val);
}

class instrument_visitor : public llvm::InstVisitor<instrument_visitor> {
public:
  instrument_visitor(std::map<llvm::BranchInst*, int>& ids)
      : next_id_(0)
      , ids_(ids)
  {
  }

  void visitBranchInst(llvm::BranchInst& inst)
  {
    if (inst.isConditional()) {
      ids_[&inst] = next_id_;
      ++next_id_;
    }
  }

private:
  int next_id_;
  std::map<llvm::BranchInst*, int>& ids_;
};

} // namespace

namespace coverage {

uint64_t wrapper::call(support::call_builder& builder)
{
  if (!instrumented_) {
    instrument();
  }

  llvm::errs() << *implementation()->getParent() << '\n';

  return support::call_wrapper::call(builder);
}

void wrapper::instrument()
{
  using namespace std::placeholders;

  auto& ctx = support::thread_context::get();

  auto i8_t = llvm::IntegerType::get(ctx, 8);
  auto p_i8_t = llvm::PointerType::getUnqual(i8_t);

  instance_ptr_ = new llvm::GlobalVariable(
      *implementation()->getParent(), p_i8_t, true,
      llvm::GlobalValue::ExternalLinkage, nullptr, "instance");
  engine()->addGlobalMapping(instance_ptr_, (void*)this);

  instrument_visitor(branch_ids_).visit(implementation());

  for (auto [branch, id] : branch_ids_) {
    visits_[id] = detail::branch_visits::None;
  }

  instrumented_ = true;
}

void wrapper::handle_branch_event(int id, bool value) {}

size_t wrapper::total_conditions() const { return 0; }
size_t wrapper::covered_conditions() const { return 0; }
double wrapper::coverage() const { return 0.0; }

} // namespace coverage
