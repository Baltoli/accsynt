#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <vector>

namespace presyn {

std::vector<llvm::Value*> small_constants(llvm::Type*);

}
