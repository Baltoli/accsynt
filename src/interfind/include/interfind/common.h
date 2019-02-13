#pragma once

namespace llvm {
  class Value;
}

namespace interfind {

bool is_global(llvm::Value *val);

}
