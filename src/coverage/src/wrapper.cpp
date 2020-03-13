#include <coverage/coverage.h>

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/InstVisitor.h>

namespace {

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

  return support::call_wrapper::call(builder);
}

void wrapper::instrument()
{
  auto& ctx = support::thread_context::get();

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
