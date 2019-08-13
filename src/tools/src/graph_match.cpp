#include "algorithm.h"
#include "match.h"

#include <support/instr_count.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#include <vector>

using namespace support;
using namespace llvm;

static cl::opt<std::string> FunctionName(
    cl::Positional, cl::desc("<function>"), cl::value_desc("function name"));

static cl::opt<std::string> FunctionName2(
    cl::Positional, cl::desc("<function>"), cl::value_desc("function name 2"));

static cl::list<std::string> InputFiles(cl::Positional,
    cl::desc("<bitcode files>"), cl::OneOrMore, cl::value_desc("filenames"));

static cl::opt<std::string> OutputFilename("o",
    cl::desc("Filename to save the generated constraints to"),
    cl::value_desc("filename"), cl::init("-"));

void run_norm_passes(Module& mod)
{
  auto pm = legacy::PassManager();

  auto pmb = PassManagerBuilder();
  pmb.OptLevel = 2;
  pmb.DisableUnrollLoops = true;
  pmb.LoopVectorize = false;
  pmb.SLPVectorize = false;
  pmb.populateModulePassManager(pm);

  pm.run(mod);
}

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  LLVMContext Context;
  SMDiagnostic Err;

  auto&& first_mod = parseIRFile(InputFiles[0], Err, Context, true, "");
  auto&& second_mod = parseIRFile(InputFiles[1], Err, Context, true, "");

  run_norm_passes(*first_mod);
  run_norm_passes(*second_mod);

  auto first_fn = first_mod->getFunction(FunctionName);
  auto second_fn = second_mod->getFunction(FunctionName2);

  auto graphs = std::vector<Graph> {};
  graphs.push_back(from_function(*first_fn));
  graphs.push_back(from_function(*second_fn));

  /* for (auto it = std::next(InputFiles.begin()); it != InputFiles.end(); ++it)
   * { */
  /*   auto&& next_mod = parseIRFile(*it, Err, Context, true, ""); */
  /*   auto next_fn = next_mod->getFunction(FunctionName); */

  /*   graphs.push_back(from_function(*next_fn)); */
  /* } */

  /* auto&& modA = parseIRFile(InputA, Err, Context, true, ""); */
  /* if (!modA) { */
  /*   Err.print(argv[0], errs()); */
  /*   return 1; */
  /* } */

  /* auto&& modB = parseIRFile(InputB, Err, Context, true, ""); */
  /* if (!modB) { */
  /*   Err.print(argv[0], errs()); */
  /*   return 1; */
  /* } */

  /* auto fnA = modA->getFunction(FunctionName); */
  /* auto fnB = modB->getFunction(FunctionName); */

  /* auto graphA = from_function(*fnA); */
  /* auto graphB = from_function(*fnB); */
  compute(graphs, instr_count(*first_fn), instr_count(*second_fn));
}

/*
define float @dot(i32 %n, float* %a, float* %b) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  %0 = fsub float %9, %12
  %1 = fmul float %0, %0
  ret float %10

header:                                           ; preds = %entry
  br label %loop-check

body:                                             ; preds = %loop-check
  %2 = getelementptr float, float* %a, i32 %iter
  %3 = load float, float* %2
  %4 = getelementptr float, float* %b, i32 %iter
  %5 = load float, float* %4
  %6 = fmul float %3, %5
  %7 = fadd float %10, %6
  br label %loop-check

loop_exit:                                        ; preds = %loop-check
  %8 = fsub float %12, %10
  %9 = fmul float %12, %13
  br label %exit

loop-check:                                       ; preds = %header, %body
  %10 = phi float [ 0.000000e+00, %header ], [ %7, %body ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body ]
  %next_iter = add i32 %iter, 1
  %11 = icmp slt i32 %iter, %n
  %12 = fsub float %10, %10
  %13 = fadd float %12, %12
  br i1 %11, label %body, label %loop_exit
}
*/

/* Graph first_graph( */
/* {{Instruction::param, "%n"},                   // 0 */
/*  {Instruction::param, "%a"},                   // 1 */
/*  {Instruction::param, "%b"},                   // 2 */
/*  {Instruction::fsub,  "%0",         {13, 18}}, // 3 */
/*  {Instruction::fmul,  "%1",         { 3,  3}}, // 4 */
/*  {Instruction::ret,   "",           {14}},     // 5 */
/*  {Instruction::gep,   "%2",         { 1, 15}}, // 6 */
/*  {Instruction::load,  "%3",         { 6}},     // 7 */
/*  {Instruction::gep,   "%4",         { 2, 15}}, // 8 */
/*  {Instruction::load,  "%5",         { 8}},     // 9 */
/*  {Instruction::fmul,  "%6",         { 7,  9}}, //10 */
/*  {Instruction::fadd,  "%7",         {14, 10}}, //11 */
/*  {Instruction::fsub,  "%8",         {18, 14}}, //12 */
/*  {Instruction::fmul,  "%9",         {18, 19}}, //13 */
/*  {Instruction::phi,   "%10",        {21, 11}}, //14 */
/*  {Instruction::phi,   "%iter",      {16, 22}}, //15   this is swapped around
 */
/*  {Instruction::add,   "%next_iter", {15, 23}}, //16 */
/*  {Instruction::icmp,  "%11",        { 0}},     //17 */
/*  {Instruction::fsub,  "%12",        {14, 14}}, //18 */
/*  {Instruction::fadd,  "%13",        {18, 18}}, //19 */
/*  {Instruction::br,    "",           {17}},     //20 */
/*  {Instruction::cnst,  "0.0"},                  //21 */
/*  {Instruction::cnst,  "0"},                    //22 */
/*  {Instruction::cnst,  "1"}});                  //23 */

/*
; ModuleID = 'dot.ll'
source_filename = "dot.ll"

; Function Attrs: norecurse nounwind readonly
define float @dot(i32 %n, float* nocapture readonly %a, float* nocapture
readonly %b) local_unnamed_addr #0 { entry: %0 = icmp sgt i32 %n, 0 br i1 %0,
label %body.preheader, label %loop_exit

body.preheader:                                   ; preds = %entry
  br label %body

body:                                             ; preds = %body.preheader,
%body %iter1 = phi i32 [ %next_iter, %body ], [ 0, %body.preheader ] %1 = phi
float [ %8, %body ], [ 0.000000e+00, %body.preheader ] %next_iter = add nuw nsw
i32 %iter1, 1 %2 = zext i32 %iter1 to i64 %3 = getelementptr float, float* %a,
i64 %2 %4 = load float, float* %3, align 4 %5 = getelementptr float, float* %b,
i64 %2 %6 = load float, float* %5, align 4 %7 = fmul float %4, %6 %8 = fadd
float %1, %7 %9 = icmp slt i32 %next_iter, %n br i1 %9, label %body, label
%loop_exit

loop_exit:                                        ; preds = %body, %entry
  %.lcssa = phi float [ 0.000000e+00, %entry ], [ %8, %body ]
  ret float %.lcssa
}

attributes #0 = { norecurse nounwind readonly }

*/

/* Graph second_graph( */
/* {{Instruction::param, "%n"},                   // 0 - 24 */
/*  {Instruction::param, "%a"},                   // 1 - 25 */
/*  {Instruction::param, "%b"},                   // 2 - 26 */
/*  {Instruction::icmp,  "%0",         { 0, 19}}, // 3 - 27 */
/*  {Instruction::br,    "",           { 3}},     // 4 - 28 */
/*  {Instruction::phi,   "%iter1",     { 7, 19}}, // 5 - 29 */
/*  {Instruction::phi,   "%1",         {20, 14}}, // 6 - 30    this is swapped
 * around */
/*  {Instruction::add,   "%next_iter", { 5, 21}}, // 7 - 31 */
/*  {Instruction::zext,  "%2",         { 5}},     // 8 - 32 */
/*  {Instruction::gep,   "%3",         { 1, 5}},  // 9 - 33    this is
 * manipulated */
/*  {Instruction::load,  "%4",         { 9}},     //10 - 34 */
/*  {Instruction::gep,   "%5",         { 2, 5}},  //11 - 35    this is
 * manipulated */
/*  {Instruction::load,  "%6",         {11}},     //12 - 36 */
/*  {Instruction::fmul,  "%7",         {10, 12}}, //13 - 37 */
/*  {Instruction::fadd,  "%8",         { 6, 13}}, //14 - 38 */
/*  {Instruction::icmp,  "%9",         { 7,  0}}, //15 - 39 */
/*  {Instruction::br,    "",           {15}},     //16 - 40 */
/*  {Instruction::phi,   "%.lcssa",    {20, 14}}, //17 - 41 */
/*  {Instruction::ret,   "",           {17}},     //18 - 42 */
/*  {Instruction::cnst,  "0"},                    //19 - 43 */
/*  {Instruction::cnst,  "0.0"},                  //20 - 44 */
/*  {Instruction::cnst,  "1"}});                  //21 - 45 */
