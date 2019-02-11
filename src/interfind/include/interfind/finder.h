#pragma once

#include <interfind/analysis.h>

#include <nlohmann/json_fwd.hpp>

namespace llvm {
  class Module;
}

namespace interfind {

/**
 * The main entry point into InterFind functionality.
 *
 * This class is responsible for accepting input data and dispatching out to
 * different components of the library to perform work. It is instantiated with
 * some configuration and a module to work on, and when it performs its analysis
 * it modifies the module given to it and returns some analysis information.
 */
class finder {
public:
  static analysis_result run(llvm::Module&, nlohmann::json);

private:
};

}
