# Changelog

All notable changes to this CTF-collection repository are documented in this file.

The format is loosely based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [2026-07-10] — Major: 3,135 Medium CTF Writeups Added

### Added
- **3,135 individual CTF writeup markdown files** sourced from Medium and InfoSecWriteups, organized across 11 category directories and 41 event directories.
- **41 CTF event pages** with dedicated writeup subdirectories (TryHackMe: 261, HackTheBox: 148, picoCTF: 86, and 38 more).
- **Updated all 11 category READMEs** with new Medium writeup tables linking to individual writeup files.
- **New writeup file format** with consistent metadata header (source, platform, category, event, year) and direct link to original Medium article.
- Categories now contain: Web (841), Misc (971), Crypto (107), Forensics (87), OSINT (71), Blockchain (70), Reverse (52), Pwn (50), Hardware (44), Mobile (34), Network (3).

### Changed
- **README.md** updated: total sources badge from 364 to 3,499+, category distribution table now reflects Medium writeup counts, event section updated.
- **Repository structure** annotations updated to show writeup counts per category.
- **20-events/README.md** rebuilt as a comprehensive index of all 41 events with writeup counts.

### Stats
- Total writeup files: 3,135 (2,330 in category directories, 799 in event directories)
- Total curated sources: 3,499+ (was 364)
- Events with dedicated writeups: 41 (was 25+)

## [2026-07-10] — Markdown Cleanup and Polish

### Changed
- **Comprehensive cleanup of all 86 curation markdown files** — fixed prose, formatting, and consistency issues across the entire collection.
- Replaced all "the collection repositories" → "internal archives" (107 replacements across 61 files) — leftover artifacts from earlier automated replacements.
- Removed all "Contribute to X development by creating an account..." trailing descriptions from table cells (these were truncated GitHub page-scraped descriptions).
- Fixed heading capitalization: "## internal archives" → "## Internal Archives" across all year and event pages.
- Fixed "Resources not integrated (42)" heading → "(54)" to match the actual count.
- Fixed duplicate "into the collection into the collection" phrasing in README.md.
- Restored "GitHub" in methodology.md and full-repo-index.md where it refers to the platform (GitHub API, GitHub topics, GitHub Pages) rather than repos.
- Renumbered table rows to be sequential (1,2,3,...) after previous row deletions.
- Cleaned up excessive blank lines (3+ → 2) and trailing whitespace across all files.
- Ensured all files end with a single newline.

### Verified
- Zero "the collection" artifacts remaining (except legitimate "this collection" uses in README.md).
- Zero "Contribute to" descriptions remaining.
- Zero broken markdown link syntax (`[X[Y` patterns).
- Zero lowercase "## internal archives" headings.
- All category READMEs have consistent section structure: Overview, Curated Articles, Sub-Topic Deep Dive, Suggested Learning Order, See Also.

## [2026-07-10] — Remove Recommended/Featured Repository Sections

### Removed
- **"Top Featured Repositories" section** from `README.md` — the curated list of 20 top repos with star counts and descriptions.
- **"Recommended Repositories (the collection)" sections** from all 13 category READMEs (`01-pwn/` through `13-network-pcap/`) — each contained 20-30 repo entries with stars, difficulty, year range, and annotations.
- **`00-start-here/recommended-repos.md`** — the standalone "Top 10 Recommended Repositories" page, including its table and "How to use these" guidance.
- **References to `recommended-repos.md`** from `README.md` (directory tree and "How to Use" section) and `00-start-here/README.md` (file listing table).

### Impact
- 14 sections removed across 14 markdown files.
- 64 files had references to `recommended-repos.md` cleaned up.
- The collection's curation files now focus on curated articles, walkthroughs, sub-topic deep dives, and event/archetype indexes — no standalone repo recommendation tables remain.
- All archived resources remain accessible via their `archives/` subdirectories within each category.

## [2026-07-10] — Quality Filter: Professional Writeups Only

### Changed
- **Filtered writeup repos to keep only professional writeups** — repos that include screenshots or videos showing the challenge being solved. Text-only answer repos were removed.
- Deleted 12 text-only writeup repos that had no visual content (no images, no videos, no YouTube references):
  - `01-pwn/archives/Pwn-College`
  - `01-pwn/archives/Pwnbooks-BinaryExploitation`
  - `02-web/archives/owasp-ctf-2025`
  - `07-misc/archives/misfortune-ctf-challenge`
  - `08-blockchain-web3/archives/2020-paradigm-ctf-writeup`
  - `20-events/archives/picoctf/picoCTF-2024-Writeup`
  - `20-events/archives/realworldctf/RWCTF-5th-Challenges`
  - `20-events/archives/seccon-ctf/SECCON13-online-CTF`
  - `30-archetypes/archives/personal-collections/CTF-Writeups-tl2cents`
  - `30-archetypes/archives/personal-collections/CTFWriteups-rkm0959`
  - `30-archetypes/archives/personal-collections/ctf-writeups-mbiesiad`
  - `30-archetypes/archives/personal-collections/ctf-writeups-sajjadium`
- Removed 69 table rows and neutralized 8 links across 42 curation files that referenced the deleted repos.
- Updated README.md with new counts (114 → 102 integrated resources) and added "Quality filter" section.
- Tools, awesome-lists, challenge source releases, and practice platforms (39 repos) were retained — they are not writeups and the visual-content filter does not apply to them.

### Final collection state
- **63 writeup repos with visual content** (screenshots/videos of solves)
- **39 non-writeup repos** (tools, lists, sources, platforms)
- **102 total integrated resources**
- **54 resources not integrated** (42 size/access + 12 text-only filtered)

## [2026-07-10] — Unified Self-Contained Collection

### Changed
- Transformed into a fully self-contained collection — all external repository links removed or converted to internal paths.
- Renamed all `mirrors/` subdirectories to `archives/`.
- Removed all "mirror"/"mirrored" language from prose.
- Updated README.md, CONTRIBUTING.md, CHANGELOG.md, methodology.md.
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
- `99-appendix/` reference material: full 364-source index, methodology, glossary, and FAQ.
- Total curated sources: 364 across 5 platforms (Internal, Medium, YouTube, CTFtime, blogs).
