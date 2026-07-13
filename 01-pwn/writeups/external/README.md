# Pwn Writeups — External Sources

This folder contains full, complete pwn CTF writeups sourced from personal blogs, CTF team archives, and security research blogs — **not** from Medium. Each writeup was downloaded in full, converted to markdown, and its images were downloaded and stored locally so the collection is fully self-contained.

## Why not Medium?

Medium articles are often truncated behind a paywall or end mid-sentence with "..." — they're not reliable as reference material. The writeups here come from personal blogs and CTF team archives where the full content is freely accessible and the authors are pwn practitioners who document their complete solve paths.

## Writeup index

| # | Writeup | Event | Topic | Words | Images |
|---|---------|-------|-------|-------|--------|
| 1 | [A Full Guide to Format String Exploitation](blog-format-string-exploitation/writeup.md) | Tutorial | Format string attack — printf %p leak, %n write, GOT overwrite | 3,224 | 30 |
| 2 | [Format — HackTheBox Challenge](en-ctf-htb-challenges-pwn-format/writeup.md) | HTB | Format string vulnerability on a HackTheBox pwn challenge | 1,967 | 4 |
| 3 | [Cyber Apocalypse 2023: Pwn](posts-cyber-apocalypse-2023-pwn/writeup.md) | Cyber Apocalypse 2023 | Multiple pwn challenges — stack, heap, ROP | 20,967 | 8 |
| 4 | [Cyber Apocalypse 2024: Pwn](posts-cyber-apocalypse-2024-pwn/writeup.md) | Cyber Apocalypse 2024 | Multiple pwn challenges across difficulty tiers | 11,923 | 0 |
| 5 | [Google CTF 2025](posts-google-ctf-2025/writeup.md) | Google CTF 2025 | Elite-tier pwn — shellcode injection, RWX exploitation | 8,041 | 0 |
| 6 | [MapleCTF 2022](posts-maplectf-2022/writeup.md) | MapleCTF 2022 | Multiple pwn challenges with detailed analysis | 4,794 | 4 |
| 7 | [HacktivityCTF 2021 — Pawn Shop](blog-hacktivityctf2021-pawn-shop/writeup.md) | HacktivityCTF 2021 | Heap exploitation — tcache poisoning, UAF | 3,699 | 0 |
| 8 | [Llama.cpp RPC RCE](blog-llama-rpc-rce/writeup.md) | Research | Real-world heap exploitation in Llama.cpp | 11,045 | 16 |
| 9 | [Heap Exploitation — glibc Internals](heap-exploitation-glibc-internals-and-nifty-tricks/writeup.md) | Research | Deep dive into glibc heap internals and exploitation tricks | 5,195 | 0 |
| 10 | [CSAW CTF 2023 — UAF/Heap](ctf-pwn-uaf-heap-2023-09-18-csawctf2023-writeup/writeup.md) | CSAW CTF 2023 | Use-after-free on a heap-based challenge | 1,918 | 13 |
| 11 | [Guide of Seccomp in CTF](2022-07-03-guide-of-seccomp-in-ctf/writeup.md) | Google CTF 2022 | Seccomp/BPF sandbox bypass techniques | 1,856 | 4 |
| 12 | [Angstrom CTF — Art of the Shell](angstrom-ctf-art-of-the-shell-writeup/writeup.md) | AngstromCTF | Shellcode crafting and injection | 1,852 | 1 |

**Total:** 12 writeups, ~77,000 words, 80 images — all locally stored, no external dependencies.

## Structure

Each writeup is stored in its own subdirectory:

```
external/
├── blog-format-string-exploitation/
│   ├── writeup.md          ← the full writeup
│   └── images/             ← downloaded images (img_1.png, img_2.png, ...)
├── posts-cyber-apocalypse-2023-pwn/
│   ├── writeup.md
│   └── images/
└── ... (10 more)
```

## Attribution

Each writeup includes a source header at the top with:
- The original URL where the writeup was published
- The author (if known)
- The retrieval date
- Word count and image count

The writeups are reproduced here for educational and reference purposes. All credit goes to the original authors. The original authors' blogs and CTF team archives are the canonical sources.

## Topics covered

- **Stack exploitation:** buffer overflows, ret2libc, ret2win, ROP chains
- **Heap exploitation:** tcache poisoning, use-after-free, fastbin dup, glibc internals
- **Format string attacks:** %p leaks, %n writes, GOT overwrite
- **Shellcode:** crafting, injection, constraint-aware generation
- **Seccomp/BPF:** sandbox bypass techniques
- **Kernel-adjacent:** Llama.cpp heap exploitation (real-world target)
- **Multi-challenge event writeups:** Cyber Apocalypse 2023/2024, Google CTF 2025, MapleCTF 2022, HacktivityCTF 2021, CSAW CTF 2023, AngstromCTF
