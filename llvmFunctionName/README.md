# llvmFunctionName — Direct Call-Site Discovery Pass (`func-names`)

- Prints **direct callees** found inside each function by walking call instructions.
- A practical starting point for call graph construction and interprocedural analysis.

## What this pass does

For each `Function`:
- iterates over instructions
- `dyn_cast<CallInst>` to detect calls
- uses `getCalledFunction()` and prints `Found function <callee> inside <caller>`

**Concept mapping:** call-site inspection → call graph edges (interprocedural analysis starter).

> Limitation: `getCalledFunction()` is only available for **direct calls**; indirect calls are skipped.

## Build & run

### Build
```bash
cmake -S . -B build
cmake --build build -j
