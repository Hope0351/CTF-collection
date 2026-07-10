# Reverse Engineering Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

The RE tooling stack is dominated by Ghidra (free, NSA), IDA Pro (commercial, industry standard), Binary Ninja (commercial, modern), and angr (Python, symbolic execution). For dynamic analysis, gdb with gef and Frida (for instrumentation) are the standards.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [Ghidra](https://ghidra-sre.org/) | Java | NSA's free reverse-engineering suite. The dominant free tool. Decompiler is excellent. Project files are shareable. |
| 2 | [IDA Pro](https://hex-rays.com/ida-pro/) | C++ | Industry-standard commercial RE tool. Hex-Rays decompiler is the best in class. Free version available with limited features. |
| 3 | [Binary Ninja](https://binary.ninja/) | C++ | Modern commercial RE tool. Excellent API for scripting; growing community. |
| 4 | [angr](https://angr.io/) | Python | Symbolic execution framework. Powerful for solving RE challenges automatically; steep learning curve. |
| 5 | [radare2](https://www.radare.org/) | C | Free, command-line RE framework. Steeper learning curve than Ghidra but more scriptable. |
| 6 | [Frida](https://frida.re/) | JavaScript | Dynamic instrumentation framework. Dominates mobile RE; also useful for desktop. |
| 7 | [x64dbg](https://x64dbg.com) | C++ | Windows-native debugger. Alternative to OllyDbg (legacy). |
| 8 | [Cutter](https://cutter.re/) | C++ | GUI frontend for radare2. Easier onboarding than raw r2. |
| 9 | [binwalk](../40-tooling/archives/forensics-tools/binwalk) | Python | Firmware analysis tool. Identifies and extracts embedded files. |

## Quick Installation

```bash
# Ghidra (free reverse engineering suite by NSA)
# Download from https://ghidra-sre.org/
# Requires Java 17+: sudo apt install openjdk-17-jdk

# angr (symbolic execution engine)
pip install angr

# radare2 (CLI reverse engineering framework)
sudo apt install radare2

# Binary Ninja (commercial alternative, free API)
# Download from https://binary.ninja/
```

## See Also

- [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) — condensed cheat sheet across all categories
- [`40-tooling/README.md`](README.md) — full tool index
