# AccSynt

AccSynt is a library for automatically learning the behaviour of an accelerator
by querying an interface for input / output examples.

## Building

Currently, AccSynt depends on LLVM 7 (trunk), and must be built using `g++` 7
(for its C++17 support). LLVM must be built from source, but any way of
obtaining `g++` can be used.

### LLVM 7

```
cd $BUILD_ROOT
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
cd llvm/tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
cd $BUILD_ROOT/llvm
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++-7 -DLLVM_ENABLE_RTTI=On -DCMAKE_INSTALL_PREFIX=$BUILD_ROOT/llvm-install ..
make install
```

Any other appropriate options to the LLVM CMake invocation can be used.

### AccSynt

```
cd $BUILD_ROOT
git clone https://github.com/Baltoli/accsynt.git
mkdir accsynt/build
cd accsynt/build
cmake -DCMAKE_CXX_COMPILER=g++-7 -DLLVM_DIR=$BUILD_ROOT/llvm-install/lib/cmake/llvm ../src
make
```
