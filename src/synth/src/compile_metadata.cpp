#include "compile_metadata.h"

using namespace llvm;

namespace synth {

compile_metadata::compile_metadata(llvm::Function *fn)
  : function(fn)
{
}

}
