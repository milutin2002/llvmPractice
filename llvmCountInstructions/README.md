# llvmCountInstructions

An LLVM pass plugin that counts IR instruction opcodes per function and prints a histogram.

## What it does

For each function it iterates over every instruction, tallies occurrences of each opcode name (via `getOpcodeName()`), and prints the counts.

Example output for `main.c`:
```
Function add
add 1
ret 1
Function greet
call 1
ret 1
Function main
call 2
ret 1
```

> Output order within a function can vary because an unordered map is used internally.

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
opt -load-pass-plugin ./build/pass.so -passes="inst-count" -disable-output main.ll
```

The pass is registered under the name `inst-count`.
