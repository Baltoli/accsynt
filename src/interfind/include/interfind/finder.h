#pragma once

#include <interfind/analysis.h>

#include <props/props.h>
#include <support/dynamic_library.h>

#include <nlohmann/json_fwd.hpp>

#include <filesystem>
#include <string>

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
  finder(llvm::Module&, nlohmann::json);

  llvm::Module& module_;
  props::signature signature_;
  std::filesystem::path library_path_;
  support::dynamic_library dynamic_library_;
};
}
