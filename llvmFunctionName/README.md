# llvmFunctionName

This repo demonstrates pass which prints the name of function inside main.c and then it iterates over all blocks and prints the name of functions called inside that block

```
mkdir build
cd build
cmake ..
cmake --build .
clang -O1 -S -emit-llvm -o main.ll ../main.c
opt -load-pass-plugin ../pass.so --passes="func-names" ./main.ll

```
