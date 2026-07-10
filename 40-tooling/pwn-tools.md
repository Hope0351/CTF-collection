# Pwn Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

Binary exploitation requires a deep tooling stack. The dominant tools are pwntools (Python library for exploit development), ROPgadget/ropper (ROP chain construction), one_gadget (libc magic-gadget finder), gdb with gef or pwndbg (debugger frontend), and checksec (mitigation checker).

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [pwntools](https://docs.pwntools.com/) | Python | The de facto standard library for CTF exploit development. Provides remote/process abstractions, packed integers, ROP chain builders, shellcraft, and tube I/O. |
| 2 | [ROPgadget](../40-tooling/archives/pwn-tools/ROPgadget) | Python | Finds ROP gadgets in ELF/PE/Mach-O binaries. Can automatically generate ROP chains. |
| 3 | [ropper](../40-tooling/archives/pwn-tools/Ropper) | Python | Alternative to ROPgadget. Faster on large binaries; supports semantic gadget search. |
| 4 | one_gadget | Ruby | Finds 'one-gadget' addresses in libc — single gadgets that spawn a shell when register/stack constraints are satisfied. |
| 5 | [gdb-gef](../40-tooling/archives/pwn-tools/gef) | Python | GDB Enhanced Features. The dominant GDB frontend for CTF. Provides checksec, heap analysis, telescope, pattern_create/offset, and more. |
| 6 | [pwndbg](../40-tooling/archives/pwn-tools/pwndbg) | Python | Alternative GDB frontend. Similar feature set to gef; choice is largely aesthetic. |
| 7 | [checksec](../40-tooling/archives/pwn-tools/checksec.sh) | Bash | Checks binary security mitigations: NX, PIE, RELRO, stack canary, FORTIFY. |
| 8 | LibcSearcher | Python | Identifies libc version from leaked function addresses. Essential for ret2libc attacks. |
| 9 | [Pwntools-README](../40-tooling/archives/pwn-tools/pwntools) | Python | Pwntools internal archive — install via `pip install pwntools`. |

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
