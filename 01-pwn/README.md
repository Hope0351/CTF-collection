# Binary Exploitation

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Memory corruption, control-flow hijacking, ROP, heap exploitation, kernel pwn, and exploitation of off-by-one / format-string / use-after-free bugs. The most technically dense category in CTF, requiring fluency in assembly, ABI details, and exploit-development tooling (pwntools, ROPgadget, one_gadget, gdb-gef/pwndbg).

This category contains **73 curated sources** from across the CTF ecosystem: 47 internal archives, 13 Medium articles, 6 YouTube video walkthroughs, 0 CTFtime event entries, and 7 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Difficulty |
|---:|---|---|
| 1 | [Pwn Challenges writeup — RVCExIITB CTF](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) | — |
| 2 | [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) | — |
| 3 | [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) | — |
| 4 | [Pwn Challenges CTF 2025 [binary Exploiation]](https://livepwn.medium.com/pwn-challenges-ctf-2025-binary-exploiation-c0ce691b9451) | Beginner |
| 5 | [pwnable.kr - bof](https://0xrick.github.io/pwn/bof) | Beginner |
| 6 | [PlaidCTF 2023 Writeups](https://siunam321.github.io/ctf/PlaidCTF-2023) | — |
| 7 | [pwn.college](https://pwn.college) | Beginner |
| 8 | [PWN: Return To Win (ret2win) | Binary Exponentiation for Beginners](https://medium.com/@fahimalshihabifty/pwn-return-to-win-ret2win-binary-exponentiation-for-beginners-1de7e0fc85cc) | Beginner |
| 9 | [csawctf{CSAW-CTF-24}](https://medium.com/@iabdullah_215/csawctf-csaw-ctf-24-a8fd8082f944) | — |
| 10 | [ICTF 2025 Writeup](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | — |
| 11 | [Decode-E-Cyber CTF 2023 — PWN/Binary Exploitation Writeup](https://febinj.medium.com/decode-e-cyber-ctf-2023-pwn-binary-exploitation-writeup-1-3e4c93a01dd1) | — |
| 12 | [DiceCTF 2024 Quals](https://chovid99.github.io/posts/dicectf-2024-quals) | Advanced |
| 13 | [Google CTF 2025](https://chovid99.github.io/posts/google-ctf-2025) | — |
| 14 | [GitEx CTF Pwn — Buffer Overflow Writeup](https://medium.com/@0xk4g3/gitex-ctf-pwn-buffer-overflow-writeup-6d261fcfb5bc) | — |
| 15 | [Try Hack Me Industrial Intrusion CTF Writeup: Buffer Overflow Exploit](https://medium.com/@michaelkhanda/try-hack-me-industrial-intrusion-ctf-writeup-buffer-overflow-exploit-on-start-binary-2d54e6df3688) | Beginner |
| 16 | [Binary Exploitation (Pwn) Challenge Walkthroughs](https://www.youtube.com/watch?v=xOHLniVJsJY) | — |
| 17 | [Day 25: buffer overflow 0 — picoCTF Binary Exploitation Writeup](https://medium.com/@siyam.exe/day-25-buffer-overflow-0-picoctf-binary-exploitation-writeup-def18015cbb1) | Beginner |
| 18 | [Pwnable.kr — bof - Shellbr3ak](https://shellbr3ak.medium.com/pwnable-kr-bof-d78f3ed36747) | Beginner |
| 19 | [TsukuCTF 2025 Writeups](https://r1ru.github.io/posts/7) | Elite |
| 20 | [pwncollege: Dealing with Data](https://medium.com/@souravbose361/pwn-college-dealing-with-data-1d7bac04c1a4) | Beginner |
| 21 | [HTB x Synack RedTeamFive Capture The Flag (CTF) 2021](https://www.youtube.com/watch?v=Kqu3qpYMml8) | Intermediate |
| 22 | [Walkthrough of bof level in pwnable.kr](https://www.youtube.com/watch?v=rwfKScdQybE) | Beginner |
| 23 | [Beginner Buffer Overflow! - pwnable.kr bof walkthrough](https://www.youtube.com/watch?v=3TBdVE9upqo) | Beginner |
| 24 | [CSAW CTF 2023 Writeup](https://tripoloski1337.github.io/ctf/pwn/uaf/heap/2023/09/18/csawctf2023-writeup.html) | — |
| 25 | [DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn)](https://www.youtube.com/watch?v=CGbPWSVm99k) | Advanced |

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
