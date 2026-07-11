# 🎯 My CTF Learning Path

This is the learning path I'm working through. I'm documenting it here so I can track my own progress and so future-me can see where I left off. It assumes basic programming literacy (any language) and basic command-line comfort, but no prior security knowledge.

Each phase has a rough time estimate — these are aspirational, not prescriptive. The real measure of readiness is whether I can solve challenges at the next tier, not whether I've logged the hours.

Detailed notes on every learning platform and tool mentioned below live in the [`resources/`](resources/) subfolder so this file stays readable. When I reference a platform or tool here, the link goes to my local notes, not to the platform's own site.

## Phase 1: Foundations (Weeks 1–4)

**Goal:** Build the underlying skills that every CTF category depends on.

### 1.1 Linux command line
- **Required proficiency:** file system navigation, text manipulation (`grep`, `awk`, `sed`, `cut`), process management, basic networking (`curl`, `nc`, `ssh`), and shell scripting.
- **Resource:** [OverTheWire Bandit](resources/learning-platforms.md#overthewire--bandit) — 34 levels of progressively harder Linux command-line puzzles. Free, browser-based. Full notes and SSH connection instructions in my local reference.
- **Time:** 1 week of evenings.

### 1.2 Python programming
- **Required proficiency:** variables, control flow, functions, file I/O, sockets, regular expressions, and the `requests` library.
- **Resource:** Any intro Python course, plus the [pwntools docs](resources/security-tools.md#pwntools) — I keep installation, API summary, and the command-line tools list locally.
- **Time:** 1–2 weeks.

### 1.3 Networking fundamentals
- **Required proficiency:** TCP/IP, HTTP, DNS, and the ability to read a packet capture in Wireshark.
- **Resource:** [HackTheBox Academy — Network Fundamentals](resources/learning-platforms.md#hackthebox-academy) (free tier). My local notes cover which free-tier modules are relevant for CTF.
- **Time:** 1 week.

### 1.4 Set up my environment
- **Required:** a Linux VM (Ubuntu 22.04 LTS is the safe default). Tools I install locally — full installation steps in [`resources/security-tools.md`](resources/security-tools.md):
  - [pwntools](resources/security-tools.md#pwntools) — CTF exploit framework.
  - [Ghidra](resources/security-tools.md#ghidra) — NSA's reverse-engineering suite.
  - [Burp Suite Community Edition](resources/security-tools.md#burp-suite-community-edition) — web proxy.
  - [Wireshark](resources/security-tools.md#wireshark) — packet capture analysis.
- **Optional but useful:**
  - [Volatility](resources/security-tools.md#volatility) — memory forensics.
  - [angr](resources/security-tools.md#angr) — symbolic execution.
  - [SageMath](resources/security-tools.md#sagemath) — symbolic math, lattice reduction.
- See [`tools-cheatsheet.md`](tools-cheatsheet.md) for the everyday one-liners I use with these tools.

## Phase 2: Beginner CTFs (Weeks 5–8)

**Goal:** Apply the foundation to actual CTF challenges at the beginner tier.

### 2.1 picoCTF (the canonical beginner CTF)
- **What it is:** Carnegie Mellon University's beginner-friendly CTF, always-on, with hundreds of challenges organized by category and difficulty.
- **How I use it:** Work through picoCTF 2019 through 2025 editions. Aim to solve 30+ challenges per edition, and write up every solve in [`20-events/picoctf/`](../20-events/picoctf/).
- **Time:** 4 weeks of evenings.

### 2.2 TryHackMe (beginner learning path)
- **What it is:** A structured learning platform with rooms that walk you through specific topics with hands-on exercises. Full notes in my [local reference](resources/learning-platforms.md#tryhackme).
- **How I use it:** Complete the "Complete Beginner" and "Web Fundamentals" learning paths. Write up every room in [`20-events/tryhackme/`](../20-events/tryhackme/).
- **Time:** 2–3 weeks.

## Phase 3: Pick a specialty (Weeks 9–16)

**Goal:** Develop competition-level depth in one or two categories.

Pick **one** of the following tracks based on background and interests. I'm currently focusing on [Track X — fill in when decided].

### Track A: Pwn (binary exploitation)
- **Prerequisites:** Comfort with C, x86-64 assembly basics, gdb.
- **Curriculum:**
  1. [pwn.college](resources/learning-platforms.md#pwncollege) — the canonical structured pwn learning path, from absolute basics to kernel exploitation. Free, hosted by Arizona State University. My local notes cover the module list and the "no public writeups" rule.
  2. [pwnable.kr](resources/learning-platforms.md#pwnablekr) — classic pwn challenges, well-documented. Notes cover all four tiers.
  3. [pwnable.tw](resources/learning-platforms.md#pwnabletw) — harder pwn challenges, less hand-holding. Notes cover notable challenges and libc-patching tips.
- **Time:** 6–8 weeks.

### Track B: Web exploitation
- **Prerequisites:** HTTP, basic JavaScript, basic SQL.
- **Curriculum:**
  1. [PortSwigger Web Security Academy](resources/learning-platforms.md#portswigger-web-security-academy) — free, comprehensive, by the makers of Burp Suite. Work through all Apprentice and Practitioner labs. Local notes cover the topic list.
  2. [OWASP Top 10](resources/ctf-communities.md#owasp-top-10) — read all 10 entries. Local notes include the full 2021 list with my own annotations.
  3. HackTheBox web challenges (medium tier).
- **Time:** 4–6 weeks.

### Track C: Crypto
- **Prerequisites:** Discrete mathematics, modular arithmetic, basic number theory.
- **Curriculum:**
  1. [CryptoHack](resources/learning-platforms.md#cryptohack) — free, comprehensive crypto CTF learning platform. Local notes cover all categories and the SageMath recommendation.
  2. Solve RSA challenges using [SageMath](resources/security-tools.md#sagemath).
  3. Work through the historical cryptanalysis literature (Vigenère, Enigma, Bleichenbacher).
- **Time:** 6–8 weeks.

### Track D: Reverse Engineering
- **Prerequisites:** C, x86-64 assembly, basic compiler theory.
- **Curriculum:**
  1. [pwn.college RE module](resources/learning-platforms.md#pwncollege) — RE-specific challenges.
  2. Reverse engineer 5–10 CrackMe challenges from [crackmes.one](resources/learning-platforms.md#crackmesone). Local notes cover difficulty filtering and language choice.
  3. Work through obfuscated JavaScript and Python challenges for variety.
- **Time:** 6–8 weeks.

### Track E: Blockchain / Web3
- **Prerequisites:** Solidity, JavaScript, basic understanding of Ethereum.
- **Curriculum:**
  1. [Ethernaut](resources/learning-platforms.md#ethernaut) — OpenZeppelin's progressively harder smart-contract CTF. Local notes cover how to connect and what the levels teach.
  2. [Damn Vulnerable DeFi](resources/learning-platforms.md#damn-vulnerable-defi) — DeFi-specific challenges. Local notes cover the Foundry workflow.
  3. [Capture The Ether](resources/learning-platforms.md#capture-the-ether) — broader Ethereum challenges.
- **Time:** 4–6 weeks.

### Track F: Forensics & Steganography
- **Prerequisites:** Basic file analysis, Linux command line, understanding of common file formats (PNG, JPEG, PDF, WAV).
- **Curriculum:**
  1. Work through picoCTF Forensics challenges (beginner to intermediate).
  2. Study [Volatility](resources/security-tools.md#volatility) for memory forensics and [Wireshark](resources/security-tools.md#wireshark) for network forensics.
  3. Work through Autopsy for disk forensics.
  4. Practice steganography with `steghide`, `zsteg`, and `stegsolve`.
- **Time:** 4–6 weeks.

### Track G: OSINT (Open-Source Intelligence)
- **Prerequisites:** Comfortable with web search, social media platforms, and basic analysis skills.
- **Curriculum:**
  1. Start with [Sherlock](resources/osint-resources.md#sherlock-command-line) for username enumeration across platforms. Installation and usage in my local notes.
  2. Practice with [TryHackMe OSINT rooms](resources/learning-platforms.md#tryhackme) for structured challenges.
  3. Learn geolocation with Google Earth, [SunCalc](resources/osint-resources.md#suncalc) (shadow analysis), and reverse image search ([TinEye](resources/osint-resources.md#tineye), Yandex).
  4. Study breach database search with [Have I Been Pwned](resources/osint-resources.md#have-i-been-pwned) and dehashed.
- **Time:** 3–4 weeks.

## Phase 4: Live competitions (Weeks 17+)

**Goal:** Apply the specialty in real-time, competitive conditions.

### 4.1 Form or join a team
- Most CTFs allow team play. Joining an existing team accelerates learning dramatically.
- Find teams via [CTFtime](resources/ctf-communities.md#ctftime), local university CTF clubs, or Discord servers like [LiveOverflow's](resources/ctf-communities.md#liveoverflow-discord).

### 4.2 Play weekly CTFs
- [CTFtime](resources/ctf-communities.md#ctftime) lists upcoming CTFs.
- Aim to play at least 1 CTF per month.
- After each CTF, **write up every solve** — even the ones I solved in 5 minutes. The writeup is the part that compounds over time.

### 4.3 Read elite writeups
- After each major CTF (DEF CON, hxp, 0CTF, DiceCTF, corCTF), read the top-placing teams' writeups within 1 week of the event ending.
- I track these in [`20-events/`](../20-events/) by event name. The goal is to compare my solve path against the intended path and note what I missed.

## Phase 5: Elite tier (Months 6+)

**Goal:** Compete at the highest level.

At this point I should be ready to attempt:
- DEF CON CTF Qualifiers (annual, May/June)
- Google CTF (annual, June)
- hxp CTF (annual, December)
- 0CTF/TCTF (annual, March)
- RealWorldCTF (annual, January)
- HitCon CTF (annual, August)
- PlaidCTF (annual, May)

Study the official source releases from Nautilus Institute (DEF CON), dicegang (DiceCTF), Crusaders-of-Rust (corCTF), and similar organizers — these reveal the intended solve path and are the gold standard for elite-tier learning.

## Closing advice to myself

- **Writeups are the most important habit.** Even if I solve a challenge in 5 minutes, write a 2-paragraph summary. The act of writing crystallizes the learning.
- **Don't skip fundamentals.** It's tempting to jump straight to advanced heap exploitation, but I'll get stuck on basics. Spend the time on Phase 1.
- **Find a community.** CTFs are more fun and more productive with a team. Join a Discord, find a local meetup, or form a team with friends.
- **Be patient.** CTFs are hard. The first 10 challenges I attempt will feel impossible. The next 100 will feel doable. After 1000, I'll see patterns everywhere.
