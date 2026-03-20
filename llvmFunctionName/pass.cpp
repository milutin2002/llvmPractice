#include "llvm/IR/Analysis.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <llvm/ADT/StringRef.h>
#include <llvm/Config/llvm-config.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/Compiler.h>
#include <llvm/Support/raw_ostream.h>
#include <unordered_set>

using namespace llvm;



struct FunctionNamePass:PassInfoMixin<FunctionNamePass>{
    PreservedAnalyses run(Function&f,FunctionAnalysisManager &){
        outs()<<"Function "<<f.getName()<<"\n";
        for(BasicBlock &bb:f){
            for(Instruction &i:bb){
                CallInst* call=dyn_cast<CallInst>(&i);
                if(call){
                    Function *f1=call->getCalledFunction();
                    if(f1){
                            outs()<<"Found function "<<f1->getName().str()<<" inside "<<f.getName().str()<<"\n";
                    }
                }
            }
        }
        return PreservedAnalyses::all();
    }
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo(){
    return {
        LLVM_PLUGIN_API_VERSION,
        "FunctionNamePass",
        LLVM_VERSION_STRING,
        [](PassBuilder &pB){
            pB.registerPipelineParsingCallback([](StringRef name,FunctionPassManager &fPM,...){
                if(name=="func-names"){
                    fPM.addPass(FunctionNamePass());
                    return true;
                }
                return false;
            });
        }
    };
}