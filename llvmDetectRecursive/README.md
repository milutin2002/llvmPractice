# llvmDetectRecursive — Direct Recursion Detector Pass (currently `func-names`)

- Detects **direct recursion**: a function contains a direct call to itself.
- Useful as an “early warning” analysis for compilation targets or runtimes that restrict recursion.

## What this pass does

For each `Function`:
- walks instructions
- checks `CallInst` + `getCalledFunction()`
- compares callee name to caller name
- prints `Recursive function detected <name>` to stdout

**Concept mapping:** call graph property check (direct recursion).

Limitations:
- Detects **direct** recursion only (not mutual recursion / SCCs).
- Prints via `std::cout` (while other passes print via `llvm::outs()`).

## Build & run

### Build
```bash
cmake -S . -B build
cmake --build build -j
