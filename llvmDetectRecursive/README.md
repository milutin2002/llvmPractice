# llvmDetectRecursive

An LLVM pass plugin that detects direct recursion — functions that call themselves.

## What it does

For each function it walks every `call` instruction and checks whether the callee name matches the caller name. If a match is found it prints `Recursive function detected <name>`.

Example output for `main.c` (which contains `sum` and `fakt`, both recursive):
```
Recursive function detected sum
Recursive function detected fakt
```

> Only **direct** recursion is detected. Mutual recursion (A calls B, B calls A) is not caught because that requires a full call graph / SCC analysis.

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
