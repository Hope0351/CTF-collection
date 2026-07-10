# Forensics & Steganography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Disk-image forensics, memory-dump analysis (Volatility), packet-capture analysis (Wireshark/tshark), and steganography (Aperi'Solve, zsteg, stegsolve). The category with the highest variance in challenge design — challenges range from trivial 'find the hidden flag in metadata' to sophisticated memory-malware-investigation scenarios.

This category contains **42 curated sources** from across the CTF ecosystem: 30 the collection repositories, 7 Medium articles, 0 YouTube video walkthroughs, 1 CTFtime event entries, and 4 blog posts.

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
