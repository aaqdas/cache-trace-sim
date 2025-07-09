# Memtrace & Cache Simulator Tool

This toolchain allows you to:

1. Build a application executable.
2. Run it under Valgrind Lackey to generate a memory access trace.
3. Convert the Valgrind trace into a micro-op style trace.
4. Run a trace-driven cache simulator on the formatted trace.

---

## Prerequisites

* GCC compiler (`gcc`)
* Valgrind (with Lackey tool)
* Python 3 (for trace conversion)
* Python 2 (for cache simulator)
* `make` utility
* `git`

---

## Setup

When cloning the repository, make sure to pull **all nested repositories/submodules recursively**:

```bash
git clone --recursive https://github.com/aaqdas/cache-trace-sim
```

If you already cloned without `--recursive`, update submodules with:

```bash
git submodule update --init --recursive
```

---

## How to Use

### 1. Build the executable

```bash
make build APP=<app-name>
```

This compiles `memtrace.c` into `memtrace.out` with default `-O0` flags.

---

### 2. Generate the memory trace

```bash
make trace APP=<app-name>
```

Runs Valgrind Lackey on the executable and converts the trace.

---

### 3. Run the cache simulator

```bash
make run APP=<app-name>
```

Runs the Python 2 cache simulator on the formatted trace.

---

## Makefile Targets Summary

| Target  | Description                                      |
| ------- | ------------------------------------------------ |
| `build` | Compile the memtrace executable (`memtrace.out`) |
| `trace` | Run Valgrind Lackey and convert trace files      |
| `run`   | Run the cache simulator on the formatted trace   |

---