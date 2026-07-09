# Changelog

All notable changes to this CTF-collection repository are documented in this file.

The format is loosely based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [2026-07-10] — Local Mirror Import

### Added
- `repos/` top-level directory containing **local mirrors of 114 GitHub repositories** referenced throughout the collection (~2.5 GB on disk after `.gitignore` filtering).
- New `📦 Local Mirrors` section in `README.md` documenting the mirror structure, link-rewrite policy, `.gitignore` exclusions, and the 42 repos that could not be mirrored.
- Expanded `.gitignore` with CTF-specific binary artifact patterns (VM images, compressed handouts, Java/Android packages, database dumps, ML model files) and explicit per-file ignores for 21 files >50 MB.

### Changed
- Rewrote **~830 markdown links** across 72 curation files to point from `https://github.com/<owner>/<repo>` to `./repos/<owner>/<repo>` (or `../repos/...` from subdirectories), with `(local mirror)` annotation appended to link text.
- Updated License section to acknowledge that mirrored repos retain their original licenses.

### Not mirrored (42 repos)
- **Failed to download (16)**: `sajjadium/ctf-archives`, `p4-team/ctf`, `hackplayers/hackthebox-writeups`, `google/google-ctf`, `justcatthefish/justctf-2023`, `project-sekai-ctf/sekaictf-2024`, `daffainfo/ctf-writeup`, `MartinPetkov/GCTF2021BeginnersQuestWriteups`, `SECCON/SECCON13_final_CTF`, `SandWithCheese/ctf-writeups`, `Tan-JunWei/CTF-Writeups`, `mephi42/ctf`, `shekkbuilder/ctf-2`, `sigpwny/UIUCTF-2023-Public`, `silly-lily/CTF-Writeups`, `siunam321/CTF-Writeups`.
- **Downloaded but dropped (26)**: Largest repos (Adamkadaban/CTFs, Crusaders-of-Rust/*, DownUnderCTF/*, dicegang/*, justcatthefish/*, SecurityInnovation/Smart-Contract-CTF, osirislab/CSAW-*, lieanu/LibcSearcher, Kasimir123/CTFWriteUps, 1GN1tE/CTF_Writeups, Nautilus-Institute/quals-2024, RasyidMF/ctf-writeup, HackTricks-wiki/hacktricks, Ferdibrgl/cyber-apocalypse-ctf--2023-2024-, david942j/*) — excluded to fit within the 10 GB disk and GitHub push size constraints of the generation environment.
- Links to all 42 repos remain unchanged (pointing to upstream GitHub).

## [2026-07-09] — Initial Curation

### Added
- Initial repository scaffold with MIT license, code of conduct, contribution guide, and changelog.
- Master `README.md` with project overview, navigation table, and usage recommendations.
- `00-start-here/` onboarding track for newcomers: learning path, tools cheat sheet, top-10 recommended repos.
- 13 category directories (`01-pwn/` through `13-network-pcap/`), each with a curated README, recommended repositories table, and sub-topic deep dives.
- `20-events/` cross-index: 25+ event-specific pages covering DEF CON CTF, Google CTF, picoCTF, HackTheBox, TryHackMe, CSAW, PlaidCTF, hxp, 0CTF/TCTF, DiceCTF, corCTF, UIUCTF, SekaiCTF, HitCon, SECCON, RealWorldCTF, idekCTF, justCTF, Paradigm CTF, and more.
- `30-archetypes/` cross-index: 7 archetype pages (personal collections, team archives, event-organizer sources, aggregators, awesome-lists, practice platforms, toolkits).
- `40-tooling/` reference: 7 tool pages covering pwn, reverse engineering, crypto, web, forensics, blockchain, and mobile tooling.
- `50-writeups-by-year/` temporal index: per-year pages from 2013 to 2026.
- `99-appendix/` reference material: full 376-source index, methodology, glossary, and FAQ.
- Total curated sources: 376 across 5 platforms (GitHub, Medium, YouTube, CTFtime, blogs).
