# Reverse Engineering

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Static and dynamic analysis of native binaries, obfuscated scripts, custom virtual machines, and increasingly LLVM IR, WebAssembly, and exotic architectures. The tooling stack is dominated by Ghidra (free), IDA Pro (commercial), Binary Ninja, angr (symbolic execution), and gdb-gef.

This category contains **64 curated sources** from across the CTF ecosystem: 52 internal archives, 9 Medium articles, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 3 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [Nahamcon CTF 2024 Reverse Engineering Challenges | by Mr Robot](https://medium.com/@0xMr_Robot/nahamcon-ctf-2024-reverse-engineering-challenges-b397296721c1) | ✍️ Medium | 2024–2024 | It pleases me to get into Nahamcon CTF 2024 and solve 6 of 10 reverse challenges in this competition and this is my wri… |
| 2 | [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) | 📝 Blog | n/a | Writeup - ComCyber Recrutement CTF · Step 1 - Network · Step 2 - Web · Step 3 - Forensic · Step 4 - Steganography · Ste… |
| 3 | [PlaidCTF 2023 Writeups - siunam's Website](https://siunam321.github.io/ctf/PlaidCTF-2023) | 📝 Blog | 2023–2023 | The Plaid Flag is the 2023 edition of PlaidCTF, an annual capture the flag competition run by PPP. Categories: web; rev… |
| 4 | [ICTF 2025 Writeup - Medium](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | ✍️ Medium | 2025–2025 | It was an exciting competition with a diverse range of challenges spanning forensics, steganography, web exploitation, … |
| 5 | [Recap: HITCON ctf 2024 Rank: 108/1699 | by hhhkb | Medium](https://medium.com/@harryfyx/recap-hitcon-ctf-2024-rank-108-1699-2e2af0b10f4f) | ✍️ Medium | 2024–2024 | Took me about 5 hours reading ClamAV documentations, reading another ClamAV CTF writeup and source code, and reading th… |
| 6 | [CyberSpace CTF 2024 Reverse Engineering Challenges - Medium](https://medium.com/@ELJoOker/cyberspace-ctf-2024-reverse-engineering-challenges-4226b9055547) | ✍️ Medium | 2024–2024 | This write-up is for some of the Reverse Engineering and Forensics challenges that I've solved in the NahamCon CTF… A c… |
| 7 | [Code X Sport Jung'23 CTF Reverse Engineering Write-up](https://sarimraza.medium.com/code-x-sport-jung23-ctf-reverse-engineering-write-up-d5997c9065a4) | ✍️ Medium | n/a | Hello everyone, I am back with another write-up covering solutions to all 4 Reverse Engineering challenges of Code X Sp… |
| 8 | [CTF Writeup | RanDom BUG | Reverse Engineering | by Ankeet Saha](https://me-ankeet.medium.com/ctf-writeup-random-bug-reverse-engineering-f17ebba1c5b3) | ✍️ Medium | 2024–2024 | In this article, I will do a walk through of a CTF challenge which was a part of TyroCTF 2024 under the Reverse Enginee… |
| 9 | [Reverse Engineering CTF writeup: My Favorite Fruit — DreamHack](https://medium.com/@talal.ak/reverse-engineering-ctf-writeup-my-favorite-fruit-dreamhack-5b2cc2a961d0) | ✍️ Medium | n/a | Recently I solved a challenge on DreamHack and the challenge name was My Favorite Fruit. The challenge was a sort of ch… |
| 10 | [How I Became the “Reverse Guy” in My CTF Team | by Rusty - Medium](https://rustybladez.medium.com/how-i-became-the-reverse-guy-in-my-ctf-team-c6fc2cef1512) | ✍️ Medium | n/a | I thought I'd become an all-rounder. Binary Exploitation, Cryptography, Forensics, OSINT, Reverse Engineering, you call… |
| 11 | [CSAW CTF 2023 Writeup - tripoloski blog](https://tripoloski1337.github.io/ctf/pwn/uaf/heap/2023/09/18/csawctf2023-writeup.html) | 📝 Blog | 2023–2023 | I competed on CSAW CTF 2023, and I solved multiple challenges e.g. from pwn, incident response and reverse engineering. |
| 12 | [ICMTC CTF 2024 Reverse Engineering Challenges Write Up](https://medium.com/@ELJoOker/icmtc-ctf-reverse-engineering-and-forensics-challenges-write-up-b3c0167ef171) | ✍️ Medium | 2024–2024 | Hello everyone! Today I'll share my solutions for solved reverse engineering challenges in ICMTC quals competition. |

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
