# llvmFunctionName

An LLVM pass plugin that prints each function's name and lists every direct callee it calls.

## What it does

For each function in the module it prints the function name, then for every `call` instruction inside it prints `Found function <callee> inside <caller>`.

Example output for `main.c`:
```
Function add
Function greet
Function main
Found function printf inside greet
Found function add inside main
```

> Only direct calls are detected. Indirect calls through function pointers are skipped because `getCalledFunction()` returns null for those.

## Prerequisites

- LLVM + Clang installed (`clang`, `opt`, headers, `LLVMConfig.cmake`)
- CMake 3.20+
- C++17 compiler

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

This produces `pass.so` in `build/`.

## Run

**1. Compile the target to LLVM IR:**
```bash
clang -O1 -emit-llvm -S main.c -o main.ll
```

**2. Run the pass with `opt`:**
```bash
opt -load-pass-plugin ./build/pass.so -passes="func-names" -disable-output main.ll
```

The pass is registered under the name `func-names`.
