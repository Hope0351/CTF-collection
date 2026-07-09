# 🚩 CTF Collection

> A comprehensive, professionally-curated archive of **Capture The Flag (CTF)** writeups, challenge sources, learning resources, video walkthroughs, and tooling — indexed by category, event, archetype, year, and platform.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Categories](https://img.shields.io/badge/Categories-13-blue)](#-repository-structure)
[![Sources](https://img.shields.io/badge/Sources-376-green)](#-corpus-statistics)
[![Platforms](https://img.shields.io/badge/Platforms-GitHub%20%7C%20Medium%20%7C%20YouTube%20%7C%20CTFtime%20%7C%20Blogs-orange)](#-corpus-statistics)
[![Maintained](https://img.shields.io/badge/Maintained-Yes-success)](CHANGELOG.md)

---

## 📖 What This Repository Is

This is a **curated knowledge base** for the global Capture The Flag community. Rather than being yet another list of links, this collection is:

- **Multi-source** — 376 curated entries drawn from 5 distinct content platforms: GitHub repositories, Medium articles, YouTube video walkthroughs, CTFtime event entries, and personal security blogs.
- **Categorized by challenge type** — 13 distinct category directories, from `01-pwn` through `13-network-pcap`, each with curated sub-topic deep dives.
- **Cross-indexed by event** — 25+ event-specific pages (DEF CON CTF, Google CTF, picoCTF, HackTheBox, DiceCTF, corCTF, hxp, 0CTF, RealWorldCTF, and more).
- **Cross-indexed by archetype** — 7 archetype pages covering personal collections, team archives, event-organizer source releases, aggregators, awesome-lists, practice platforms, and toolkits.
- **Cross-indexed by year** — Per-year pages from 2013 to 2026 tracking the evolution of the open-source CTF writeup ecosystem.
- **Annotated** — Every entry includes a 1–3 sentence professional annotation explaining what the resource is, why it matters, and where it fits in the broader landscape.
- **Enriched with metadata** — GitHub repositories include star counts, primary language, last-push date, and difficulty assessment.

This is **not** a mirror of other people's content. Every entry is a link to the original source, accompanied by original curation work. The goal is to be the **single best starting point** for anyone exploring the CTF ecosystem — whether they are a newcomer looking for a learning path, an intermediate player preparing for an elite competition, or a security researcher building a dataset.

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
| **GitHub repositories** | 136 |
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

The following GitHub repositories are the structural backbone of the open-source CTF writeup ecosystem. Each has been cross-referenced by multiple independent search angles and verified to have substantial community adoption.

| # | Repository | Stars | Categories | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | [sajjadium/ctf-archives](https://github.com/sajjadium/ctf-archives) | 1,509 ⭐⭐⭐⭐ | Crypto, Hardware | 2013–2026 | CTF Archives: Collection of CTF Challenges. Contribute to sajjadium/ctf-archives development by cre… |
| 2 | [daffainfo/ctf-writeup](https://github.com/daffainfo/ctf-writeup) | 188 ⭐⭐ | — | 2021–2024 | GitHub Stars Archive Program. This repository shall comprise writeups concerning Capture The Flag (… |
| 3 | [r3kapig/writeup (local mirror)](./repos/r3kapig/writeup) | 188 ⭐⭐ | Forensics, Crypto, Pwn | 2018–2022 | CTF challenges writeup. r3kapig is a united CTF Team. We are publishing our official writeups here.… |
| 4 | [apsdehal/awesome-ctf (local mirror)](./repos/apsdehal/awesome-ctf) | 11,656 ⭐⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2016–2016 | A curated list of Capture The Flag (CTF) frameworks, libraries, resources, softwares and tutorials.… |
| 5 | [blockthreat/blocksec-ctfs (local mirror)](./repos/blockthreat/blocksec-ctfs) | 1,632 ⭐⭐⭐⭐ | Programming, Reverse Engineering, Crypto | 2017–2023 | A curated list of blockchain security Wargames, Challenges, and Capture the Flag (CTF) competitions… |
| 6 | [minaminao/ctf-blockchain (local mirror)](./repos/minaminao/ctf-blockchain) | 1,084 ⭐⭐⭐⭐ | Programming, Crypto, OSINT | 2018–2025 | This repository collects blockchain challenges in CTFs and wargames. Some of them include personal … |
| 7 | [momenbasel/htb-writeups (local mirror)](./repos/momenbasel/htb-writeups) | 152 ⭐⭐ | Forensics, Crypto, Mobile | 2017–2026 | The most comprehensive Hack The Box writeup collection - 500+ machines, 400+ challenges, interactiv… |
| 8 | [orangetw/My-CTF-Web-Challenges (local mirror)](./repos/orangetw/My-CTF-Web-Challenges) | 2,853 ⭐⭐⭐⭐ | Crypto, Cloud, Pwn | 2013–2025 | My CTF Web Challenges. This is the repository of all CTF challenges I made, including the source co… |
| 9 | [Crypto-Cat/CTF (local mirror)](./repos/Crypto-Cat/CTF) | 2,512 ⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2026–2026 | CTF challenge write-ups, files, scripts etc to go with my video walkthroughs. Check out my blog and… |
| 10 | [p4-team/ctf](https://github.com/p4-team/ctf) | 1,844 ⭐⭐⭐⭐ | — | 2015–2023 | 2023.04.01 Hack-a-Sat 4 Quals(4th place/381 teams) · 2022.01.29 InsomniHack Teaser 2022(1st place/4… |
| 11 | [xtiankisutsa/awesome-mobile-ctf (local mirror)](./repos/xtiankisutsa/awesome-mobile-ctf) | 1,157 ⭐⭐⭐⭐ | Forensics, Crypto, Mobile | 2013–2022 | This is a curated list of mobile based CTFs, write-ups and vulnerable mobile apps. Most of them are… |
| 12 | [Adamkadaban/CTFs (local mirror)](./repos/Adamkadaban/CTFs) | 840 ⭐⭐⭐ | Programming, Forensics, Crypto | 2018–2024 | CTF Cheat Sheet + Writeups / Files ... Really good resource from John Hammond for different types o… |
| 13 | [sajjadium/ctf-writeups (local mirror)](./repos/sajjadium/ctf-writeups) | 227 ⭐⭐ | Web | 2017–2019 | CTF Writeups: Collection of CTF "technical" writeups by PersianCats. - sajjadium/ctf-writeups. |
| 14 | [DownUnderCTF/Challenges_2025_Public (local mirror)](./repos/DownUnderCTF/Challenges_2025_Public) | 110 ⭐⭐ | — | 2025–2025 | Files + Solutions for DownUnderCTF 2025 Challenges - GitHub - DownUnderCTF/Challenges_2025_Public: … |
| 15 | [Kasimir123/CTFWriteUps (local mirror)](./repos/Kasimir123/CTFWriteUps) | 61 ⭐⭐ | Forensics, Crypto, Stego | 2021–2021 | Collection of CTF Writeups for various ctfs. Mostly focused on reverse engineering, and contains al… |
| 16 | [tim-barc/ctf_writeups (local mirror)](./repos/tim-barc/ctf_writeups) | 43 ⭐ | Forensics, Mobile, Reverse Engineering | 2019–2025 | Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to sol… |
| 17 | [ashutosh1206/Crypto-CTF-Writeups (local mirror)](./repos/ashutosh1206/Crypto-CTF-Writeups) | 42 ⭐ | Crypto | n/a | Writeups to Crypto Challenges in CTFs. Contribute to ashutosh1206/Crypto-CTF-Writeups development b… |
| 18 | [merrychap/ctf-writeups (local mirror)](./repos/merrychap/ctf-writeups) | 36 ⭐ | Pwn, Reverse Engineering, Forensics | n/a | All writeups are about Reverse Engineering and Binary Exploitation tasks. No crypto, forensics, and… |
| 19 | [Tan-JunWei/CTF-Writeups](https://github.com/Tan-JunWei/CTF-Writeups) | 15 ⭐ | Web, OSINT, Forensics | n/a | Welcome to my Capture The Flag (CTF) writeup repository! Here you'll find detailed explanations and… |
| 20 | [SandWithCheese/ctf-writeups](https://github.com/SandWithCheese/ctf-writeups) | 14 ⭐ | Reverse Engineering | n/a | Welcome to my CTF (Capture The Flag) writeups repository! This repository contains solutions for va… |

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

## 📦 Local Mirrors

To make this collection fully self-contained and usable offline, **114 of the 156 linked GitHub repositories** have been mirrored locally under [`./repos/`](./repos/). Markdown links throughout this collection have been rewritten to point to the local mirror instead of the upstream GitHub URL, using the annotation `(local mirror)` in the link text.

### What's mirrored

| Metric | Count |
|---|---:|
| Total GitHub repositories referenced | 156 |
| Successfully mirrored locally | **114** |
| Not mirrored (size / rate-limit / disk constraints) | 42 |
| Local mirror directory | [`./repos/`](./repos/) |
| Total mirror size on disk | ~2.5 GB (after `.gitignore` filters) |

### How to identify a mirrored link

Original links used the form:

```
[apsdehal/awesome-ctf](https://github.com/apsdehal/awesome-ctf)
```

After mirroring, links now look like:

```
[apsdehal/awesome-ctf (local mirror)](./repos/apsdehal/awesome-ctf)
```

The `(local mirror)` suffix makes mirrored links visually distinguishable in GitHub's rendered markdown. Unmirrored repos (the 42 that could not be downloaded due to size, rate-limiting, or disk constraints on the generation machine) keep their original `https://github.com/...` URLs unchanged.

### Repository layout

```
CTF-collection/
├── README.md                          ← you are here
├── repos/                             ← local mirrors (NEW)
│   ├── apsdehal/
│   │   └── awesome-ctf/
│   ├── Crusaders-of-Rust/
│   │   ├── corCTF-2022-public-challenge-archive/
│   │   ├── corctf-2024-public-challenge-repo/
│   │   └── corctf-2025-public-challenge-repo/
│   ├── ... (114 owner/repo pairs total)
│   └── sajjadium/
│       └── ctf-writeups/
├── 00-start-here/
├── 01-pwn/ ... 13-network-pcap/
├── 20-events/
├── 30-archetypes/
├── 40-tooling/
├── 50-writeups-by-year/
└── 99-appendix/
```

### What's NOT committed (`.gitignore` policy)

To keep the repository within GitHub's size limits, the following categories of files are excluded from commits via `.gitignore` (but remain on the local mirror):

- **Binary challenge artifacts**: `*.pcap`, `*.pcapng`, `*.bin`, `*.elf`, `*.exe`, `*.dll`, `*.so`, `*.dylib`, `*.dmp`, `*.raw`, `*.img`, `*.iso`, `*.vmdk`
- **VM images and kernel artifacts**: `*.qcow2`, `*.vdi`, `*.vhd`, `*.ova`, `*.ovf`, `*.bzImage`, `*.vmlinuz`, `*.initramfs`, `*.cpio`
- **Compressed handouts**: `*.tar.gz`, `*.tgz`, `*.tar.bz2`, `*.tbz2`, `*.tar.xz`, `*.txz`, `*.7z`, `*.rar`, `*.lz4`, `*.zst`
- **Java / Android packages**: `*.jar`, `*.aar`, `*.apk`, `*.dex`, `*.war`
- **Database / memory dumps**: `*.db`, `*.sqlite`, `*.sqlite3`, `*.memdump`, `*.heapdump`, `*.hprof`
- **ML model files**: `*.dat`, `*.pkl`, `*.pickle`, `*.h5`, `*.pb`, `*.onnx`, `*.pt`, `*.pth`, `*.ckpt`, `*.safetensors`
- **Explicit per-file ignores** for 21 files larger than 50 MB (VM images, prebuilt binaries, large archives)

### Repos not mirrored (42)

The following repositories could not be mirrored due to size, rate-limiting, or disk constraints on the generation machine. Their links throughout this collection remain unchanged (pointing to upstream GitHub):

#### Failed to download (16 — never fetched)

| Repository | Reason |
|---|---|
| `sajjadium/ctf-archives` | Too large (master archive) |
| `p4-team/ctf` | Too large (10+ years of writeups) |
| `hackplayers/hackthebox-writeups` | Too large |
| `google/google-ctf` | Too large (500+ MB .git) |
| `justcatthefish/justctf-2023` | Too large |
| `project-sekai-ctf/sekaictf-2024` | Too large |
| `daffainfo/ctf-writeup` | 335 MB, exceeds size cap |
| `MartinPetkov/GCTF2021BeginnersQuestWriteups` | Extract failed (disk) |
| `SECCON/SECCON13_final_CTF` | Extract failed (disk) |
| `SandWithCheese/ctf-writeups` | Transient download fail |
| `Tan-JunWei/CTF-Writeups` | 403 rate-limited |
| `mephi42/ctf` | Not attempted |
| `shekkbuilder/ctf-2` | Not attempted |
| `sigpwny/UIUCTF-2023-Public` | Not attempted |
| `silly-lily/CTF-Writeups` | Not attempted |
| `siunam321/CTF-Writeups` | Not attempted |

#### Downloaded but not pushed (26 — dropped to fit within disk/push constraints)

These repos were downloaded successfully but had to be excluded from the committed mirror to fit within the generation environment's disk and GitHub push size constraints. Their links have been restored to point to upstream GitHub.

| Repository | Approx. size |
|---|---:|
| `Adamkadaban/CTFs` | 1.3 GB |
| `Crusaders-of-Rust/corCTF-2022-public-challenge-archive` | (part of 898 MB owner total) |
| `Crusaders-of-Rust/corctf-2024-public-challenge-repo` | (part of 898 MB owner total) |
| `Crusaders-of-Rust/corctf-2025-public-challenge-repo` | (part of 898 MB owner total) |
| `DownUnderCTF/Challenges_2022_Public` | (part of 811 MB owner total) |
| `DownUnderCTF/Challenges_2025_Public` | (part of 811 MB owner total) |
| `dicegang/dicectf-quals-2024-challenges` | (part of 684 MB owner total) |
| `dicegang/dicectf-quals-2025-challenges` | (part of 684 MB owner total) |
| `justcatthefish/ctf-writeups` | (part of 530 MB owner total) |
| `justcatthefish/justctf-2024` | (part of 530 MB owner total) |
| `justcatthefish/justctf-2025` | (part of 530 MB owner total) |
| `SecurityInnovation/Smart-Contract-CTF` | 492 MB |
| `osirislab/CSAW-CTF-2022-Final-WriteUps` | (part of 424 MB owner total) |
| `osirislab/CSAW-CTF-2023-Quals` | (part of 424 MB owner total) |
| `osirislab/CSAW-CTF-2024-Quals` | (part of 424 MB owner total) |
| `osirislab/CSAW-CTF-2025-Finals-Public` | (part of 424 MB owner total) |
| `lieanu/LibcSearcher` | 346 MB |
| `Kasimir123/CTFWriteUps` | 328 MB |
| `1GN1tE/CTF_Writeups` | 127 MB |
| `Nautilus-Institute/quals-2024` | 181 MB |
| `RasyidMF/ctf-writeup` | 175 MB |
| `HackTricks-wiki/hacktricks` | 164 MB |
| `Ferdibrgl/cyber-apocalypse-ctf--2023-2024-` | 157 MB |
| `david942j/ctf-writeups` | 161 MB |
| `david942j/one_gadget` | (part of 161 MB owner total) |
| `DownUnderCTF/Challenges_2021_public` | (part of 811 MB owner total) |

To add these to the mirror, re-run the generation pipeline on a machine with ≥ 25 GB free disk.

### Regenerating the mirror

The mirror was generated by an automated script that:

1. Walked all `.md` files in this repository
2. Extracted every unique `https://github.com/<owner>/<repo>` URL
3. Cloned each repo with `git clone --depth 1` (shallow, no history)
4. Stripped each repo's `.git/` directory to save disk
5. Removed `.gitmodules` files (submodules not initialized)
6. Removed `filter=lfs` `.gitattributes` rules (LFS not configured)
7. Rewrote markdown links to point to `./repos/<owner>/<repo>` with `(local mirror)` annotation

See the `scripts/` directory in the development workspace for the source of the generation tooling.

---

## 📜 License

The curation, annotation, and structural work in this repository is licensed under the [MIT License](LICENSE). The mirrored repositories under [`./repos/`](./repos/) retain their **original licenses** — each subdirectory's contents are governed by the license declared in that upstream project. Where no license is present, the default terms of the original repository apply.

---

## 🙏 Acknowledgments

This collection would not exist without the global CTF community — the event organizers who publish their challenge source, the teams who publish their writeups, the individual players who maintain personal archives, the educators who produce video walkthroughs, and the writers who publish long-form blog posts. Every entry in this collection is a link to one of those contributions. If you find a resource here useful, please consider starring the original repository, subscribing to the original author, or thanking them on social media.

Maintained by [@Hope0351](https://github.com/Hope0351).
