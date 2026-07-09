# Reverse Engineering

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Static and dynamic analysis of native binaries, obfuscated scripts, custom virtual machines, and increasingly LLVM IR, WebAssembly, and exotic architectures. The tooling stack is dominated by Ghidra (free), IDA Pro (commercial), Binary Ninja, angr (symbolic execution), and gdb-gef.

This category contains **64 curated sources** from across the CTF ecosystem: 52 GitHub repositories, 9 Medium articles, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 3 blog posts.

## 🏆 Recommended Repositories (GitHub)

The following GitHub repositories are the highest-value resources for this category. They are ranked by cross-search relevance, mention count, and star count.

| # | Repository | Stars | Difficulty | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | [apsdehal/awesome-ctf (local mirror)](../repos/apsdehal/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Beginner | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials. This list aims to h… |
| 2 | [blockthreat/blocksec-ctfs (local mirror)](../repos/blockthreat/blocksec-ctfs) | 1,632 ⭐⭐⭐⭐ | Varied | 2017–2023 | A curated list of blockchain security Wargames, Challenges, and Capture the Flag (CTF) competitions and solution writeu… |
| 3 | [minaminao/ctf-blockchain (local mirror)](../repos/minaminao/ctf-blockchain) | 1,084 ⭐⭐⭐⭐ | Elite | 2018–2025 | This repository collects blockchain challenges in CTFs and wargames. Some of them include personal writeups and solutio… |
| 4 | [momenbasel/htb-writeups (local mirror)](../repos/momenbasel/htb-writeups) | 152 ⭐⭐ | Varied | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactive knowledge graph, s… |
| 5 | [Crypto-Cat/CTF (local mirror)](../repos/Crypto-Cat/CTF) | 2,512 ⭐⭐⭐⭐ | Varied | 2026–2026 | CTF challenge write-ups, files, scripts etc to go with my video walkthroughs. Check out my blog and discord server. A c… |
| 6 | [xtiankisutsa/awesome-mobile-ctf (local mirror)](../repos/xtiankisutsa/awesome-mobile-ctf) | 1,157 ⭐⭐⭐⭐ | Varied | 2013–2022 | This is a curated list of mobile based CTFs, write-ups and vulnerable mobile apps. Most of them are android based due t… |
| 7 | [Adamkadaban/CTFs](https://github.com/Adamkadaban/CTFs) | 840 ⭐⭐⭐ | Varied | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types of challenges: https:… |
| 8 | [Kasimir123/CTFWriteUps](https://github.com/Kasimir123/CTFWriteUps) | 61 ⭐⭐ | Varied | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains all source files if th… |
| 9 | [tim-barc/ctf_writeups (local mirror)](../repos/tim-barc/ctf_writeups) | 43 ⭐ | Varied | 2019–2025 | Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to solve various Capture T… |
| 10 | [merrychap/ctf-writeups (local mirror)](../repos/merrychap/ctf-writeups) | 36 ⭐ | Varied | n/a | All writeups are about Reverse Engineering and Binary Exploitation tasks. No crypto, forensics, and others. I'm not spe… |
| 11 | [SandWithCheese/ctf-writeups](https://github.com/SandWithCheese/ctf-writeups) | 14 ⭐ | Beginner | n/a | Welcome to my CTF (Capture The Flag) writeups repository! This repository contains solutions for various CTF challenges… |
| 12 | [tl2cents/CTF-Writeups (local mirror)](../repos/tl2cents/CTF-Writeups) | 5 ⭐ | Varied | 2024–2025 | Archive writeups or exploits of ctf challenges, mainly crypto and blockchain. Detailed writeups can be found in my blog… |
| 13 | [JohnHammond/ctf-katana (local mirror)](../repos/JohnHammond/ctf-katana) | 2,920 ⭐⭐⭐⭐ | Varied | 2015–2020 | This repository aims to hold suggestions (and hopefully/eventually code) for CTF challenges. The "project" is nicknamed… |
| 14 | [hackthebox/cyber-apocalypse-2025 (local mirror)](../repos/hackthebox/cyber-apocalypse-2025) | 200 ⭐⭐ | Intermediate | 2025–2025 | Official writeups for Cyber Apocalypse CTF 2025: Tales from Eldoria. Questionnaire about finite fields and elliptic cur… |
| 15 | [dicegang/dicectf-quals-2024-challenges](https://github.com/dicegang/dicectf-quals-2024-challenges) | 30 ⭐ | Elite | 2024–2024 | All challenges from DiceCTF Quals 2024. Contribute to dicegang/dicectf-quals-2024-challenges development by creating an… |
| 16 | [fkie-cad/awesome-embedded-and-iot-security (local mirror)](../repos/fkie-cad/awesome-embedded-and-iot-security) | 2,349 ⭐⭐⭐⭐ | Varied | 2013–2020 | A curated list of awesome resources about embedded and IoT security. The list contains software and hardware tools, boo… |
| 17 | [hackplayers/hackthebox-writeups](https://github.com/hackplayers/hackthebox-writeups) | 2,044 ⭐⭐⭐⭐ | Intermediate | 2017–2023 | Writeups for HacktheBox 'boot2root' machines. Contribute to Hackplayers/hackthebox-writeups development by creating an … |
| 18 | [ctfs/resources](https://github.com/ctfs/resources) | 1,819 ⭐⭐⭐⭐ | Beginner | n/a | This repository aims to be an archive of information, tools, and references regarding CTF competitions. CTFs, especiall… |
| 19 | [JohnHammond/katana (local mirror)](../repos/JohnHammond/katana) | 1,359 ⭐⭐⭐⭐ | Varied | 2019–2019 | This repository attempts to offer code and material to automate running through the check-list or hitting the low-hangi… |
| 20 | [devploit/awesome-ctf-resources (local mirror)](../repos/devploit/awesome-ctf-resources) | 777 ⭐⭐⭐ | Varied | 2015–2015 | A list of Capture The Flag (CTF) frameworks, libraries, resources and software for started/experienced CTF players - de… |
| 21 | [j00ru/ctf-tasks (local mirror)](../repos/j00ru/ctf-tasks) | 656 ⭐⭐⭐ | Varied | 2013–2021 | This repository contains an archive of CTF challenges I developed in the last few years for various CTFs organized by m… |
| 22 | [david942j/ctf-writeups](https://github.com/david942j/ctf-writeups) | 322 ⭐⭐⭐ | Varied | 2016–2021 | Collection of scripts and writeups. Contribute to david942j/ctf-writeups development by creating an account on GitHub. |
| 23 | [neutrinoguy/awesome-ics-writeups (local mirror)](../repos/neutrinoguy/awesome-ics-writeups) | 201 ⭐⭐ | Varied | 2013–2025 | A collection of writeups related to ICS/SCADA hacking. This covers areas like OT, IoT and IIoT. It includes exploitatio… |
| 24 | [project-sekai-ctf/sekaictf-2025 (local mirror)](../repos/project-sekai-ctf/sekaictf-2025) | 135 ⭐⭐ | Advanced | 2024–2025 | This repository contains official source code and writeups for challenges from SekaiCTF 2025. CTFTime • Website • Disco… |
| 25 | [JohnHammond/miscellaneous (local mirror)](../repos/JohnHammond/miscellaneous) | 84 ⭐⭐ | Varied | 2013–2016 | The purpose of this repository is to archive any extraneous documents, or anything else that really has no specific cat… |
| 26 | [project-sekai-ctf/sekaictf-2024](https://github.com/project-sekai-ctf/sekaictf-2024) | 83 ⭐⭐ | Advanced | 2024–2024 | This repository contains official source code and writeups for challenges from SekaiCTF 2024. CTFTime Event • Website •… |
| 27 | [mephi42/ctf](https://github.com/mephi42/ctf) | 76 ⭐⭐ | Varied | 2019–2024 | My writeups and solutions from various CTFs. Capturing flags with More Smoked Leet Chicken since 2019. |
| 28 | [D4mianWayne/PwnLand (local mirror)](../repos/D4mianWayne/PwnLand) | 62 ⭐⭐ | Varied | 2020–2025 | Knowledge Base of Exploitation Techniques. Contribute to pwnfuzz/exploitation-grimoire development by creating an accou… |
| 29 | [noamgariani11/picoCTF-2024-Writeup (local mirror)](../repos/noamgariani11/picoCTF-2024-Writeup) | 57 ⭐⭐ | Beginner | 2024–2024 | picoCTF 2024 solutions are all searchable and easy to explore step-by-step writeups and use the built-in tools develope… |
| 30 | [kayranfatih/awesome-iot-and-hardware-security (local mirror)](../repos/kayranfatih/awesome-iot-and-hardware-security) | 46 ⭐ | Varied | 2015–2026 | A collection of awesome tools, books, resources, software, documents and cool stuff about Internet of Things (IoT) and … |


## ✍️ Curated Articles & Walkthroughs

Beyond GitHub repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

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

- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - GitHub (local mirror)](../repos/apsdehal/awesome-ctf) — 🐙 GitHub Repo
- [blockthreat/blocksec-ctfs - GitHub (local mirror)](../repos/blockthreat/blocksec-ctfs) — 🐙 GitHub Repo
- [Hack The Box Writeups - The Ultimate HTB Resource - GitHub (local mirror)](../repos/momenbasel/htb-writeups) — 🐙 GitHub Repo
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - GitHub (local mirror)](../repos/Crypto-Cat/CTF) — 🐙 GitHub Repo
- [GitHub - xtiankisutsa/awesome-mobile-CTF (local mirror)](../repos/xtiankisutsa/awesome-mobile-ctf) — 🐙 GitHub Repo

### Custom VMs

bytecode-based challenge binaries with custom instruction sets.

Top resources for this sub-topic:

- [gijsh/rhme2_writeups: Writeups for the RHME2 CTF - GitHub (local mirror)](../repos/gijsh/rhme2_writeups) — 🐙 GitHub Repo
- [BarakBinyamin/ctf: Some embedded network attacks  - GitHub (local mirror)](../repos/BarakBinyamin/ctf) — 🐙 GitHub Repo

### Obfuscated scripts

PyArmor, py2exe, Lua bytecode, JavaScript obfuscation.

Top resources for this sub-topic:

- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - GitHub (local mirror)](../repos/Crypto-Cat/CTF) — 🐙 GitHub Repo
- [GitHub - david942j/ctf-writeups: Collection of scripts and writeups](https://github.com/david942j/ctf-writeups) — 🐙 GitHub Repo
- [kyndrawynne/pwnscripts - GitHub (local mirror)](../repos/kyndrawynne/pwnscripts) — 🐙 GitHub Repo

### LLVM IR / WebAssembly

modern obfuscation targets.

Top resources for this sub-topic:

- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - GitHub (local mirror)](../repos/apsdehal/awesome-ctf) — 🐙 GitHub Repo
- [blockthreat/blocksec-ctfs - GitHub (local mirror)](../repos/blockthreat/blocksec-ctfs) — 🐙 GitHub Repo
- [Hack The Box Writeups - The Ultimate HTB Resource - GitHub (local mirror)](../repos/momenbasel/htb-writeups) — 🐙 GitHub Repo
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - GitHub (local mirror)](../repos/Crypto-Cat/CTF) — 🐙 GitHub Repo
- [GitHub - xtiankisutsa/awesome-mobile-CTF (local mirror)](../repos/xtiankisutsa/awesome-mobile-ctf) — 🐙 GitHub Repo

### Anti-reverse engineering

anti-debug, anti-VM, anti-disassembly tricks.

Top resources for this sub-topic:

- [Kasimir123/CTFWriteUps: Collection of CTF Writeups for  - GitHub](https://github.com/Kasimir123/CTFWriteUps) — 🐙 GitHub Repo
- [Yet another CTF writeups repository. PWN and RE tasks - GitHub (local mirror)](../repos/merrychap/ctf-writeups) — 🐙 GitHub Repo
- [1GN1tE/CTF_Writeups: Writeups of some Reverse Engineering](https://github.com/1GN1tE/CTF_Writeups) — 🐙 GitHub Repo
- [docfate111/binary_exploitation: CTF/hacking challenge  - GitHub (local mirror)](../repos/docfate111/binary_exploitation) — 🐙 GitHub Repo


## 🎯 Suggested Learning Order

If you're new to reverse engineering, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [pwn.college RE module](https://pwn.college/) — then reverse-engineer 5–10 [CrackMe challenges](https://crackmes.one/).

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal GitHub repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
