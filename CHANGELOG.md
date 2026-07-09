# Changelog

All notable changes to this CTF-collection repository are documented in this file.

The format is loosely based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [2026-07-10] — Mirror Restructure

### Changed
- **Restructured all 114 mirrored repos** from the flat `repos/<owner>/<repo>/` layout into a category-organized `<category>/mirrors/[<subtype>/]<repo-name>/` structure. The upstream owner prefix has been removed from directory paths; repos are now organized by their primary CTF category.
- Removed `(local mirror)` annotation from all link text (812 annotations removed). Links now read naturally, e.g., `[apsdehal/awesome-ctf](30-archetypes/mirrors/awesome-lists/awesome-ctf)`.
- Rewrote 809 markdown links across 72 curation files to point to new mirror locations with correct relative paths.
- Updated README.md "Mirrored Repositories" section with the new structure diagram and layout details.
- Updated License section to reference `mirrors/` subdirectories within each category instead of the old `repos/` directory.

### New mirror structure
- `01-pwn/mirrors/` — 5 pwn learning resources
- `02-web/mirrors/` — 4 web challenge repos
- `03-crypto/mirrors/` — 2 crypto writeup repos
- `06-osint/mirrors/` — 2 OSINT challenge repos
- `07-misc/mirrors/` — 2 misc challenge repos
- `08-blockchain-web3/mirrors/` — 5 blockchain/Web3 repos
- `10-hardware-iot/mirrors/` — 1 hardware repo
- `20-events/mirrors/<event>/` — 30 event-specific repos across 13 events (picoCTF, HackTheBox, DEF CON, SECCON, etc.)
- `30-archetypes/mirrors/<type>/` — 39 repos (awesome-lists, personal-collections, team-archives, practice-platforms, event-organizer-sources)
- `40-tooling/mirrors/<tool-type>/` — 24 tool repos (pwn-tools, web-tools, forensics-tools, blockchain-tools, mobile-tools, crypto-tools, misc-tools)

### Removed
- Deleted the old `repos/` top-level directory (all content moved into category `mirrors/` subdirectories).

## [2026-07-09] — Mirror Import (superseded by 2026-07-10 restructure)

### Added
- `repos/` top-level directory containing **local mirrors of 114 GitHub repositories** referenced throughout the collection (~2.5 GB on disk after `.gitignore` filtering).
- Expanded `.gitignore` with CTF-specific binary artifact patterns.
- "Local Mirrors" section in README.md documenting the mirror structure (now superseded).

### Changed
- Rewrote markdown links to point to `./repos/<owner>/<repo>` with `(local mirror)` annotation (superseded — links now point to category-organized `mirrors/` subdirectories without annotation).

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
