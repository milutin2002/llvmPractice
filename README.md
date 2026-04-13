# llvmPractice — LLVM Analysis Pass Plugins

- **Multiple LLVM analysis passes** implemented as **out-of-tree pass plugins** (one subfolder per pass).
- Demonstrates **compiler infrastructure fundamentals**: LLVM IR traversal and call-site properties.
- Designed to be **reproducible and demoable**: CMake builds + `clang -S -emit-llvm` + `opt -load-pass-plugin` pipelines.

> Repo goal: build small, readable analysis passes that produce “compiler telemetry” and can be extended into tooling.

---

## What this repository contains

This repository is organized as **one pass per folder**. Each folder builds a standalone LLVM **pass plugin** (shared library) exposing a named pipeline pass that you can run via `opt`.

Current detected pass folders:
- `llvmCountInstructions/` — instruction opcode histogram per function (`inst-count`)
- `llvmFunctionName/` — direct call-site discovery (`func-names`)
- `llvmDetectRecursive/` — direct recursion detection (**currently also** `func-names`; recommended rename)

> **Unspecified / unknown future passes:** If you add more subfolders, follow the template at the bottom of this README.

---

## Why analysis passes matter (and why this maps to Tenstorrent)

LLVM **analysis passes** compute properties of IR without changing semantics. In practice, analysis is the foundation for:
- **Compiler infrastructure:** analyses enable or guide optimizations and correctness checks.
- **Hardware-aware compilation:** analyses feed cost models and constraints (e.g., recursion constraints, call patterns, instruction mixes).



Primary references:
- LLVM new pass manager (`opt -passes`, nesting, `-load-pass-plugin`):
  https://llvm.org/docs/NewPassManager.html
- Writing a new-PM LLVM pass (plugin registration patterns):
  https://llvm.org/docs/WritingAnLLVMNewPMPass.html
- Clang IR emission example (`clang file.c -S -emit-llvm`):
  https://clang.llvm.org/get_started.html

---

## Quick start (download → build → run)

### Prerequisites

You need an LLVM installation that provides:
- `clang`
- `opt`
- LLVM headers + CMake config (`LLVMConfig.cmake`)

> Practical note: out-of-tree plugins generally work best when the **LLVM used to build the plugin matches the `opt` you run**.

### Build any pass plugin (per folder)

Each pass folder is self-contained. Example for `llvmCountInstructions`:

```bash
cd llvmCountInstructions
cmake -S . -B build
cmake --build build -j
# Output artifact (Linux): build/pass.so
