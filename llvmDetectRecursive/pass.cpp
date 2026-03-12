#include "llvm/IR/Analysis.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <iostream>
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



struct RecursiveDetectPass:PassInfoMixin<RecursiveDetectPass>{
    PreservedAnalyses run(Function&f,FunctionAnalysisManager &){
        bool det=false;
        for(BasicBlock &bb:f){
            for(Instruction &i:bb){
                CallInst* call=dyn_cast<CallInst>(&i);
                if(call){
                    Function *f1=call->getCalledFunction();
                    if(f1 && f1->getName().compare(f.getName())==0){
                            det=true;
                    }
                }
            }
        }
        if(det){
            std::cout<<"Recursive function detected "<< f.getName().str() <<std::endl;
        }
        return PreservedAnalyses::all();
    }
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo(){
    return {
        LLVM_PLUGIN_API_VERSION,
        "RecursiveDetectPass",
        LLVM_VERSION_STRING,
        [](PassBuilder &pB){
            pB.registerPipelineParsingCallback([](StringRef name,FunctionPassManager &fPM,...){
                if(name=="func-names"){
                    fPM.addPass(RecursiveDetectPass());
                    return true;
                }
                return false;
            });
        }
    };
}