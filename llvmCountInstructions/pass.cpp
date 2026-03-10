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
#include <unordered_map>

using namespace llvm;
using namespace std;


typedef struct Stats{
    string name;
    unordered_map<string, int>map;
}Stats;

struct InstCountPass:PassInfoMixin<InstCountPass>{
    PreservedAnalyses run(Function&f,FunctionAnalysisManager &){
        errs()<<"Function "<<f.getName()<<"\n";
        Stats s;
        s.name=f.getName();
        for(BasicBlock &bb:f){
            for(Instruction &i:bb){
                s.map[i.getOpcodeName()]++;
            }
        }
        for(auto it=s.map.begin();it!=s.map.end();it++){
            errs()<<it->first<<" "<<it->second<<"\n";
        }
        return PreservedAnalyses::all();
    }
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo(){
    return {
        LLVM_PLUGIN_API_VERSION,
        "InstCountPass",
        LLVM_VERSION_STRING,
        [](PassBuilder &pB){
            pB.registerPipelineParsingCallback([](StringRef name,FunctionPassManager &fPM,...){
                if(name=="inst-count"){
                    fPM.addPass(InstCountPass());
                    return true;
                }
                return false;
            });
        }
    };
}