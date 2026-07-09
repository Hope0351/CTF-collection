# Network & Pcap Analysis

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Packet-capture analysis for credential extraction, exfiltration detection, protocol-level attack reconstruction, and traffic-forensics. Wireshark and tshark are the dominant tools; writeups typically include reproducible display filters.

This category contains **13 curated sources** from across the CTF ecosystem: 13 GitHub repositories, 0 Medium articles, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 0 blog posts.

## 🏆 Recommended Repositories (GitHub)

The following GitHub repositories are the highest-value resources for this category. They are ranked by cross-search relevance, mention count, and star count.

| # | Repository | Stars | Difficulty | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | [apsdehal/awesome-ctf (local mirror)](../repos/apsdehal/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Beginner | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials. This list aims to h… |
| 2 | [momenbasel/htb-writeups (local mirror)](../repos/momenbasel/htb-writeups) | 152 ⭐⭐ | Varied | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactive knowledge graph, s… |
| 3 | [Adamkadaban/CTFs](https://github.com/Adamkadaban/CTFs) | 840 ⭐⭐⭐ | Varied | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types of challenges: https:… |
| 4 | [Kasimir123/CTFWriteUps](https://github.com/Kasimir123/CTFWriteUps) | 61 ⭐⭐ | Varied | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains all source files if th… |
| 5 | [tim-barc/ctf_writeups (local mirror)](../repos/tim-barc/ctf_writeups) | 43 ⭐ | Varied | 2019–2025 | Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to solve various Capture T… |
| 6 | [JohnHammond/ctf-katana (local mirror)](../repos/JohnHammond/ctf-katana) | 2,920 ⭐⭐⭐⭐ | Varied | 2015–2020 | This repository aims to hold suggestions (and hopefully/eventually code) for CTF challenges. The "project" is nicknamed… |
| 7 | [devploit/awesome-ctf-resources (local mirror)](../repos/devploit/awesome-ctf-resources) | 777 ⭐⭐⭐ | Varied | 2015–2015 | A list of Capture The Flag (CTF) frameworks, libraries, resources and software for started/experienced CTF players - de… |
| 8 | [JohnHammond/miscellaneous (local mirror)](../repos/JohnHammond/miscellaneous) | 84 ⭐⭐ | Varied | 2013–2016 | The purpose of this repository is to archive any extraneous documents, or anything else that really has no specific cat… |
| 9 | [Sudoite/ctf-writeups (local mirror)](../repos/Sudoite/ctf-writeups) | 27 ⭐ | Varied | 2016–2019 | This is a repository of writeups for various CTF challenges. I am intentionally leaving in discussion about where I mad… |
| 10 | [mbiesiad/ctf-writeups (local mirror)](../repos/mbiesiad/ctf-writeups) | 6 ⭐ | Varied | 2021–2025 | Personal Collection of CTF Writeups and Security Research. A personal collection of cybersecurity writeups - from CTF c… |
| 11 | [MacacaHub/CTF-writeups (local mirror)](../repos/MacacaHub/CTF-writeups) | 4  | Varied | 2019–2021 | 2021. BambooFox CTF 2021; HTCF Mid CTF 2021 (only for NSYSU course) · 2020. TCat CTF 2020; TJCTF 2020; HTCF Mid CTF 202… |
| 12 | [tsids/picoCTF-Writeups (local mirror)](../repos/tsids/picoCTF-Writeups) | 1  | Beginner | 2019–2026 | Navigate to the folder of the challenge you are looking for, and the solution can be found in <Challenge Title>.md. Fee… |
| 13 | [BarakBinyamin/ctf (local mirror)](../repos/BarakBinyamin/ctf) | 1  | Varied | 2023–2023 | The IOT-light uses hardcoded credentials to connect to WiFi, check for updates and communications by connecting to a cu… |


## ✍️ Curated Articles & Walkthroughs

Beyond GitHub repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|

## 🔬 Sub-Topic Deep Dive

The Network & Pcap Analysis category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### HTTP/HTTPS analysis

request reconstruction, cookie extraction.

*No directly-matching resources in this collection — consult the broader category list above.*

### DNS analysis

tunneling detection, exfil detection, subdomain enumeration.

*No directly-matching resources in this collection — consult the broader category list above.*

### FTP / SMB / NFS analysis

plaintext credential extraction.

Top resources for this sub-topic:

- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - GitHub (local mirror)](../repos/apsdehal/awesome-ctf) — 🐙 GitHub Repo
- [Hack The Box Writeups - The Ultimate HTB Resource - GitHub (local mirror)](../repos/momenbasel/htb-writeups) — 🐙 GitHub Repo
- [GitHub - Adamkadaban/CTFs: CTF Cheat Sheet + Writeups / Files for](https://github.com/Adamkadaban/CTFs) — 🐙 GitHub Repo
- [Kasimir123/CTFWriteUps: Collection of CTF Writeups for  - GitHub](https://github.com/Kasimir123/CTFWriteUps) — 🐙 GitHub Repo
- [JohnHammond/ctf-katana: This repository aims to hold  - GitHub (local mirror)](../repos/JohnHammond/ctf-katana) — 🐙 GitHub Repo

### Custom protocol analysis

Wireshark dissector writing.

Top resources for this sub-topic:

- [BarakBinyamin/ctf: Some embedded network attacks  - GitHub (local mirror)](../repos/BarakBinyamin/ctf) — 🐙 GitHub Repo

### TLS decryption

session key logging, pre-shared-key analysis.

*No directly-matching resources in this collection — consult the broader category list above.*


## 🎯 Suggested Learning Order

If you're new to network & pcap analysis, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with the Wireshark sample captures, then work through Malware Traffic Analysis exercises.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal GitHub repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
