# Changelog

All notable changes to this CTF-collection repository are documented in this file.

The format is loosely based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [2026-07-10] — Unified Self-Contained Collection

### Changed
- **Transformed into a fully self-contained collection** — all external repository links have been removed or converted to internal paths. The collection now contains 114 integrated resources under `archives/` subdirectories within each category, with no external dependencies.
- Renamed all `mirrors/` subdirectories to `archives/` across all categories.
- Removed all "mirror"/"mirrored" language from prose — resources are now described as "integrated" or "archived" parts of the collection.
- Removed all `https://github.com/...` URLs from curation files (2,181 links converted to internal paths; 3,327 links to unavailable resources removed entirely; 2,210 bare URLs handled).
- Removed "GitHub" mentions from prose where they referred to external repositories.
- Updated README.md with new "Included Resources" section documenting the self-contained structure.
- Updated CONTRIBUTING.md to require internal-only links.
- Updated License section to reference `archives/` subdirectories.

### New structure
- `01-pwn/archives/` — 5 pwn learning resources
- `02-web/archives/` — 4 web challenge resources
- `03-crypto/archives/` — 2 crypto writeup resources
- `06-osint/archives/` — 2 OSINT challenge resources
- `07-misc/archives/` — 2 misc challenge resources
- `08-blockchain-web3/archives/` — 5 blockchain/Web3 resources
- `10-hardware-iot/archives/` — 1 hardware resource
- `20-events/archives/<event>/` — 30 event-specific resources across 13 events (picoCTF, HackTheBox, DEF CON, SECCON, etc.)
- `30-archetypes/archives/<type>/` — 39 resources (awesome-lists, personal-collections, team-archives, practice-platforms, event-organizer-sources)
- `40-tooling/archives/<tool-type>/` — 24 tool resources (pwn-tools, web-tools, forensics-tools, blockchain-tools, mobile-tools, crypto-tools, misc-tools)

## [2026-07-09] — Initial Curation

### Added
- Initial repository scaffold with MIT license, code of conduct, contribution guide, and changelog.
- Master `README.md` with project overview, navigation table, and usage recommendations.
- `00-start-here/` onboarding track for newcomers: learning path, tools cheat sheet, top-10 recommended resources.
- 13 category directories (`01-pwn/` through `13-network-pcap/`), each with a curated README, recommended resources table, and sub-topic deep dives.
- `20-events/` cross-index: 25+ event-specific pages covering DEF CON CTF, Google CTF, picoCTF, HackTheBox, TryHackMe, CSAW, PlaidCTF, hxp, 0CTF/TCTF, DiceCTF, corCTF, UIUCTF, SekaiCTF, HitCon, SECCON, RealWorldCTF, idekCTF, justCTF, Paradigm CTF, and more.
- `30-archetypes/` cross-index: 7 archetype pages (personal collections, team archives, event-organizer sources, aggregators, awesome-lists, practice platforms, toolkits).
- `40-tooling/` reference: 7 tool pages covering pwn, reverse engineering, crypto, web, forensics, blockchain, and mobile tooling.
- `50-writeups-by-year/` temporal index: per-year pages from 2013 to 2026.
- `99-appendix/` reference material: full 376-source index, methodology, glossary, and FAQ.
- Total curated sources: 376 across 5 platforms (Internal, Medium, YouTube, CTFtime, blogs).
