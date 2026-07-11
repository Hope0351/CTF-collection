# Security Tools Reference

This file consolidates the security tools referenced in my CTF learning
path and cheat sheet. Instead of linking out to each tool's site every
time, I keep installation and usage notes here so the collection stays
self-contained.

---

## pwntools

**What it is.** A CTF framework and exploit-development library for
Python, designed for rapid prototyping. It is the single most-used tool
in any pwn CTF.

**Installation.**
```bash
pip install pwntools
```

**What it gives me.**
- `from pwn import *` — pulls in the entire API.
- `remote(host, port)` / `process(binary)` — connection helpers.
- `p32()` / `p64()` / `u32()` / `u64()` — pack/unpack integers.
- `cyclic()` / `cyclic_find()` — pattern-based offset finding.
- `ROP(binary)` — ROP chain builder.
- `ELF(binary)` — section/symbol inspection.
- `context.arch` / `context.os` — architecture configuration.
- `asm()` / `disasm()` — assembly/disassembly.
- `shellcraft` — pre-built shellcode snippets.

**Command-line tools included.**
- `pwn checksec` — print security mitigations of a binary.
- `pwn cyclic` — generate De Bruijn patterns.
- `pwn asm` / `pwn disasm` — assemble/disassemble.
- `pwn libcdb` — search glibc by build ID.

**Docs reference.** The official documentation is extensive; I keep a
local cheatsheet in `tools-cheatsheet.md` for the patterns I use most.

---

## Ghidra

**What it is.** A software reverse-engineering suite developed by the
NSA and open-sourced in 2019. It includes a disassembler, a decompiler
(for x86, x86_64, ARM, MIPS, and more), and a scriptable plugin system
using Java or Python (via Jython).

**Installation.**
```bash
# Requires JDK 17+
sudo apt install openjdk-17-jdk
# Download the latest release zip from the GitHub releases page
unzip ghidra-X.Y.Z_PUBLIC.zip
cd ghidra-X.Y.Z_PUBLIC
./ghidraRun
```

**What I use it for.**
- Decompiling C binaries to readable C-like pseudocode.
- Renaming functions and variables to match my understanding.
- Cross-referencing (XREF) — find all callers of a function.
- Searching for strings, constants, and patterns.
- Writing scripts to automate repetitive analysis.

**Tips for myself.**
- Always run "Auto Analyze" with default options after importing a
  binary. The analysis takes a minute but unlocks all the cross-refs.
- Use `Ctrl+E` to edit a function signature — fixing the signature
  makes the decompiler output dramatically better.
- Right-click → "Retype Variable" liberally. Bad types are the #1 cause
  of unreadable decompiler output.

---

## Burp Suite Community Edition

**What it is.** A web-application security testing proxy by PortSwigger.
The Community Edition is free and includes the core proxy, Repeater, and
Intruder (rate-limited). It is the de-facto standard tool for web CTF
challenges.

**Installation.**
```bash
# Download the installer from portswigger.net
# Or on Kali/Parrot:
sudo apt install burpsuite
```

**What I use it for.**
- **Proxy** — intercept and modify HTTP requests/responses in real time.
- **Repeater** — manually modify and resend individual requests. This is
  where I spend 90% of my web-CTF time.
- **Intruder** — automate fuzzing of a parameter (Community Edition is
  rate-limited but still usable).
- **Param Miner** extension — discover hidden parameters and headers.

**Setup.**
1. Configure the browser proxy to `127.0.0.1:8080`.
2. Install the PortSwigger CA certificate so HTTPS traffic decrypts.
3. Browse to the target; requests appear in the HTTP History tab.

**Tips for myself.**
- Learn the keyboard shortcuts in Repeater: `Ctrl+R` to send a request,
  `Ctrl+Space` to send it.
- The "Comparer" tool is underrated — use it to diff two responses when
  blind-injecting.

---

## Wireshark

**What it is.** The world's most widely used network protocol analyzer.
It lets me capture and interactively browse packet traffic, with
dissectors for hundreds of protocols.

**Installation.**
```bash
sudo apt install wireshark tshark
```

**What I use it for.**
- Inspecting `.pcap` files from forensics challenges.
- Extracting files transferred over HTTP/FTP/SMB.
- Decrypting TLS traffic when I have the session key log.
- Following TCP streams to reconstruct conversations.

**Command-line sibling — tshark.**
```bash
# List protocols in a capture
tshark -r capture.pcap -Y "http" -T fields -e http.request.uri

# Follow a TCP stream as ASCII
tshark -r capture.pcap -Y "tcp.stream eq 0" -z "follow,tcp,ascii,0"

# Extract FTP commands
tshark -r capture.pcap -Y "ftp" -T fields -e ftp.request.command -e ftp.request.arg
```

**Tips for myself.**
- "File → Export Objects → HTTP" is the fastest way to pull files out
  of a capture.
- For TLS decryption, set `SSLKEYLOGFILE` environment variable on the
  client, then point Wireshark at the key log in Preferences → Protocols
  → TLS.

---

## Volatility

**What it is.** A memory-forensics framework. Given a RAM dump, it can
extract processes, network connections, registry hives, cached files,
passwords, and more. Versions 2 and 3 differ significantly; Volatility 3
is the current version.

**Installation (Volatility 3).**
```bash
pip install volatility3
```
The pip version is current enough for CTF work. For symbol tables that the
pip release doesn't ship, I download the symbol package for the target OS
from the Volatility Foundation's symbol-table repository and place it in
`volatility3/symbols/`.

**Common commands (Volatility 3 syntax).**
```bash
# Identify the OS profile
vol3 -f memory.dmp windows.info

# List processes
vol3 -f memory.dmp windows.pslist
vol3 -f memory.dmp windows.pstree

# Dump a process's memory
vol3 -f memory.dmp windows.memdump --pid 1234 --dump .

# List network connections
vol3 -f memory.dmp windows.netstat

# Dump NTLM hashes
vol3 -f memory.dmp windows.hashdump

# Recover command history
vol3 -f memory.dmp windows.cmdscan
```

**Tips for myself.**
- Always start with `windows.info` (or `linux.info` / `mac.info`) to
  confirm the OS before running other plugins.
- The Volatility 2 syntax (e.g., `--profile=Win7SP1x64`) does not work
  in Volatility 3 — profiles are auto-detected.

---

## angr

**What it is.** A Python framework for symbolic execution and binary
analysis. It is invaluable for solving "find the input that reaches this
address" challenges, which come up constantly in reverse engineering
CTFs.

**Installation.**
```bash
pip install angr
```

**Typical usage.**
```python
import angr
proj = angr.Project('./challenge', auto_load_libs=False)
state = proj.factory.entry_state()
simgr = proj.factory.simulation_manager(state)
# Find the "win" address, avoid the "lose" address
simgr.explore(find=0x400a30, avoid=0x400a50)
if simgr.found:
    found = simgr.found[0]
    print(found.posix.dumps(0))  # stdin that reaches the win path
```

**Tips for myself.**
- Set `auto_load_libs=False` to avoid spending hours symbolically
  executing libc.
- angr is slow on large binaries. Use it after I've narrowed down the
  relevant function via Ghidra.
- The `explore(find=lambda s: b'flag' in s.posix.dumps(1))` pattern is
  convenient but can hang — prefer concrete addresses when known.

---

## SageMath

**What it is.** A free open-source mathematics software system, bundling
hundreds of specialised libraries under a unified Python interface. For
CTF purposes, it is the tool for lattice-based cryptanalysis, elliptic
curve math, and integer factorisation that `sympy` cannot handle.

**Installation.**
```bash
# On Linux, the easiest is the official binary:
# Download from sagemath.org, or:
sudo apt install sagemath
# Or via conda:
conda install -c conda-forge sage
```

**What I use it for.**
- Factoring RSA moduli (small ones, or ones with special structure).
- Computing discrete logarithms on elliptic curves.
- Lattice reduction (LLL, BKZ) for hidden-number-problem challenges.
- Solving systems of modular equations.

**Example — RSA decrypt given p, q.**
```python
from sage.all import *
n = 0x...
e = 65537
c = 0x...
p, q = ..., ...
phi = (p-1)*(q-1)
d = inverse_mod(e, phi)
m = power_mod(c, d, n)
print(bytes.fromhex(hex(m)[2:]))
```

**Tips for myself.**
- SageMath's `factor()` is much smarter than trial division — it uses
  PARI under the hood. But for >200-bit moduli it will still be slow.
- For lattice challenges, the `matrix.LLL()` method is the workhorse.
- Keep a SageMath kernel in Jupyter for interactive exploration.

---

## Source attribution

The descriptions above were written in my own words based on the
official documentation and landing pages of each tool, downloaded on
2026-07-11 for reference. The tools themselves are not reproduced here —
only my notes about them. Tool names are trademarks of their respective
owners.
