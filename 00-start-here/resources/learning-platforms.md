# Learning Platforms Reference

This file consolidates the learning platforms referenced in my CTF learning
path. Instead of linking out to each platform every time, I keep the
descriptions and getting-started notes here so the collection stays
self-contained.

---

## OverTheWire — Bandit

**What it is.** A wargame aimed at absolute beginners, hosted by the
OverTheWire community. It teaches the Linux command-line basics needed
before tackling any other wargame or CTF category.

**How it works.** The game is organised in 34 levels (Level 0 through
Level 33). You start at Level 0 and try to "beat" or "finish" it. Finishing
a level gives you the password for the next level. Each level has a page on
the site describing the goal and how to connect.

**How to connect.** Levels are played over SSH against
`bandit.labs.overthewire.org` on port 2220. The password for Level 0 is
`bandit0`. From a terminal:

```bash
ssh bandit0@bandit.labs.overthewire.org -p 2220
# password: bandit0
```

**Skills covered.** File system navigation, file permissions, `find`,
`grep`, `tar`, `gzip`, `base64`, `xxd`, cron jobs, git repos, and basic
shell scripting. By the end of the 34 levels you should be comfortable
enough on the Linux command line to start any other wargame.

**Tips for myself.**
- Read the level page carefully — it usually tells you exactly which
  command to look up.
- Use `man <command>` liberally. The man pages are the intended reference.
- Don't reach for a walkthrough before trying for at least 20 minutes. The
  struggle is the lesson.

---

## pwn.college

**What it is.** An education platform for developing and practicing core
cybersecurity skills in a hands-on fashion, hosted by Arizona State
University. It is open and free for anyone to participate.

**How it works.** You register on the dojo and receive a "white belt",
signifying the beginning of your journey. You then progress through
modules, earning belts as you complete challenges. The platform powers much
of ASU's cybersecurity curriculum.

**Modules available.**
- **Program Misuse** — privilege escalation via file-permission and
  setuid mistakes.
- **Shellcode** — writing and injecting shellcode.
- **Reverse Engineering** — statically and dynamically analysing
  binaries.
- **Pwn (Binary Exploitation)** — stack, heap, format strings, ROP.
- **Rop** — return-oriented programming chains.
- **Heap Exploitation** — glibc heap internals and exploitation.
- **Kernel Exploitation** — Linux kernel attack surface.
- **Assembly** — x86_64 and RISC-V assembly.

**Important rule.** pwn.college asks that you do **not** publish writeups,
walkthrough videos, or livestreams of challenge solutions. The challenges
are used to grade university students. I respect this — my notes on
pwn.college challenges stay private and are not pushed to this repo.

**How to start.** Register at the dojo (search "pwn.college dojo"), pick
the module you want to work through, and follow the "Start" instructions
for each challenge. Challenges run inside a per-user namespace on the
platform's infrastructure.

---

## pwnable.kr

**What it is.** A classic wargame site for binary exploitation, with
challenges organised into four difficulty tiers: Toddler, Rookiss, Grotesque,
and Hacker's Secret. It has been a staple of the pwn community for years.

**How to connect.** Create an account on the site. Toddler-tier challenges
give you SSH access to a remote box where the vulnerable binary lives.
Higher tiers may give you only a binary to download and analyse locally.

**Tiers.**
- **Toddler** — beginner-friendly, teaches the basics of file descriptor
  manipulation, stack overflows, and format strings.
- **Rookiss** — intermediate, includes UAF, heap exploitation, and
  ROP-based challenges.
- **Grotesque** — hard, multi-stage challenges.
- **Hacker's Secret** — the hardest tier, often requiring kernel-level
  exploitation or creative techniques.

**Tips for myself.**
- Start with `fd`, `collision`, `bof`, and `flag` in the Toddler tier.
- The Toddler tier has hints on the challenge page — read them.
- Keep a local copy of each binary you download; the site occasionally
  rotates challenges.

---

## pwnable.tw

**What it is.** A harder sibling of pwnable.kr, with less hand-holding and
more realistic challenge difficulty. Good preparation for live CTF pwn
challenges.

**How to connect.** Register on the site, then SSH into the challenge
boxes as described on each challenge page. Some challenges only provide a
binary and a libc — you do the rest locally.

**Notable challenges.**
- `start` — small MIPS-style stack overflow, good warm-up.
- `orw` — open/read/write shellcode.
- `calc` — a stack-based calculator with an arithmetic overflow.
- `hacknote` — classic UAF on a heap-based note-taking program.
- `Silver Bullet` — a RPG-style challenge with a one-byte length overflow.
- `applestore` — a use-after-free in a linked-list "cart".

**Tips for myself.**
- pwnable.tw challenges usually ship with a specific libc. Download it
  from the challenge page and patch your local binary with
  `patchelf --set-interpreter ./ld-linux.so ./challenge` and
  `patchelf --replace-needed libc.so.6 ./libc.so`.
- The intended difficulty is "I can solve pwnable.kr comfortably" before
  starting here.

---

## CryptoHack

**What it is.** A free, fun platform for learning modern cryptography by
solving interactive puzzles and challenges. You learn by breaking the
ciphers and protocols that secure the digital world.

**How it works.** Register on the platform, pick a category, and start
solving. Each challenge gives you a Python script or a server endpoint to
attack. Solving a challenge awards points; finishing a category earns a
trophy.

**Categories.**
- **Introduction** — XOR, base64, basic Python.
- **Symmetric Cryptography** — AES, ECB, CBC, GCM, padding oracles.
- **Mathematics** — modular arithmetic, primes, GCD.
- **Hash Functions** — collision, length-extension.
- **RSA** — small exponents, Wiener, Hastad, common modulus.
- **Elliptic Curves** — ECDLP, invalid curve, Pohlig-Hellman.
- **Lattices** — LLL, CVP, hidden number problem.
- **Miscellaneous** — Diffie-Hellman, PRNGs, zero-knowledge.

**Tips for myself.**
- Install SageMath before starting — many lattice and ECC challenges are
  painful without it.
- Keep a `cryptohack/` folder in my repo for solver scripts. I do not
  publish full solutions out of respect for the platform, but I keep my
  own notes.
- The leaderboard is a good way to gauge progress, but the real value is
  the category completion trophies.

---

## HackTheBox Academy

**What it is.** HackTheBox's structured learning platform, with
self-paced "paths" and individual "modules" covering everything from
networking fundamentals to advanced red-team operations. A free tier gives
access to a limited set of modules.

**How it works.** Create an account on the Academy (separate from the
main HackTheBox platform). Modules are broken into sections, each with
reading material and a hands-on exercise. Completing exercises awards
cubes (currency) which unlock more modules.

**Relevant free-tier modules for CTF.**
- **Network Fundamentals** — TCP/IP, DNS, HTTP, packet structure.
- **Linux Fundamentals** — file system, permissions, processes.
- **Web Requests** — HTTP methods, headers, cookies.
- **Using Web Proxies** — Burp Suite basics.

**Tips for myself.**
- The free tier is enough to build a foundation. Don't pay until I've
  exhausted free content.
- Pair the Academy with the main HTB platform — Academy teaches the
  theory, the main platform gives me boxes to practice on.

---

## PortSwigger Web Security Academy

**What it is.** A free, comprehensive web-security training platform built
by the makers of Burp Suite. It is the single best free resource for
learning web exploitation, period.

**How it works.** The Academy is organised into topics, each with a set of
labs. Every lab is a self-contained vulnerable web app running in a
browser-accessible container. You solve the lab by exploiting the
vulnerability, then the lab marks itself as solved.

**Topics covered.**
- **Server-side vulnerabilities** — SQLi, SSRF, SSTI, path traversal,
  authentication, access control, file upload, deserialization.
- **Client-side vulnerabilities** — XSS, CSRF, CORS, DOM-based attacks,
  prototype pollution.
- **Advanced topics** — HTTP request smuggling, OAuth, JWT attacks,
  web cache poisoning, HTTP Host header attacks.

**Tips for myself.**
- Work through all Apprentice and Practitioner labs before touching
  Expert labs.
- Don't look at the solution until I've tried for at least 30 minutes.
- The solutions PortSwigger provides are gold — read them even for labs
  I solve, because the intended path is often cleaner than mine.

---

## crackmes.one

**What it is.** A community repository of "CrackMe" challenges — small
binaries specifically designed to be reverse-engineered. Each challenge
has a stated difficulty and a stated language/platform.

**How it works.** Browse the site, download a CrackMe, reverse-engineer
it to find the password or write a keygen, then submit your solution back
to the site. Authors get karma for good challenges; solvers get karma for
good writeups.

**Tips for myself.**
- Filter by difficulty "1" and "2" to start.
- The C/C++ CrackMes are the best preparation for CTF reverse
  engineering.
- Avoid the Java/C# CrackMes until I'm comfortable with native RE — they
  require different tooling (JD-GUI, dnSpy) that doesn't transfer to
  CTFs as cleanly.

---

## Ethernaut

**What it is.** OpenZeppelin's progressively harder smart-contract CTF,
played directly in the browser against a testnet. Each level is a
vulnerable Solidity contract that I must hack.

**How it works.** Connect a browser wallet (MetaMask on a testnet), open
the Ethernaut console, and call `contract.abi` to see what the level
contract exposes. I exploit the contract to trigger the `level`'s
`isComplete` condition, then submit to move on.

**Levels cover.**
- Reentrancy, delegatecall abuse, integer overflow/underflow,
  selfdestruct, access control, randomness, time manipulation, gatekeeper
  patterns, and more.

**Tips for myself.**
- Read the Solidity source for each level carefully — the vulnerability
  is usually right there.
- Keep my exploit transactions in a local Foundry/Hardhat project so I
  can re-run them.

---

## Damn Vulnerable DeFi

**What it is.** A set of DeFi-specific smart-contract challenges, harder
and more realistic than Ethernaut. Each challenge simulates a real DeFi
attack scenario: flash loans, price oracles, governance takeovers, etc.

**How it works.** Clone the repo, install Foundry, and run the challenge
test suite. The goal is to make the provided test pass by writing an
exploit contract.

**Tips for myself.**
- Don't move on from a challenge until I understand *why* the exploit
  works, not just *that* it works.
- The later challenges require understanding Compound, Uniswap, and
  other DeFi protocol internals — read those protocols' source first.

---

## Capture The Ether

**What it is.** A broader Ethereum CTF covering both Solidity smart
contracts and Ethereum-ecosystem challenges (e.g., predicting the
contract address a deployment will create).

**How it works.** Like Ethernaut, you connect a browser wallet and solve
challenges in a testnet console. The challenges are split into "Deploy"
(challenges about predicting/deploying contracts) and "Hack"
(challenges about exploiting deployed contracts).

**Tips for myself.**
- Easier than Damn Vulnerable DeFi but harder than Ethernaut. Good
  middle ground.
- The "Guess the number" family of challenges teaches the lesson that
  on-chain "randomness" is never random.

---

## TryHackMe

**What it is.** A structured learning platform with "rooms" — self-paced
lessons that walk through a specific topic with hands-on exercises. Good
for beginners who want a guided path.

**How it works.** Create an account, pick a learning path or an
individual room, and follow the tasks. Most rooms spin up a virtual
machine that I connect to via OpenVPN or the in-browser attack box.

**Relevant learning paths for CTF.**
- **Complete Beginner** — foundations: Linux, Windows, networking, web.
- **Web Fundamentals** — HTTP, Burp Suite, OWASP Top 10.
- **Jr Penetration Tester** — broader offensive security path.

**Tips for myself.**
- The free tier has plenty of rooms; don't subscribe until I've finished
  the free paths.
- Write up every room I complete, even the easy ones — the practice of
  writing reinforces the practice of hacking.

---

## Source attribution

The descriptions above were written in my own words based on the
official landing pages of each platform, downloaded on
2026-07-11 for reference. The platforms themselves are not reproduced
here — only my notes about them. Platform names are trademarks of their
respective owners.
