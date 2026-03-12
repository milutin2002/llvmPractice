# llvmFunctionName

This repo demonstrates pass which prints the all recursive functions

```
mkdir build
cd build
cmake ..
cmake --build .
clang -O1 -S -emit-llvm -o main.ll ../main.c
opt -load-pass-plugin ../pass.so --passes="func-names" ./main.ll

```