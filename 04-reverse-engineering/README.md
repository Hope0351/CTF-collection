# Reverse Engineering

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Static and dynamic analysis of native binaries, obfuscated scripts, custom virtual machines, and increasingly LLVM IR, WebAssembly, and exotic architectures. The tooling stack is dominated by Ghidra (free), IDA Pro (commercial), Binary Ninja, angr (symbolic execution), and gdb-gef.

## 🔬 Sub-Topic Deep Dive

The Reverse Engineering category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Native binaries (x86/x64)

stripped binaries, custom packing, anti-debugging.

*No directly-matching resources in this collection — consult the broader category list above.*

### ARM / MIPS / RISC-V

cross-architecture RE; common in IoT.

Top resources for this sub-topic:

- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - the collection](../30-archetypes/archives/awesome-lists/awesome-ctf) — 📚 Repository
- [blockthreat/blocksec-ctfs - the collection](../30-archetypes/archives/awesome-lists/blocksec-ctfs) — 📚 Repository
- [Hack The Box Writeups - The Ultimate HTB Resource - the collection](../20-events/archives/hackthebox/htb-writeups) — 📚 Repository
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository
- [xtiankisutsa/awesome-mobile-CTF](../30-archetypes/archives/awesome-lists/awesome-mobile-ctf) — 📚 Repository

### Custom VMs

bytecode-based challenge binaries with custom instruction sets.

Top resources for this sub-topic:

- [gijsh/rhme2_writeups: Writeups for the RHME2 CTF - the collection](../10-hardware-iot/archives/rhme2-writeups) — 📚 Repository
- [BarakBinyamin/ctf: Some embedded network attacks  - the collection](../30-archetypes/archives/personal-collections/ctf-BarakBinyamin) — 📚 Repository

### Obfuscated scripts

PyArmor, py2exe, Lua bytecode, JavaScript obfuscation.

Top resources for this sub-topic:

- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository
- david942j/ctf-writeups: Collection of scripts and writeups — 📚 Repository
- [kyndrawynne/pwnscripts - the collection](../40-tooling/archives/pwn-tools/pwnscripts) — 📚 Repository

### LLVM IR / WebAssembly

modern obfuscation targets.

Top resources for this sub-topic:

- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - the collection](../30-archetypes/archives/awesome-lists/awesome-ctf) — 📚 Repository
- [blockthreat/blocksec-ctfs - the collection](../30-archetypes/archives/awesome-lists/blocksec-ctfs) — 📚 Repository
- [Hack The Box Writeups - The Ultimate HTB Resource - the collection](../20-events/archives/hackthebox/htb-writeups) — 📚 Repository
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository
- [xtiankisutsa/awesome-mobile-CTF](../30-archetypes/archives/awesome-lists/awesome-mobile-ctf) — 📚 Repository

### Anti-reverse engineering

anti-debug, anti-VM, anti-disassembly tricks.

Top resources for this sub-topic:

- [Kasimir123/CTFWriteUps](../30-archetypes/archives/personal-collections/CTFWriteUps-Kasimir123) - Collection of CTF Writeups - 📚 Repository
- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [1GN1tE/CTF_Writeups](../30-archetypes/archives/personal-collections/CTF_Writeups-1GN1tE) - Writeups of some Reverse Engineering - 📚 Repository
- [docfate111/binary_exploitation: CTF/hacking challenge  - the collection](../01-pwn/archives/binary_exploitation) — 📚 Repository

## 🎯 Suggested Learning Order

If you're new to reverse engineering, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [pwn.college RE module](https://pwn.college/) — then reverse-engineer 5–10 [CrackMe challenges](https://crackmes.one/).

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
