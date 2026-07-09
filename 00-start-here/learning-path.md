# 🎯 CTF Learning Path — From Zero to Elite

This is a structured, opinionated learning path. It assumes you have basic programming literacy (any language) and basic command-line comfort, but no prior security knowledge. Follow it in order; each step builds on the previous.

## Phase 1: Foundations (Weeks 1–4)

**Goal:** Build the underlying skills that every CTF category depends on.

### 1.1 Linux command line
- **Required proficiency:** file system navigation, text manipulation (`grep`, `awk`, `sed`, `cut`), process management, basic networking (`curl`, `nc`, `ssh`), and shell scripting.
- **Resource:** [OverTheWire Bandit](https://overthewire.org/wargames/bandit/) — 34 levels of progressively harder Linux command-line puzzles. Free, browser-based.
- **Time:** 1 week of evenings.

### 1.2 Python programming
- **Required proficiency:** variables, control flow, functions, file I/O, sockets, regular expressions, and the `requests` library.
- **Resource:** Any intro Python course, plus the [pwntools docs](https://docs.pwntools.com/) (read the first 5 sections).
- **Time:** 1–2 weeks.

### 1.3 Networking fundamentals
- **Required proficiency:** TCP/IP, HTTP, DNS, and the ability to read a packet capture in Wireshark.
- **Resource:** [HackTheBox Academy — Network Fundamentals](https://academy.hackthebox.com/) (free tier).
- **Time:** 1 week.

### 1.4 Set up your environment
- **Required:** a Linux VM (Ubuntu 22.04 LTS is the safe default), [pwntools](https://docs.pwntools.com/), [Ghidra](https://ghidra-sre.org/), [Burp Suite Community Edition](https://portswigger.net/burp), [Wireshark](https://www.wireshark.org/).
- **Optional but useful:** [Volatility](https://www.volatilityfoundation.org/), [angr](https://angr.io/), [SageMath](https://www.sagemath.org/).
- See [`tools-cheatsheet.md`](tools-cheatsheet.md) for installation commands.

## Phase 2: Beginner CTFs (Weeks 5–8)

**Goal:** Apply your foundation to actual CTF challenges at the beginner tier.

### 2.1 picoCTF (the canonical beginner CTF)
- **What it is:** Carnegie Mellon University's beginner-friendly CTF, always-on, with hundreds of challenges organized by category and difficulty.
- **How to use it:** Work through picoCTF 2019, 2020, 2021, 2022, 2023, 2024, and 2025 editions. Aim to solve 30+ challenges per edition.
- **Time:** 4 weeks of evenings.
- **Companion writeups:** [`Cajac/picoCTF-Writeups`](https://github.com/Cajac/picoCTF-Writeups) (250+ writeups), [`noamgariani11/picoCTF-2024-Writeup`](https://github.com/noamgariani11/picoCTF-2024-Writeup).

### 2.2 TryHackMe (beginner learning path)
- **What it is:** A structured learning platform with rooms that walk you through specific topics with hands-on exercises.
- **How to use it:** Complete the "Complete Beginner" and "Web Fundamentals" learning paths.
- **Time:** 2–3 weeks.
- **Companion writeups:** [`The-Debarghya/TryHackMe-Writeups`](https://github.com/The-Debarghya/TryHackMe-Writeups), [`ShubhamJagtap2000/TryHackMe-THM`](https://github.com/ShubhamJagtap2000/TryHackMe-THM).

## Phase 3: Pick a specialty (Weeks 9–16)

**Goal:** Develop competition-level depth in one or two categories.

Pick **one** of the following tracks based on your background and interests:

### Track A: Pwn (binary exploitation)
- **Prerequisites:** Comfort with C, x86-64 assembly basics, gdb.
- **Curriculum:**
  1. [pwn.college](https://pwn.college/) — the canonical structured pwn learning path, from absolute basics to kernel exploitation. Free, hosted by Arizona State University.
  2. [pwnable.kr](https://pwnable.kr/) — classic pwn challenges, well-documented.
  3. [pwnable.tw](https://pwnable.tw/) — harder pwn challenges, less hand-holding.
- **Companion repos:** [`docfate111/binary_exploitation`](https://github.com/docfate111/binary_exploitation), [`merrychap/ctf-writeups`](https://github.com/merrychap/ctf-writeups).
- **Time:** 6–8 weeks.

### Track B: Web exploitation
- **Prerequisites:** HTTP, basic JavaScript, basic SQL.
- **Curriculum:**
  1. [PortSwigger Web Security Academy](https://portswigger.net/web-security) — free, comprehensive, by the makers of Burp Suite. Work through all Apprentice and Practitioner labs.
  2. [OWASP Top 10](https://owasp.org/Top10/) — read all 10 entries.
  3. HackTheBox web challenges (medium tier).
- **Companion repos:** [`orangetw/My-CTF-Web-Challenges`](https://github.com/orangetw/My-CTF-Web-Challenges).
- **Time:** 4–6 weeks.

### Track C: Crypto
- **Prerequisites:** Discrete mathematics, modular arithmetic, basic number theory.
- **Curriculum:**
  1. [CryptoHack](https://cryptohack.org/) — free, comprehensive crypto CTF learning platform.
  2. [ashutosh1206/Crypto-CTF-Writeups](https://github.com/ashutosh1206/Crypto-CTF-Writeups) — read 10+ writeups.
  3. Solve RSA challenges using SageMath.
- **Companion repos:** [`rkm0959/CTFWriteups`](https://github.com/rkm0959/CTFWriteups), [`ashutosh1206/Crypto-CTF-Writeups`](https://github.com/ashutosh1206/Crypto-CTF-Writeups).
- **Time:** 6–8 weeks.

### Track D: Reverse Engineering
- **Prerequisites:** C, x86-64 assembly, basic compiler theory.
- **Curriculum:**
  1. [pwn.college RE module](https://pwn.college/) — RE-specific challenges.
  2. Reverse engineer 5–10 CrackMe challenges from [crackmes.one](https://crackmes.one/).
  3. Work through [`1GN1tE/CTF_Writeups`](https://github.com/1GN1tE/CTF_Writeups) — RE-focused.
- **Companion repos:** [`Kasimir123/CTFWriteUps`](https://github.com/Kasimir123/CTFWriteUps), [`1GN1tE/CTF_Writeups`](https://github.com/1GN1tE/CTF_Writeups).
- **Time:** 6–8 weeks.

### Track E: Blockchain / Web3
- **Prerequisites:** Solidity, JavaScript, basic understanding of Ethereum.
- **Curriculum:**
  1. [Ethernaut](https://ethernaut.openzeppelin.com/) — OpenZeppelin's progressively harder smart-contract CTF.
  2. [Damn Vulnerable DeFi](https://www.damnvulnerabledefi.xyz/) — DeFi-specific challenges.
  3. [Capture The Ether](https://capturetheether.com/) — broader Ethereum challenges.
- **Companion repos:** [`minaminao/ctf-blockchain`](https://github.com/minaminao/ctf-blockchain), [`AshiqAhamed17/web3-ctf-writeups`](https://github.com/AshiqAhamed17/web3-ctf-writeups).
- **Time:** 4–6 weeks.

## Phase 4: Live competitions (Weeks 17+)

**Goal:** Apply your specialty in real-time, competitive conditions.

### 4.1 Form or join a team
- Most CTFs allow team play. Joining an existing team accelerates learning dramatically.
- Find teams via [CTFtime](https://ctftime.org/), local university CTF clubs, or Discord servers like [LiveOverflow's](https://discord.gg/liveoverflow).

### 4.2 Play weekly CTFs
- [CTFtime](https://ctftime.org/event/list/) lists upcoming CTFs.
- Aim to play at least 1 CTF per month.
- After each CTF, **write up your solves** — this is the single most important learning habit you can build.

### 4.3 Read elite writeups
- After each major CTF (DEF CON, hxp, 0CTF, DiceCTF, corCTF), read the team writeups within 1 week.
- Team writeup archives: [`p4-team/ctf`](https://github.com/p4-team/ctf), [`r3kapig/writeup`](https://github.com/r3kapig/writeup), [`theori-io/ctf`](https://github.com/theori-io/ctf).

## Phase 5: Elite tier (Months 6+)

**Goal:** Compete at the highest level.

At this point you should be ready to attempt:
- DEF CON CTF Qualifiers (annual, May/June)
- Google CTF (annual, June)
- hxp CTF (annual, December)
- 0CTF/TCTF (annual, March)
- RealWorldCTF (annual, January)
- HitCon CTF (annual, August)
- PlaidCTF (annual, May)

Study the official source releases from Nautilus Institute (DEF CON), dicegang (DiceCTF), Crusaders-of-Rust (corCTF), and similar organizers — these reveal the intended solve path and are the gold standard for elite-tier learning.

## Closing advice

- **Writeups are the most important habit.** Even if you solve a challenge in 5 minutes, write a 2-paragraph summary. The act of writing crystallizes the learning.
- **Don't skip fundamentals.** It's tempting to jump straight to advanced heap exploitation, but you'll get stuck on basics. Spend the time on Phase 1.
- **Find a community.** CTFs are more fun and more productive with a team. Join a Discord, find a local meetup, or form a team with friends.
- **Be patient.** CTFs are hard. The first 10 challenges you attempt will feel impossible. The next 100 will feel doable. After 1000, you'll see patterns everywhere.
