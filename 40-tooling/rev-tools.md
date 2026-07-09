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
# Most tools are pip-installable
pip install pwntools angr ropper pyelftools

# Or apt-installable on Debian/Ubuntu
sudo apt install gdb gdb-gef ghidra wireshark tshark binwalk foremost exiftool steghide

# Foundry (blockchain)
curl -L https://foundry.paradigm.xyz | bash
foundryup

# Frida (mobile)
pip install frida-tools
```

## See Also

- [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) — condensed cheat sheet across all categories
- [`40-tooling/README.md`](README.md) — full tool index
