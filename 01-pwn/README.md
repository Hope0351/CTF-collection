# Binary Exploitation

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Memory corruption, control-flow hijacking, ROP, heap exploitation, kernel pwn, and exploitation of off-by-one / format-string / use-after-free bugs. The most technically dense category in CTF, requiring fluency in assembly, ABI details, and exploit-development tooling (pwntools, ROPgadget, one_gadget, gdb-gef/pwndbg).

This category contains **73 curated sources** from across the CTF ecosystem: 47 GitHub repositories, 13 Medium articles, 6 YouTube video walkthroughs, 0 CTFtime event entries, and 7 blog posts.

## 🏆 Recommended Repositories (GitHub)

The following GitHub repositories are the highest-value resources for this category. They are ranked by cross-search relevance, mention count, and star count.

| # | Repository | Stars | Difficulty | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | [r3kapig/writeup](../30-archetypes/mirrors/team-archives/writeup-r3kapig) | 188 ⭐⭐ | Varied | 2018–2022 | CTF challenges writeup. r3kapig is a united CTF Team. We are publishing our official writeups here. The writeup page is… |
| 2 | [apsdehal/awesome-ctf](../30-archetypes/mirrors/awesome-lists/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Beginner | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials. This list aims to h… |
| 3 | [momenbasel/htb-writeups](../20-events/mirrors/hackthebox/htb-writeups) | 152 ⭐⭐ | Varied | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactive knowledge graph, s… |
| 4 | [orangetw/My-CTF-Web-Challenges](../02-web/mirrors/My-CTF-Web-Challenges) | 2,853 ⭐⭐⭐⭐ | Varied | 2013–2025 | My CTF Web Challenges. This is the repository of all CTF challenges I made, including the source code, write-up and ide… |
| 5 | [Crypto-Cat/CTF](../30-archetypes/mirrors/personal-collections/CTF-CryptoCat) | 2,512 ⭐⭐⭐⭐ | Varied | 2026–2026 | CTF challenge write-ups, files, scripts etc to go with my video walkthroughs. Check out my blog and discord server. A c… |
| 6 | [xtiankisutsa/awesome-mobile-ctf](../30-archetypes/mirrors/awesome-lists/awesome-mobile-ctf) | 1,157 ⭐⭐⭐⭐ | Varied | 2013–2022 | This is a curated list of mobile based CTFs, write-ups and vulnerable mobile apps. Most of them are android based due t… |
| 7 | [Adamkadaban/CTFs](https://github.com/Adamkadaban/CTFs) | 840 ⭐⭐⭐ | Varied | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types of challenges: https:… |
| 8 | [Kasimir123/CTFWriteUps](https://github.com/Kasimir123/CTFWriteUps) | 61 ⭐⭐ | Varied | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains all source files if th… |
| 9 | [merrychap/ctf-writeups](../30-archetypes/mirrors/personal-collections/ctf-writeups-merrychap) | 36 ⭐ | Varied | n/a | All writeups are about Reverse Engineering and Binary Exploitation tasks. No crypto, forensics, and others. I'm not spe… |
| 10 | [JohnHammond/ctf-katana](../30-archetypes/mirrors/awesome-lists/ctf-katana) | 2,920 ⭐⭐⭐⭐ | Varied | 2015–2020 | This repository aims to hold suggestions (and hopefully/eventually code) for CTF challenges. The "project" is nicknamed… |
| 11 | [hackthebox/cyber-apocalypse-2025](../20-events/mirrors/hackthebox/cyber-apocalypse-2025) | 200 ⭐⭐ | Intermediate | 2025–2025 | Official writeups for Cyber Apocalypse CTF 2025: Tales from Eldoria. Questionnaire about finite fields and elliptic cur… |
| 12 | [dicegang/dicectf-quals-2024-challenges](https://github.com/dicegang/dicectf-quals-2024-challenges) | 30 ⭐ | Elite | 2024–2024 | All challenges from DiceCTF Quals 2024. Contribute to dicegang/dicectf-quals-2024-challenges development by creating an… |
| 13 | [fkie-cad/awesome-embedded-and-iot-security](../30-archetypes/mirrors/awesome-lists/awesome-embedded-and-iot-security) | 2,349 ⭐⭐⭐⭐ | Varied | 2013–2020 | A curated list of awesome resources about embedded and IoT security. The list contains software and hardware tools, boo… |
| 14 | [hackplayers/hackthebox-writeups](https://github.com/hackplayers/hackthebox-writeups) | 2,044 ⭐⭐⭐⭐ | Intermediate | 2017–2023 | Writeups for HacktheBox 'boot2root' machines. Contribute to Hackplayers/hackthebox-writeups development by creating an … |
| 15 | [devploit/awesome-ctf-resources](../30-archetypes/mirrors/awesome-lists/awesome-ctf-resources) | 777 ⭐⭐⭐ | Varied | 2015–2015 | A list of Capture The Flag (CTF) frameworks, libraries, resources and software for started/experienced CTF players - de… |
| 16 | [david942j/ctf-writeups](https://github.com/david942j/ctf-writeups) | 322 ⭐⭐⭐ | Varied | 2016–2021 | Collection of scripts and writeups. Contribute to david942j/ctf-writeups development by creating an account on GitHub. |
| 17 | [LiveOverflow/pwn_docker_example](../01-pwn/mirrors/pwn_docker_example) | 230 ⭐⭐ | Varied | n/a | We used this code to run a challenge in a server setup with docker, and then use a docker container as a CTF OS to writ… |
| 18 | [project-sekai-ctf/sekaictf-2025](../20-events/mirrors/sekaictf/sekaictf-2025) | 135 ⭐⭐ | Advanced | 2024–2025 | This repository contains official source code and writeups for challenges from SekaiCTF 2025. CTFTime • Website • Disco… |
| 19 | [JohnHammond/miscellaneous](../07-misc/mirrors/miscellaneous) | 84 ⭐⭐ | Varied | 2013–2016 | The purpose of this repository is to archive any extraneous documents, or anything else that really has no specific cat… |
| 20 | [project-sekai-ctf/sekaictf-2024](https://github.com/project-sekai-ctf/sekaictf-2024) | 83 ⭐⭐ | Advanced | 2024–2024 | This repository contains official source code and writeups for challenges from SekaiCTF 2024. CTFTime Event • Website •… |
| 21 | [mephi42/ctf](https://github.com/mephi42/ctf) | 76 ⭐⭐ | Varied | 2019–2024 | My writeups and solutions from various CTFs. Capturing flags with More Smoked Leet Chicken since 2019. |
| 22 | [D4mianWayne/PwnLand](../01-pwn/mirrors/PwnLand) | 62 ⭐⭐ | Varied | 2020–2025 | Knowledge Base of Exploitation Techniques. Contribute to pwnfuzz/exploitation-grimoire development by creating an accou… |
| 23 | [pwncollege/linux-luminarium](../20-events/mirrors/pwn-college/linux-luminarium) | 52 ⭐⭐ | Beginner | n/a | This is a pwn.college dojo built around teaching basic Linux knowledge, through hands-on challenges, from absolutely no… |
| 24 | [kayranfatih/awesome-iot-and-hardware-security](../30-archetypes/mirrors/awesome-lists/awesome-iot-and-hardware-security) | 46 ⭐ | Varied | 2015–2026 | A collection of awesome tools, books, resources, software, documents and cool stuff about Internet of Things (IoT) and … |
| 25 | [sigpwny/UIUCTF-2023-Public](https://github.com/sigpwny/UIUCTF-2023-Public) | 39 ⭐ | Varied | 2023–2023 | This is the repository for all UIUCTF 2023 challenges and infrastructure. This is an exact copy of our development repo… |
| 26 | [JohnHammond/misfortune-ctf-challenge](../07-misc/mirrors/misfortune-ctf-challenge) | 34 ⭐ | Varied | 2023–2023 | A small binary exploitation challenge to demonstrate a typical return2libc attack - JohnHammond/misfortune-ctf-challeng… |
| 27 | [pwncollege/challenges](../20-events/mirrors/pwn-college/challenges) | 33 ⭐ | Beginner | n/a | This repository will one day contain all core pwn.college challenges. The basic idea is that challenges are just direct… |
| 28 | [Sudoite/ctf-writeups](../30-archetypes/mirrors/personal-collections/ctf-writeups-Sudoite) | 27 ⭐ | Varied | 2016–2019 | This is a repository of writeups for various CTF challenges. I am intentionally leaving in discussion about where I mad… |
| 29 | [justcatthefish/justctf-2023](https://github.com/justcatthefish/justctf-2023) | 21 ⭐ | Elite | 2023–2023 | This repo contains sources for justCTF 2023 challenges hosted by justCatTheFish as well as summary of winners and spons… |
| 30 | [dicegang/dicectf-quals-2025-challenges](https://github.com/dicegang/dicectf-quals-2025-challenges) | 9 ⭐ | Elite | 2025–2025 | All challenges from DiceCTF Quals 2025. Contribute to dicegang/dicectf-quals-2025-challenges development by creating an… |


## ✍️ Curated Articles & Walkthroughs

Beyond GitHub repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) | ✍️ Medium | n/a | This is a walkthrough article for the binary exploitation/PWN challenges from RVCExIITB CTF competition. There were onl… |
| 2 | [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) | ▶️ YouTube | 2021–2021 | Video walkthrough for the "Name Server" Pwn (binary exploitation) challenge from the Tamil CTF 2021. We'll exploit this… |
| 3 | [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) | ✍️ Medium | n/a | This writeup documents the analysis, methodology, and technical findings for seven complex challenges completed during … |
| 4 | [Pwn Challenges CTF 2025 [binary Exploiation] | by livepwn - Medium](https://livepwn.medium.com/pwn-challenges-ctf-2025-binary-exploiation-c0ce691b9451) | ✍️ Medium | 2025–2025 | I started learning pwn (binary exploiation). There are some cool challenges that also help you to solve some easy pwn c… |
| 5 | [pwnable.kr - bof - 0xRick's Blog](https://0xrick.github.io/pwn/bof) | 📝 Blog | n/a | It was a simple easy buffer overflow challenge (You can also check these), by overwriting a variable we can get a shell… |
| 6 | [PlaidCTF 2023 Writeups - siunam's Website](https://siunam321.github.io/ctf/PlaidCTF-2023) | 📝 Blog | 2023–2023 | The Plaid Flag is the 2023 edition of PlaidCTF, an annual capture the flag competition run by PPP. Categories: web; rev… |
| 7 | [pwn.college](https://pwn.college) | 📝 Blog | n/a | Some of the modules are closed-source, because they include source code and solution scripts, but others can be found o… |
| 8 | [PWN : Return To Win(ret2win)| Binary exponentiation for beginners](https://medium.com/@fahimalshihabifty/pwn-return-to-win-ret2win-binary-exponentiation-for-beginners-1de7e0fc85cc) | ✍️ Medium | n/a | In this post, I'll walk you through a writeup on Return-to-Win exploits and their variations. These techniques are comm… |
| 9 | [csawctf{CSAW-CTF-24} - Medium](https://medium.com/@iabdullah_215/csawctf-csaw-ctf-24-a8fd8082f944) | ✍️ Medium | n/a | This blog has the write-up for a PWN challenge that I solved in the CSAW CTF'24. So without any further a do. Let's get… |
| 10 | [ICTF 2025 Writeup - Medium](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | ✍️ Medium | 2025–2025 | It was an exciting competition with a diverse range of challenges spanning forensics, steganography, web exploitation, … |
| 11 | [Decode-E-Cyber CTF 2023 — PWN/Binary Exploitation Writeup — 2](https://febinj.medium.com/decode-e-cyber-ctf-2023-pwn-binary-exploitation-writeup-1-3e4c93a01dd1) | ✍️ Medium | 2023–2023 | The binary has no stack cookie, and the NX (non-executable stack) is disabled, so we can exploit buffer overflow(if the… |
| 12 | [DiceCTF 2024 Quals - Chovid99's Blog](https://chovid99.github.io/posts/dicectf-2024-quals) | 📝 Blog | 2024–2024 | Below is the writeup for the pwn challenges that I managed to solve. Pwn. hop. Description. Using 32 bits to encode a s… |
| 13 | [Google CTF 2025 - Chovid99's Blog](https://chovid99.github.io/posts/google-ctf-2025) | 📝 Blog | 2025–2025 | So, this time, I will share my writeup for the unicornel trustzone challenge. Pwn. Unicornel Trustzone. Description. Un… |
| 14 | [GitEx CTF Pwn — Buffer Overflow Writeup | by Libc - Medium](https://medium.com/@0xk4g3/gitex-ctf-pwn-buffer-overflow-writeup-6d261fcfb5bc) | ✍️ Medium | n/a | GitEx CTF Pwn — Buffer Overflow Writeup Challenge Overview This was a classic stack buffer overflow challenge from GitE… |
| 15 | [Try Hack Me Industrial Intrusion CTF Writeup: Buffer Overflow Exploit](https://medium.com/@michaelkhanda/try-hack-me-industrial-intrusion-ctf-writeup-buffer-overflow-exploit-on-start-binary-2d54e6df3688) | ✍️ Medium | n/a | Challenge Theme: Industrial OT Intrusion Recovery Category: Pwn. Challenge Context. Three months after a malware attack… |
| 16 | [Binary Exploitation (Pwn) Challenge Walkthroughs - YouTube](https://www.youtube.com/watch?v=xOHLniVJsJY) | ▶️ YouTube | 2021–2021 | Video walkthrough for Binary Exploitation (pwn) challenges from the Killer Queen 2021 Capture The Flag (CTF). We'll cov… |
| 17 | [Day 25: buffer overflow 0 — picoCTF Binary Exploitation Writeup](https://medium.com/@siyam.exe/day-25-buffer-overflow-0-picoctf-binary-exploitation-writeup-def18015cbb1) | ✍️ Medium | n/a | A first step into picoCTF binary exploitation, where spamming A's somehow became a legitimate strategy. Today, we are s… |
| 18 | [Pwnable.kr — bof - Shellbr3ak - Medium](https://shellbr3ak.medium.com/pwnable-kr-bof-d78f3ed36747) | ✍️ Medium | n/a | Pwnable.kr — bof What's going on aspiring hackers, this is shellbreak, and today we'll be doing a simple buffer overflo… |
| 19 | [TsukuCTF 2025 Writeups - r1ru](https://r1ru.github.io/posts/7) | 📝 Blog | 2025–2025 | At TsukuCTF 2025, I created three kernel pwn challenges. It was my first time creating CTF challenges, but I learned a … |
| 20 | [pwncollege: Dealing with Data. pwn college dealing with data room | by Sourav B…](https://medium.com/@souravbose361/pwn-college-dealing-with-data-1d7bac04c1a4) | ✍️ Medium | n/a | Let's start your journey through encodings with something simple. This program takes a password, but you have no way to… |
| 21 | [HTB x Synack RedTeamFive Capture The Flag (CTF) 2021 - YouTube](https://www.youtube.com/watch?v=Kqu3qpYMml8) | ▶️ YouTube | 2021–2021 | Video walkthrough for Binary Exploitation (pwn) challenges from the "Hack The Box x Synack: 2021 Edition Capture The Fl… |
| 22 | [Walkthrough of bof level in pwnable.kr - YouTube](https://www.youtube.com/watch?v=rwfKScdQybE) | ▶️ YouTube | n/a | Walkthrough of the solution to the bof level in the http://pwnable.kr online wargames. More information about me on my … |
| 23 | [Beginner Buffer Overflow! - pwnable.kr bof walkthrough - YouTube](https://www.youtube.com/watch?v=3TBdVE9upqo) | ▶️ YouTube | n/a | Exploiting a simple binary buffer overflow in a Linux x86 binary to gain a shell on target! ==== Social Media ==== Disc… |
| 24 | [How I Became the “Reverse Guy” in My CTF Team | by Rusty - Medium](https://rustybladez.medium.com/how-i-became-the-reverse-guy-in-my-ctf-team-c6fc2cef1512) | ✍️ Medium | n/a | I thought I'd become an all-rounder. Binary Exploitation, Cryptography, Forensics, OSINT, Reverse Engineering, you call… |
| 25 | [CSAW CTF 2023 Writeup - tripoloski blog](https://tripoloski1337.github.io/ctf/pwn/uaf/heap/2023/09/18/csawctf2023-writeup.html) | 📝 Blog | 2023–2023 | I competed on CSAW CTF 2023, and I solved multiple challenges e.g. from pwn, incident response and reverse engineering. |
| 26 | [DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn)](https://www.youtube.com/watch?v=CGbPWSVm99k) | ▶️ YouTube | 2024–2024 | DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn) · Comments. |

## 🔬 Sub-Topic Deep Dive

The Binary Exploitation category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Stack-based exploitation

buffer overflows, off-by-one, stack canary bypass, ROP.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - GitHub](../30-archetypes/mirrors/personal-collections/ctf-writeups-merrychap) — 🐙 GitHub Repo
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [PwnLand - GitHub](../01-pwn/mirrors/PwnLand) — 🐙 GitHub Repo
- [GitHub - JohnHammond/misfortune-ctf](../07-misc/mirrors/misfortune-ctf-challenge) — 🐙 GitHub Repo

### Heap exploitation

use-after-free, double-free, fastbin/unbin/tcache attacks, House of Force/Spirit/Einherjar/etc..

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - GitHub](../30-archetypes/mirrors/personal-collections/ctf-writeups-merrychap) — 🐙 GitHub Repo
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [PwnLand - GitHub](../01-pwn/mirrors/PwnLand) — 🐙 GitHub Repo
- [GitHub - JohnHammond/misfortune-ctf](../07-misc/mirrors/misfortune-ctf-challenge) — 🐙 GitHub Repo

### Format string attacks

arbitrary read/write via printf-family functions.

*No directly-matching resources in this collection — consult the broader category list above.*

### Kernel pwn

Linux kernel exploitation: SLUB allocator, msg_msg, pipe_buffer, struct-file abuse.

Top resources for this sub-topic:

- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - GitHub](../30-archetypes/mirrors/personal-collections/CTF-CryptoCat) — 🐙 GitHub Repo
- [Yet another CTF writeups repository. PWN and RE tasks - GitHub](../30-archetypes/mirrors/personal-collections/ctf-writeups-merrychap) — 🐙 GitHub Repo
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium

### Exploit mitigations

ASLR, NX, PIE, RELRO, stack canaries, CFI.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - GitHub](../30-archetypes/mirrors/personal-collections/ctf-writeups-merrychap) — 🐙 GitHub Repo
- [Pwn Challenges writeup — RVCExIITB CTF | by Febin - Medium](https://febinj.medium.com/pwn-challenges-writeup-rvcexiitb-ctf-b62ccc2c68c7) — ✍️ Medium
- [Name Server [Tamil CTF] - Binary Exploitation (Pwn) Walkthrough](https://www.youtube.com/watch?v=Q5Xx3aM0cUE) — ▶️ YouTube
- [LiveOverflow/pwn_docker_example: Example pwnable challenge hosted](../01-pwn/mirrors/pwn_docker_example) — 🐙 GitHub Repo
- [PwnLand - GitHub](../01-pwn/mirrors/PwnLand) — 🐙 GitHub Repo

### ARM / RISC-V pwn

exploitation on non-x86 architectures; common in IoT challenges.

Top resources for this sub-topic:

- [r3kapig/writeup: CTF challenges writeup - GitHub](../30-archetypes/mirrors/team-archives/writeup-r3kapig) — 🐙 GitHub Repo
- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - GitHub](../30-archetypes/mirrors/awesome-lists/awesome-ctf) — 🐙 GitHub Repo
- [Hack The Box Writeups - The Ultimate HTB Resource - GitHub](../20-events/mirrors/hackthebox/htb-writeups) — 🐙 GitHub Repo
- [orangetw/My-CTF-Web-Challenges - GitHub](../02-web/mirrors/My-CTF-Web-Challenges) — 🐙 GitHub Repo
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - GitHub](../30-archetypes/mirrors/personal-collections/CTF-CryptoCat) — 🐙 GitHub Repo


## 🎯 Suggested Learning Order

If you're new to binary exploitation, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [pwn.college](https://pwn.college/) — the canonical structured pwn learning path. Work through 'Program Misuse' → 'Shellcode Injection' → 'Sandboxing' → 'System Shell' → 'Shellcode Injection II' → 'Dynamic Allocator Misuse' → 'Heap Exploitation' → 'Kernel Exploitation'.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal GitHub repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
