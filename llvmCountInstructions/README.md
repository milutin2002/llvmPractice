
## `llvmCountInstructions/README.md`

# llvmCountInstructions — Instruction Mix Metrics Pass (`inst-count`)

- Counts LLVM IR instruction opcodes **per function** and prints a small “instruction mix” histogram.

## What this pass does

For each `Function` in the input IR:
- iterates `BasicBlock` → `Instruction`
- counts `Instruction::getOpcodeName()` occurrences
- prints results using `llvm::outs()`

**Concept mapping:** instruction analysis + metrics.

> Note: the implementation uses an unordered map, so output ordering can vary.

## Build & run

### Prerequisites
- LLVM + Clang installed (`clang`, `opt`, headers + LLVMConfig.cmake)
- CMake 3.20+, C++17 compiler

### Build
```bash
cmake -S . -B build
cmake --build build -j
