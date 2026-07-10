# Binary Exploitation

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Memory corruption, control-flow hijacking, ROP, heap exploitation, kernel pwn, and exploitation of off-by-one / format-string / use-after-free bugs. The most technically dense category in CTF, requiring fluency in assembly, ABI details, and exploit-development tooling (pwntools, ROPgadget, one_gadget, gdb-gef/pwndbg).

## 🔬 Sub-Topic Deep Dive

The Binary Exploitation category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Stack-based exploitation

buffer overflows, off-by-one, stack canary bypass, ROP.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [PwnLand - the collection](../01-pwn/archives/PwnLand) — 📚 Repository

### Heap exploitation

use-after-free, double-free, fastbin/unbin/tcache attacks, House of Force/Spirit/Einherjar/etc..

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [PwnLand - the collection](../01-pwn/archives/PwnLand) — 📚 Repository

### Format string attacks

arbitrary read/write via printf-family functions.

*No directly-matching resources in this collection — consult the broader category list above.*

### Kernel pwn

Linux kernel exploitation: SLUB allocator, msg_msg, pipe_buffer, struct-file abuse.

Top resources for this sub-topic:

- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository
- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium

### Exploit mitigations

ASLR, NX, PIE, RELRO, stack canaries, CFI.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [LiveOverflow/pwn_docker_example: Example pwnable challenge hosted](../01-pwn/archives/pwn_docker_example) — 📚 Repository
- [PwnLand - the collection](../01-pwn/archives/PwnLand) — 📚 Repository

### ARM / RISC-V pwn

exploitation on non-x86 architectures; common in IoT challenges.

Top resources for this sub-topic:

- [r3kapig/writeup: CTF challenges writeup - the collection](../30-archetypes/archives/team-archives/writeup-r3kapig) — 📚 Repository
- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - the collection](../30-archetypes/archives/awesome-lists/awesome-ctf) — 📚 Repository
- [Hack The Box Writeups - The Ultimate HTB Resource - the collection](../20-events/archives/hackthebox/htb-writeups) — 📚 Repository
- [orangetw/My-CTF-Web-Challenges - the collection](../02-web/archives/My-CTF-Web-Challenges) — 📚 Repository
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository

## 🎯 Suggested Learning Order

If you're new to binary exploitation, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [pwn.college](https://pwn.college/) — the canonical structured pwn learning path. Work through 'Program Misuse' → 'Shellcode Injection' → 'Sandboxing' → 'System Shell' → 'Shellcode Injection II' → 'Dynamic Allocator Misuse' → 'Heap Exploitation' → 'Kernel Exploitation'.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
