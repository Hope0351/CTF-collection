# Reverse Engineering

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Static and dynamic analysis of native binaries, obfuscated scripts, custom virtual machines, and increasingly LLVM IR, WebAssembly, and exotic architectures. The tooling stack is dominated by Ghidra (free), IDA Pro (commercial), Binary Ninja, angr (symbolic execution), and gdb-gef.

This category contains **64 curated sources** from across the CTF ecosystem: 52 internal archives, 9 Medium articles, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 3 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Difficulty |
|---:|---|---|
| 1 | [Nahamcon CTF 2024 Reverse Engineering Challenges](https://medium.com/@0xMr_Robot/nahamcon-ctf-2024-reverse-engineering-challenges-b397296721c1) | — |
| 2 | [Writeup - ComCyber Recrutement CTF](https://blog.root-me.org/posts/writeup_comcyber) | — |
| 3 | [PlaidCTF 2023 Writeups](https://siunam321.github.io/ctf/PlaidCTF-2023) | — |
| 4 | [ICTF 2025 Writeup](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | — |
| 5 | [Recap: HITCON CTF 2024 Rank: 108/1699](https://medium.com/@harryfyx/recap-hitcon-ctf-2024-rank-108-1699-2e2af0b10f4f) | — |
| 6 | [CyberSpace CTF 2024 Reverse Engineering Challenges](https://medium.com/@ELJoOker/cyberspace-ctf-2024-reverse-engineering-challenges-4226b9055547) | — |
| 7 | [Code X Sport Jung'23 CTF Reverse Engineering Write-up](https://sarimraza.medium.com/code-x-sport-jung23-ctf-reverse-engineering-write-up-d5997c9065a4) | — |
| 8 | [CTF Writeup | RanDom BUG | Reverse Engineering](https://me-ankeet.medium.com/ctf-writeup-random-bug-reverse-engineering-f17ebba1c5b3) | — |
| 9 | [Reverse Engineering CTF Writeup: My Favorite Fruit — DreamHack](https://medium.com/@talal.ak/reverse-engineering-ctf-writeup-my-favorite-fruit-dreamhack-5b2cc2a961d0) | — |
| 10 | [How I Became the "Reverse Guy" in My CTF Team](https://rustybladez.medium.com/how-i-became-the-reverse-guy-in-my-ctf-team-c6fc2cef1512) | — |
| 11 | [CSAW CTF 2023 Writeup](https://tripoloski1337.github.io/ctf/pwn/uaf/heap/2023/09/18/csawctf2023-writeup.html) | — |
| 12 | [ICMTC CTF 2024 Reverse Engineering Challenges Write Up](https://medium.com/@ELJoOker/icmtc-ctf-reverse-engineering-and-forensics-challenges-write-up-b3c0167ef171) | — |

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
