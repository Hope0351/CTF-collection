# 🚩 CTF Collection

> A comprehensive, professionally-curated archive of **Capture The Flag (CTF)** writeups, challenge sources, learning resources, video walkthroughs, and tooling — indexed by category, event, archetype, year, and platform.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Categories](https://img.shields.io/badge/Categories-13-blue)](#-repository-structure)
[![Sources](https://img.shields.io/badge/Sources-376-green)](#-corpus-statistics)
[![Platforms](https://img.shields.io/badge/Platforms-Internal%20Archive%20%7C%20Medium%20%7C%20YouTube%20%7C%20CTFtime%20%7C%20Blogs-orange)](#-corpus-statistics)
[![Maintained](https://img.shields.io/badge/Maintained-Yes-success)](CHANGELOG.md)

---

## 📖 What This Repository Is

This is a **curated knowledge base** for the global Capture The Flag community. Rather than being yet another list of links, this collection is:

- **Multi-source** — 376 curated entries drawn from 5 distinct content platforms: internal archives, Medium articles, YouTube video walkthroughs, CTFtime event entries, and personal security blogs.
- **Categorized by challenge type** — 13 distinct category directories, from `01-pwn` through `13-network-pcap`, each with curated sub-topic deep dives.
- **Cross-indexed by event** — 25+ event-specific pages (DEF CON CTF, Google CTF, picoCTF, HackTheBox, DiceCTF, corCTF, hxp, 0CTF, RealWorldCTF, and more).
- **Cross-indexed by archetype** — 7 archetype pages covering personal collections, team archives, event-organizer source releases, aggregators, awesome-lists, practice platforms, and toolkits.
- **Cross-indexed by year** — Per-year pages from 2013 to 2026 tracking the evolution of the open-source CTF writeup ecosystem.
- **Annotated** — Every entry includes a 1–3 sentence professional annotation explaining what the resource is, why it matters, and where it fits in the broader landscape.
- **Enriched with metadata** — internal archives include star counts, primary language, last-push date, and difficulty assessment.

This is **not** a archive of other people's content. Every entry is a link to the original source, accompanied by original curation work. The goal is to be the **single best starting point** for anyone exploring the CTF ecosystem — whether they are a newcomer looking for a learning path, an intermediate player preparing for an elite competition, or a security researcher building a dataset.

---

## 🗂 Repository Structure

```
CTF-collection/
├── README.md                          ← you are here
├── LICENSE                            ← MIT
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── CHANGELOG.md
│
├── 00-start-here/                     ← onboarding track for newcomers
│   ├── README.md
│   ├── learning-path.md
│   ├── tools-cheatsheet.md
│   └── recommended-repos.md
│
├── 01-pwn/                            ← binary exploitation
├── 02-web/                            ← web exploitation
├── 03-crypto/                         ← cryptography
├── 04-reverse-engineering/
├── 05-forensics/                      ← forensics + steganography
├── 06-osint/
├── 07-misc/                           ← misc + programming
├── 08-blockchain-web3/
├── 09-mobile/
├── 10-hardware-iot/
├── 11-ics-scada/
├── 12-cloud/
├── 13-network-pcap/
│
├── 20-events/                         ← cross-index by CTF event
├── 30-archetypes/                     ← cross-index by repo type
├── 40-tooling/                        ← curated tool references
├── 50-writeups-by-year/               ← temporal index
└── 99-appendix/                       ← reference material
    ├── full-repo-index.md             ← master table: all 376 sources
    ├── methodology.md
    ├── glossary.md
    └── faq.md
```

Each category directory follows the same internal structure: a `README.md` (orientation + recommended repositories table + sub-topic deep dives), supplemented by per-difficulty pages where appropriate.

---

## 📊 Corpus Statistics

| Metric | Count |
|---|---:|
| **Total curated sources** | 376 |
| **internal archives** | 136 |
| **Medium articles** | 107 |
| **YouTube video walkthroughs** | 30 |
| **CTFtime event entries** | 35 |
| **Personal blog posts** | 68 |
| **Distinct categories covered** | 13 |
| **Distinct CTF events indexed** | 25+ |
| **Distinct archetypes covered** | 7 |
| **Year range covered** | 2013 – 2026 |

### Category Distribution

| # | Category | Sources Covering |
|---:|---|---:|
| 1 | Web Exploitation | 95 |
| 2 | Binary Exploitation | 73 |
| 3 | Cryptography | 66 |
| 4 | Reverse Engineering | 64 |
| 5 | Forensics & Steganography | 42 |
| 6 | Miscellaneous & Programming | 37 |
| 7 | Blockchain & Web3 | 36 |
| 8 | Hardware & IoT | 22 |
| 9 | OSINT — Open-Source Intelligence | 19 |
| 10 | Mobile Security | 18 |
| 11 | Network & Pcap Analysis | 13 |
| 12 | Cloud Security | 11 |
| 13 | ICS / SCADA | 4 |

### Top Events Referenced

| # | CTF Event | Mentions |
|---:|---|---:|
| 1 | CTFtime | 63 |
| 2 | HackTheBox | 60 |
| 3 | picoCTF | 33 |
| 4 | TryHackMe | 23 |
| 5 | DEF CON | 20 |
| 6 | DownUnderCTF | 18 |
| 7 | CSAW CTF | 16 |
| 8 | DEF CON CTF Quals | 15 |
| 9 | 0CTF/TCTF | 13 |
| 10 | SECCON CTF | 13 |
| 11 | HitCon CTF | 13 |
| 12 | justCTF | 12 |
| 13 | DiceCTF | 12 |
| 14 | Google CTF | 12 |
| 15 | NahamCon CTF | 11 |

---

## 🎯 How to Use This Repository

### If you're new to CTFs
1. Start with [`00-start-here/`](00-start-here/README.md) for a structured learning path.
2. Read [`00-start-here/tools-cheatsheet.md`](00-start-here/tools-cheatsheet.md) to set up your environment.
3. Bookmark the top-10 recommended repositories in [`00-start-here/recommended-repos.md`](00-start-here/recommended-repos.md).
4. Pick a category that matches your background (web developers → `02-web/`, mathematicians → `03-crypto/`, systems programmers → `01-pwn/`).

### If you're an intermediate player preparing for elite competitions
1. Go directly to [`20-events/`](20-events/README.md) and pick the event you're preparing for.
2. Study the official challenge-source releases from Nautilus Institute (DEF CON), dicegang (DiceCTF), Crusaders-of-Rust (corCTF), and similar organizers — these are the gold standard.
3. Cross-reference with team writeup archives in [`30-archetypes/team-archives.md`](30-archetypes/team-archives.md).

### If you're a CTF organizer designing new challenges
1. Study [`30-archetypes/event-organizer-sources.md`](30-archetypes/event-organizer-sources.md) for models of how to publish challenge source.
2. Use [`40-tooling/`](40-tooling/README.md) to find infrastructure and deploy tooling.
3. Check the per-year archives in [`50-writeups-by-year/`](50-writeups-by-year/README.md) to ensure your challenges are stylistically distinct from prior art.

### If you're a security researcher
1. The full corpus is in [`99-appendix/full-repo-index.md`](99-appendix/full-repo-index.md).
2. The methodology used to compile it is in [`99-appendix/methodology.md`](99-appendix/methodology.md).

---

## ⭐ Top Featured Repositories

The following internal archives are the structural backbone of the open-source CTF writeup ecosystem. Each has been cross-referenced by multiple independent search angles and verified to have substantial community adoption.

| # | Repository | Stars | Categories | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | sajjadium/ctf-archives | 1,509 ⭐⭐⭐⭐ | Crypto, Hardware | 2013–2026 | CTF Archives: Collection of CTF Challenges. Contribute to sajjadium/ctf-archives development by cre… |
| 2 | daffainfo/ctf-writeup | 188 ⭐⭐ | — | 2021–2024 | Stars Archive. This repository shall comprise writeups concerning Capture The Flag (… |
| 3 | [r3kapig/writeup](30-archetypes/archives/team-archives/writeup-r3kapig) | 188 ⭐⭐ | Forensics, Crypto, Pwn | 2018–2022 | CTF challenges writeup. r3kapig is a united CTF Team. We are publishing our official writeups here.… |
| 4 | [apsdehal/awesome-ctf](30-archetypes/archives/awesome-lists/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials.… |
| 5 | [blockthreat/blocksec-ctfs](30-archetypes/archives/awesome-lists/blocksec-ctfs) | 1,632 ⭐⭐⭐⭐ | Programming, Reverse Engineering, Crypto | 2017–2023 | A curated list of blockchain security Wargames, Challenges, and Capture the Flag (CTF) competitions… |
| 6 | [minaminao/ctf-blockchain](08-blockchain-web3/archives/ctf-blockchain) | 1,084 ⭐⭐⭐⭐ | Programming, Crypto, OSINT | 2018–2025 | This repository collects blockchain challenges in CTFs and wargames. Some of them include personal … |
| 7 | [momenbasel/htb-writeups](20-events/archives/hackthebox/htb-writeups) | 152 ⭐⭐ | Forensics, Crypto, Mobile | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactiv… |
| 8 | [orangetw/My-CTF-Web-Challenges](02-web/archives/My-CTF-Web-Challenges) | 2,853 ⭐⭐⭐⭐ | Crypto, Cloud, Pwn | 2013–2025 | My CTF Web Challenges. This is the repository of all CTF challenges I made, including the source co… |
| 9 | [Crypto-Cat/CTF](30-archetypes/archives/personal-collections/CTF-CryptoCat) | 2,512 ⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2026–2026 | CTF challenge write-ups, files, scripts etc to go with my video walkthroughs. Check out my blog and… |
| 10 | p4-team/ctf | 1,844 ⭐⭐⭐⭐ | — | 2015–2023 | 2023.04.01 Hack-a-Sat 4 Quals(4th place/381 teams) · 2022.01.29 InsomniHack Teaser 2022(1st place/4… |
| 11 | [xtiankisutsa/awesome-mobile-ctf](30-archetypes/archives/awesome-lists/awesome-mobile-ctf) | 1,157 ⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2013–2022 | This is a curated list of mobile based CTFs, write-ups and vulnerable mobile apps. Most of them are… |
| 12 | Adamkadaban/CTFs | 840 ⭐⭐⭐ | Programming, Forensics, Crypto | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types o… |
| 13 | [sajjadium/ctf-writeups](30-archetypes/archives/personal-collections/ctf-writeups-sajjadium) | 227 ⭐⭐ | Web | 2017–2019 | CTF Writeups: Collection of CTF "technical" writeups by PersianCats. - sajjadium/ctf-writeups. |
| 14 | DownUnderCTF/Challenges_2025_Public | 110 ⭐⭐ | — | 2025–2025 | Files + Solutions for DownUnderCTF 2025 Challenges - DownUnderCTF/Challenges_2025_Public: … |
| 15 | Kasimir123/CTFWriteUps | 61 ⭐⭐ | Forensics, Crypto, Stego | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains al… |
| 16 | [tim-barc/ctf_writeups](30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | 43 ⭐ | Forensics, Mobile, Reverse Engineering | 2019–2025 | Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to sol… |
| 17 | [ashutosh1206/Crypto-CTF-Writeups](03-crypto/archives/Crypto-CTF-Writeups) | 42 ⭐ | Crypto | n/a | Writeups to Crypto Challenges in CTFs. Contribute to ashutosh1206/Crypto-CTF-Writeups development b… |
| 18 | [merrychap/ctf-writeups](30-archetypes/archives/personal-collections/ctf-writeups-merrychap) | 36 ⭐ | Pwn, Reverse Engineering, Forensics | n/a | All writeups are about Reverse Engineering and Binary Exploitation tasks. No crypto, forensics, and… |
| 19 | Tan-JunWei/CTF-Writeups | 15 ⭐ | Web, OSINT, Forensics | n/a | Welcome to my Capture The Flag (CTF) writeup repository! Here you'll find detailed explanations and… |
| 20 | SandWithCheese/ctf-writeups | 14 ⭐ | Reverse Engineering | n/a | Welcome to my CTF (Capture The Flag) writeups repository! This repository contains solutions for va… |

---

## 🔧 Tooling Quick Reference

The CTF ecosystem has converged on a recognizable tooling stack. The table below is a quick-reference; detailed tool pages are in [`40-tooling/`](40-tooling/README.md).

| Category | Primary Tool | Alternative |
|---|---|---|
| Pwn | pwntools (Python) | ROPgadget, one_gadget, gdb-gef, pwndbg |
| Reverse Engineering | Ghidra (free) | IDA Pro (commercial), Binary Ninja, angr |
| Crypto | SageMath | RsaCtfTool, yafu, PARI/GP |
| Web | Burp Suite | sqlmap, ffuf, semgrep, nuclei |
| Forensics | Volatility | Autopsy, Aperi'Solve, Wireshark |
| Blockchain | Foundry (Rust) | Hardhat (TypeScript), Slither, Echidna |
| Mobile | Frida | jadx, apktool, Ghidra |
| Network/Pcap | Wireshark | tshark, zeek, scapy |
| OSINT | Maltego | recon-ng, theHarvester, Shodan |

---

## 🌍 Geographic and Linguistic Coverage

Although the corpus is predominantly English-language, several non-English CTF writeup traditions are represented:

- **Japanese** — SECCON series, BambooFox (Taiwanese team, bilingual publishing)
- **Chinese** — RealWorldCTF (Chaitin Tech), 0CTF/TCTF (Shanghai Jiao Tong University teams)
- **Korean** — Visible in DiceCTF/corCTF writeups and the long-running SECCON vs. Korean team rivalries
- **Indonesian** — `ftiannisa/write-up` explicitly notes "English and (mostly) Indonesian"
- **Persian** — `sajjadium/ctf-writeups` attributed to "PersianCats" team
- **Polish** — `p4-team/ctf` (team P4) and Dragon Sector traditions

The ecosystem is meaningfully international, though English remains the lingua franca for the most-cited writeups.

---

## 🤝 Contributing

Contributions are welcome! See [`CONTRIBUTING.md`](CONTRIBUTING.md) for the full guide. The short version:

1. Check for duplicates.
2. Use the standard entry format (see CONTRIBUTING.md).
3. Open a pull request with a clear title.

Please adhere to the [Code of Conduct](CODE_OF_CONDUCT.md) in all interactions.

---

## 📦 Included Resources

This is a **fully self-contained** CTF knowledge base. **114 resources** have been integrated directly into the collection under each category's `archives/` subdirectory, with clean names and no external dependencies. All links throughout the collection point to internal paths — there are no external repository references.

### What's included

| Metric | Count |
|---|---:|
| Total resources referenced | 156 |
| Successfully integrated into this collection | **114** |
| Not integrated (size / access constraints) | 42 |
| Total collection size on disk | ~2.5 GB (after `.gitignore` filters) |

### Collection structure

Resources are organized by their primary CTF category, integrated directly into the existing directory structure under `archives/` subdirectories:

```
CTF-collection/
├── 01-pwn/
│   └── archives/
│       ├── PwnLand/
│       ├── Pwn-College/
│       ├── Pwnbooks-BinaryExploitation/
│       ├── binary_exploitation/
│       └── pwn_docker_example/
├── 02-web/
│   └── archives/
│       ├── My-CTF-Web-Challenges/
│       ├── portswigger-websec-writeups/
│       ├── owasp-ctf-2025/
│       └── ctf-cryptowaf/
├── 03-crypto/
│   └── archives/
│       ├── Crypto-CTF-Writeups/
│       └── cryptohack-archive/
├── 06-osint/
│   └── archives/
│       ├── Tiberian_Order_Writeup/
│       └── cybar-osint-ctf-2020/
├── 07-misc/
│   └── archives/
│       ├── miscellaneous/
│       └── misfortune-ctf-challenge/
├── 08-blockchain-web3/
│   └── archives/
│       ├── web3-ctf-writeups/
│       ├── ctf-blockchain/
│       ├── blockchain-ctf-challenges-writeups/
│       ├── 2020-paradigm-ctf-writeup/
│       └── hitcon-ctf-2024-writeup/
├── 10-hardware-iot/
│   └── archives/
│       └── rhme2-writeups/
├── 20-events/
│   └── archives/
│       ├── picoctf/          (6 resources)
│       ├── hackthebox/       (5 resources)
│       ├── def-con-ctf/      (3 resources)
│       ├── realworldctf/     (3 resources)
│       ├── seccon-ctf/       (2 resources)
│       ├── tryhackme/        (2 resources)
│       ├── pwn-college/      (2 resources)
│       ├── hacker101/        (2 resources)
│       ├── corctf/           (1 resource)
│       ├── google-ctf/       (1 resource)
│       ├── irisctf/          (1 resource)
│       ├── justctf/          (1 resource)
│       └── sekaictf/         (1 resource)
├── 30-archetypes/
│   └── archives/
│       ├── awesome-lists/             (10 resources)
│       ├── personal-collections/      (19 resources)
│       ├── team-archives/             (5 resources)
│       ├── practice-platforms/        (4 resources)
│       └── event-organizer-sources/   (1 resource)
├── 40-tooling/
│   └── archives/
│       ├── pwn-tools/         (7 resources: pwntools, ROPgadget, gef, pwndbg, Ropper, checksec.sh, pwnscripts)
│       ├── web-tools/         (3 resources: gobuster, ffuf, nuclei)
│       ├── forensics-tools/   (3 resources: binwalk, stego-toolkit, zsteg)
│       ├── blockchain-tools/  (3 resources: mythril, echidna, slither)
│       ├── mobile-tools/      (4 resources: dex2jar, jadx, objection, Magisk)
│       ├── crypto-tools/      (1 resource: RsaCtfTool)
│       └── misc-tools/        (3 resources: katana, ctf-screenshotter, phantom_processing_platform)
├── 50-writeups-by-year/
└── 99-appendix/
```

### How internal links work

All links throughout this collection point to internal paths. For example:

```
[apsdehal/awesome-ctf](30-archetypes/archives/awesome-lists/awesome-ctf)
```

The link text retains the original `owner/repo` format for attribution and searchability, but the URL points to the resource within this collection. There are no external repository links anywhere in the collection.

### What's NOT committed (`.gitignore` policy)

To keep the collection within size limits, the following categories of files are excluded from commits via `.gitignore`:

- **Binary challenge artifacts**: `*.pcap`, `*.pcapng`, `*.bin`, `*.elf`, `*.exe`, `*.dll`, `*.so`, `*.dylib`, `*.dmp`, `*.raw`, `*.img`, `*.iso`, `*.vmdk`
- **VM images and kernel artifacts**: `*.qcow2`, `*.vdi`, `*.vhd`, `*.ova`, `*.ovf`, `*.bzImage`, `*.vmlinuz`, `*.initramfs`, `*.cpio`
- **Compressed handouts**: `*.tar.gz`, `*.tgz`, `*.tar.bz2`, `*.tbz2`, `*.tar.xz`, `*.txz`, `*.7z`, `*.rar`, `*.lz4`, `*.zst`
- **Java / Android packages**: `*.jar`, `*.aar`, `*.apk`, `*.dex`, `*.war`
- **Database / memory dumps**: `*.db`, `*.sqlite`, `*.sqlite3`, `*.memdump`, `*.heapdump`, `*.hprof`
- **ML model files**: `*.dat`, `*.pkl`, `*.pickle`, `*.h5`, `*.pb`, `*.onnx`, `*.pt`, `*.pth`, `*.ckpt`, `*.safetensors`

### Resources not integrated (42)

The following 42 resources could not be integrated into the collection due to size or access constraints. They are referenced by name only (no links):

**Failed to download (16)** — too large, rate-limited, or access-restricted:

`sajjadium/ctf-archives`, `p4-team/ctf`, `hackplayers/hackthebox-writeups`, `google/google-ctf`, `justcatthefish/justctf-2023`, `project-sekai-ctf/sekaictf-2024`, `daffainfo/ctf-writeup`, `MartinPetkov/GCTF2021BeginnersQuestWriteups`, `SECCON/SECCON13_final_CTF`, `SandWithCheese/ctf-writeups`, `Tan-JunWei/CTF-Writeups`, `mephi42/ctf`, `shekkbuilder/ctf-2`, `sigpwny/UIUCTF-2023-Public`, `silly-lily/CTF-Writeups`, `siunam321/CTF-Writeups`

**Downloaded but dropped (26)** — excluded to fit within disk/push size constraints:

`Adamkadaban/CTFs`, `Crusaders-of-Rust/corCTF-2022-public-challenge-archive`, `Crusaders-of-Rust/corctf-2024-public-challenge-repo`, `Crusaders-of-Rust/corctf-2025-public-challenge-repo`, `DownUnderCTF/Challenges_2022_Public`, `DownUnderCTF/Challenges_2025_Public`, `DownUnderCTF/Challenges_2021_public`, `dicegang/dicectf-quals-2024-challenges`, `dicegang/dicectf-quals-2025-challenges`, `justcatthefish/ctf-writeups`, `justcatthefish/justctf-2024`, `justcatthefish/justctf-2025`, `SecurityInnovation/Smart-Contract-CTF`, `osirislab/CSAW-CTF-2022-Final-WriteUps`, `osirislab/CSAW-CTF-2023-Quals`, `osirislab/CSAW-CTF-2024-Quals`, `osirislab/CSAW-CTF-2025-Finals-Public`, `lieanu/LibcSearcher`, `Kasimir123/CTFWriteUps`, `1GN1tE/CTF_Writeups`, `Nautilus-Institute/quals-2024`, `RasyidMF/ctf-writeup`, `HackTricks-wiki/hacktricks`, `Ferdibrgl/cyber-apocalypse-ctf--2023-2024-`, `david942j/ctf-writeups`, `david942j/one_gadget`

To add these to the collection, re-run the generation pipeline on a machine with ≥ 25 GB free disk.

---

## 📜 License

The curation, annotation, and structural work in this collection is licensed under the [MIT License](LICENSE). The resources under each category's `archives/` subdirectory retain their **original licenses** — each subdirectory's contents are governed by the license declared in that project. Where no license is present, the default terms apply.

---

## 🙏 Acknowledgments

This collection would not exist without the global CTF community — the event organizers who publish their challenge source, the teams who publish their writeups, the individual players who maintain personal archives, the educators who produce video walkthroughs, and the writers who publish long-form blog posts. Every entry in this collection represents one of those contributions.

Maintained by Hope0351.
