# Forensics & Steganography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Disk-image forensics, memory-dump analysis (Volatility), packet-capture analysis (Wireshark/tshark), and steganography (Aperi'Solve, zsteg, stegsolve). The category with the highest variance in challenge design — challenges range from trivial 'find the hidden flag in metadata' to sophisticated memory-malware-investigation scenarios.

This category contains **42 curated sources** from across the CTF ecosystem: 30 the collection repositories, 7 Medium articles, 0 YouTube video walkthroughs, 1 CTFtime event entries, and 4 blog posts.

## 🏆 Recommended Repositories (the collection)

The following the collection repositories are the highest-value resources for this category. They are ranked by cross-search relevance, mention count, and star count.

| # | Repository | Stars | Difficulty | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | [r3kapig/writeup](../30-archetypes/archives/team-archives/writeup-r3kapig) | 188 ⭐⭐ | Varied | 2018–2022 | CTF challenges writeup. r3kapig is a united CTF Team. We are publishing our official writeups here. The writeup page is… |
| 2 | [apsdehal/awesome-ctf](../30-archetypes/archives/awesome-lists/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Beginner | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials. This list aims to h… |
| 3 | [momenbasel/htb-writeups](../20-events/archives/hackthebox/htb-writeups) | 152 ⭐⭐ | Varied | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactive knowledge graph, s… |
| 4 | [Crypto-Cat/CTF](../30-archetypes/archives/personal-collections/CTF-CryptoCat) | 2,512 ⭐⭐⭐⭐ | Varied | 2026–2026 | CTF challenge write-ups, files, scripts etc to go with my video walkthroughs. Check out my blog and discord server. A c… |
| 5 | [xtiankisutsa/awesome-mobile-ctf](../30-archetypes/archives/awesome-lists/awesome-mobile-ctf) | 1,157 ⭐⭐⭐⭐ | Varied | 2013–2022 | This is a curated list of mobile based CTFs, write-ups and vulnerable mobile apps. Most of them are android based due t… |
| 6 | Adamkadaban/CTFs | 840 ⭐⭐⭐ | Varied | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types of challenges: https:… |
| 7 | Kasimir123/CTFWriteUps | 61 ⭐⭐ | Varied | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains all source files if th… |
| 8 | [tim-barc/ctf_writeups](../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | 43 ⭐ | Varied | 2019–2025 | Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to solve various Capture T… |
| 9 | [merrychap/ctf-writeups](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) | 36 ⭐ | Varied | n/a | All writeups are about Reverse Engineering and Binary Exploitation tasks. No crypto, forensics, and others. I'm not spe… |
| 10 | Tan-JunWei/CTF-Writeups | 15 ⭐ | Varied | n/a | Welcome to my Capture The Flag (CTF) writeup repository! Here you'll find detailed explanations and solutions to variou… |
| 11 | [JohnHammond/ctf-katana](../30-archetypes/archives/awesome-lists/ctf-katana) | 2,920 ⭐⭐⭐⭐ | Varied | 2015–2020 | This repository aims to hold suggestions (and hopefully/eventually code) for CTF challenges. The "project" is nicknamed… |
| 12 | [hackthebox/cyber-apocalypse-2025](../20-events/archives/hackthebox/cyber-apocalypse-2025) | 200 ⭐⭐ | Intermediate | 2025–2025 | Official writeups for Cyber Apocalypse CTF 2025: Tales from Eldoria. Questionnaire about finite fields and elliptic cur… |
| 13 | [dominicbreuker/stego-toolkit](../40-tooling/archives/forensics-tools/stego-toolkit) | 2,675 ⭐⭐⭐⭐ | Intermediate | n/a | This project is a Docker image useful for solving Steganography challenges as those you can find at CTF platforms like … |
| 14 | hackplayers/hackthebox-writeups | 2,044 ⭐⭐⭐⭐ | Intermediate | 2017–2023 | Writeups for HacktheBox 'boot2root' machines. Contribute to Hackplayers/hackthebox-writeups development by creating an … |
| 15 | [devploit/awesome-ctf-resources](../30-archetypes/archives/awesome-lists/awesome-ctf-resources) | 777 ⭐⭐⭐ | Varied | 2015–2015 | A list of Capture The Flag (CTF) frameworks, libraries, resources and software for started/experienced CTF players - de… |
| 16 | [neutrinoguy/awesome-ics-writeups](../30-archetypes/archives/awesome-lists/awesome-ics-writeups) | 201 ⭐⭐ | Varied | 2013–2025 | A collection of writeups related to ICS/SCADA hacking. This covers areas like OT, IoT and IIoT. It includes exploitatio… |
| 17 | [JohnHammond/miscellaneous](../07-misc/archives/miscellaneous) | 84 ⭐⭐ | Varied | 2013–2016 | The purpose of this repository is to archive any extraneous documents, or anything else that really has no specific cat… |
| 19 | [kayranfatih/awesome-iot-and-hardware-security](../30-archetypes/archives/awesome-lists/awesome-iot-and-hardware-security) | 46 ⭐ | Varied | 2015–2026 | A collection of awesome tools, books, resources, software, documents and cool stuff about Internet of Things (IoT) and … |
| 20 | [Sudoite/ctf-writeups](../30-archetypes/archives/personal-collections/ctf-writeups-Sudoite) | 27 ⭐ | Varied | 2016–2019 | This is a repository of writeups for various CTF challenges. I am intentionally leaving in discussion about where I mad… |
| 21 | [hagronnestad/ctf-htb-cyber-apocalypse-2024](../20-events/archives/hackthebox/cyber-apocalypse-2024) | 6 ⭐ | Intermediate | 2024–2024 | HackTheBox CTF Cyber Apocalypse 2024: No fighting, no backstabbing, and no factions fighting Phreaks) A societal gauntl… |
| 23 | [cHo0s3N/JustCTF](../20-events/archives/justctf/JustCTF) | 6 ⭐ | Elite | 2019–2019 | writeups! #JUSTCTF. Contribute to cHo0s3N/JustCTF development by creating an account. |
| 24 | [snwau/picoCTF-2025-Writeup](../20-events/archives/picoctf/picoCTF-2025-Writeup) | 5 ⭐ | Beginner | 2025–2025 | Explore the the collection Discussions forum for snwau picoCTF-2025-Writeup. Discuss code, ask questions & collaborate with the… |
| 25 | [0xETX/CTF-Writeups](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) | 4  | Varied | 2021–2023 | Writeups for CTF challenges I have completed in the past. Contains different challenge categories such as Programming, … |
| 26 | [MacacaHub/CTF-writeups](../30-archetypes/archives/personal-collections/CTF-writeups-MacacaHub) | 4  | Varied | 2019–2021 | 2021. BambooFox CTF 2021; HTCF Mid CTF 2021 (only for NSYSU course) · 2020. TCat CTF 2020; TJCTF 2020; HTCF Mid CTF 202… |
| 27 | [stefanman125/root-me-challenges](../30-archetypes/archives/practice-platforms/root-me-challenges) | 4  | Varied | n/a | This is a Write-up for the CTF website root-me. It features challenges in various categories, such as Forensics, Crypta… |
| 28 | [tsids/picoCTF-Writeups](../20-events/archives/picoctf/picoCTF-Writeups-tsids) | 1  | Beginner | 2019–2026 | Navigate to the folder of the challenge you are looking for, and the solution can be found in <Challenge Title>.md. Fee… |
| 29 | [rstacks/corCTF2024-writeup](../20-events/archives/corctf/corCTF2024-writeup) | 0  | Advanced | 2024–2024 | corCTF 2024 was a 48 hour competition that ran from 7/26/2024 through 7/28/2024. Below are my writeups for the challeng… |
| 30 | silly-lily/CTF-Writeups | 0  | Varied | 2022–2026 | Writeups for CTFs. Contribute to silly-lily/CTF-Writeups development by creating an account. |


## ✍️ Curated Articles & Walkthroughs

Beyond the collection repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) | ✍️ Medium | n/a | This writeup documents the analysis, methodology, and technical findings for seven complex challenges completed during … |
| 2 | [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) | 📝 Blog | n/a | Writeup - ComCyber Recrutement CTF · Step 1 - Network · Step 2 - Web · Step 3 - Forensic · Step 4 - Steganography · Ste… |
| 3 | [TCP1P CTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/tcp1pctf2024) | 📝 Blog | 2024–2024 | This is a writeup for some forensics challenges from TCP1P CTF 2024. Again, L3ak forensics team managed to full clear t… |
| 4 | [DownUnderCTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/ductf2024) | 📝 Blog | 2024–2024 | This is a writeup for all forensics challenges from DownUnderCTF 2024. Overall, an extremely enjoyable CTF with great c… |
| 5 | [Forensics & Steganography Challenges — CTF Writeups](https://medium.com/@santhoshr3512/forensics-steganography-challenges-ctf-writeups-0f71112ddf4a) | ✍️ Medium | n/a | This challenge shows how visual cryptography can hide data across multiple images. Individually the images appear as ra… |
| 6 | [ICTF 2025 Writeup - Medium](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | ✍️ Medium | 2025–2025 | It was an exciting competition with a diverse range of challenges spanning forensics, steganography, web exploitation, … |
| 7 | [CTFtime.org / ImaginaryCTF 2024 / Crash / Writeup](https://ctftime.org/writeup/39341) | 🏆 CTFtime | 2024–2024 | CTF writeups, Crash. ... Original writeup (https://medium.com/@zeroair41/solving-the-crash-forensics-challenge-on-imagi… |
| 8 | [Midnight Flag CTF Writeups (Forensics, Web3, Crypto, Reverse)](https://medium.com/@shoaibbinrashid11/midnight-flag-ctf-writeups-forensics-web3-crypto-reverse-9e8e49e36153) | ✍️ Medium | n/a | The solver uses an Overbeck-style method to remove the “distortion” and decode. · The decoded message becomes an AES ke… |
| 9 | [idek CTF 2022* Forensics - HiddenGem Mixtape Writeup](https://crazymanarmy.github.io/2023/01/16/idek-CTF-2022-Forensics-HiddenGem-Mixtape-Writeup/index.html) | 📝 Blog | 2022–2022 | Note 1: All flags are wrapped in idek{} format, you don't need to do it yourself. Note 2: The zip file is the same for … |
| 10 | [CyberSpace CTF 2024 Reverse Engineering Challenges - Medium](https://medium.com/@ELJoOker/cyberspace-ctf-2024-reverse-engineering-challenges-4226b9055547) | ✍️ Medium | 2024–2024 | This write-up is for some of the Reverse Engineering and Forensics challenges that I've solved in the NahamCon CTF… A c… |
| 11 | [Writeup for PicoCTF 2022 | by Archit Vats - Medium](https://medium.com/@architvats96/writeup-for-picoctf-2022-ctftime-336a6cce9f38) | ✍️ Medium | 2022–2022 | This writeup has the solutions for the following challenges: Forensics (Enhance, Lookey Here, Packets Primer, Redaction… |
| 12 | [How I Became the “Reverse Guy” in My CTF Team | by Rusty - Medium](https://rustybladez.medium.com/how-i-became-the-reverse-guy-in-my-ctf-team-c6fc2cef1512) | ✍️ Medium | n/a | I thought I'd become an all-rounder. Binary Exploitation, Cryptography, Forensics, OSINT, Reverse Engineering, you call… |

## 🔬 Sub-Topic Deep Dive

The Forensics & Steganography category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Disk image forensics

TSK, Autopsy, file carving.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [DominicBreuker/stego-toolkit: Collection of steganography tools](../40-tooling/archives/forensics-tools/stego-toolkit) — 📚 Repository
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository

### Memory forensics

Volatility — process list, network connections, malware extraction.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [TCP1P CTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/tcp1pctf2024) — 📝 Blog

### Steganography

LSB, audio stego, spectral stego, steghide, zsteg.

Top resources for this sub-topic:

- [DominicBreuker/stego-toolkit: Collection of steganography tools](../40-tooling/archives/forensics-tools/stego-toolkit) — 📚 Repository
- [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) — 📝 Blog
- [Forensics & Steganography Challenges — CTF Writeups](https://medium.com/@santhoshr3512/forensics-steganography-challenges-ctf-writeups-0f71112ddf4a) — ✍️ Medium
- [ICTF 2025 Writeup - Medium](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) — ✍️ Medium

### Network forensics

pcap analysis, protocol reconstruction, traffic anomaly detection.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) — 📝 Blog

### Metadata forensics

EXIF, document metadata, OLE structures.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [TCP1P CTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/tcp1pctf2024) — 📝 Blog


## 🎯 Suggested Learning Order

If you're new to forensics & steganography, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with HackTheBox's forensics challenges (easy tier), then read the Volatility documentation and work through memory-dump challenges.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal the collection repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
