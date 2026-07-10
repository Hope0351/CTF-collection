# 📋 Methodology

> Part of **CTF-collection** — see [`99-appendix/full-repo-index.md`](full-repo-index.md) for the corpus this methodology produced.

## Search Strategy

The CTF-collection corpus was compiled via 86 web-search queries across 8 thematic axes. The queries were designed to maximize coverage of the CTF writeup landscape from different angles, so that resources organically surfaced by multiple independent searches would emerge as the most-recognized center-of-gravity nodes.

### The 8 Thematic Axes

1. **Awesome-list / aggregator queries** — generic searches for curated CTF resource lists, designed to surface the well-known awesome-ctf style directories that themselves reference hundreds of downstream writeup repositories.

2. **Per-category queries** — one targeted search per major CTF category (pwn, web, crypto, reverse engineering, forensics, OSINT, blockchain/Web3, misc, hardware/IoT, mobile, ICS/SCADA). These identify specialist resources that may not appear in generic CTF searches.

3. **Per-event queries** — searches for writeups of the most prestigious or well-documented CTF events: DEF CON CTF, Google CTF, picoCTF, HackTheBox (including Cyber Apocalypse), TryHackMe, CSAW CTF, PlaidCTF, hxp CTF, 0CTF/TCTF, DiceCTF, corCTF, UIUCTF, SekaiCTF, HitCon CTF, SECCON CTF, RealWorldCTF, idekCTF, justCTF, BambooFox CTF, Paradigm CTF, DownUnderCTF, NahamCon, MapnaCTF, WaniCTF, TCP1P CTF, bi0sCTF, and others.

4. **Per-team queries** — searches for writeup archives from historically top-placing CTF teams (p4/team, r3kapig, dicegang, Crusaders-of-Rust, justcatthefish, Plaid Parliament of Pwning, Dragon Sector, etc.).

5. **Per-author queries** — searches for writeup collections from well-known CTF educators and content creators (LiveOverflow, 0xdf, John Hammond, Crypto-Cat, IppSec).

6. **Per-platform queries** — searches for writeups of the major practice platforms: pwn.college, HackTheBox, TryHackMe, picoCTF (which doubles as both an event and a practice platform), CryptoHack, pwnable.kr/tw, Root-Me, OverTheWire, HackThisSite.

7. **GitHub topic queries** — searches targeting GitHub's own topic taxonomy (`ctf-writeup`, `ctf-challenges`, `awesome-ctf`), which surface repositories that authors have explicitly tagged.

8. **Year-range queries** — searches filtered to 2023–2026 to capture the current state of the writeup ecosystem, complementing the all-time queries.

## De-duplication and Ranking

Each search returned up to 20 results. After extracting repository URLs with a strict regex filter (excluding blob/tree/issues/pull paths and utility pages like /topics, /trending, /explore), all mentions were normalized to canonical `owner/repo` form and de-duplicated. Each source was then scored along two axes:

- **`distinct_search_count`** — the number of distinct search queries (out of 86) in which the source appeared. This is the strongest signal of cross-context relevance.
- **`mention_count`** — the total number of times the source appeared across all searches (including multiple appearances within a single search).

Sources were sorted by `(distinct_search_count, mention_count)` descending.

## Source Classification

Each source was classified into one of five source types based on its URL:

| Source Type | Detection |
|---|---|
| **Repository** | Path matches `<owner>/<repo>` |
| **Medium Article** | URL contains `medium.com` |
| **YouTube Video** | URL matches `youtube.com/watch?v=` or `youtu.be/` |
| **CTFtime Entry** | URL contains `ctftime.org` |
| **Blog Post** | URL is on a known security blog (0xdf.gitlab.io, ippsec.rocks, hacktricks.xyz, portswigger.net, etc.) or a personal domain ending in `.gitlab.io`, `.github.io`, `.vercel.app`, `.netlify.app` |

## Metadata Enrichment

For each GitHub source, the GitHub REST API was queried (authenticated via PAT, 5000 req/hour rate limit) to fetch:

- `stargazers_count` — star count
- `forks_count` — fork count
- `language` — primary language
- `license.spdx_id` — license identifier (e.g., MIT, GPL-3.0)
- `description` — short description
- `created_at`, `updated_at`, `pushed_at` — timestamps
- `topics` — repository topics
- `homepage` — homepage URL (if any)
- `size` — repository size in KB
- `default_branch` — default branch name
- `archived`, `is_template`, `has_wiki`, `has_issues` — boolean flags

For non-GitHub sources, the search snippet and title were used for categorization.

## Categorization

Categories were detected via keyword matching against titles and snippets. The category pattern list covers 15 distinct categories: Pwn, Web, Crypto, Reverse Engineering, Forensics, OSINT, Misc, Blockchain, Mobile, Hardware, ICS/SCADA, Cloud, Network/Pcap, Stego, Programming. A source may match multiple categories.

CTF events were detected via a curated pattern list of 50+ known events, including all S-tier and A-tier events.

Years were extracted via regex matching for 4-digit numbers in the 2013–2026 range.

## Difficulty Assessment

Difficulty was assessed heuristically based on the presence of tier-indicating keywords:

- **Beginner**: keyword matches for "beginner", "picoCTF", "pwn.college", "TryHackMe", "starter", "noob", "easy"
- **Elite**: keyword matches for "DEF CON", "0CTF", "hxp", "RealWorldCTF", "PlaidCTF", "Paradigm CTF", "Google CTF", "quals"
- **Advanced**: keyword matches for "DiceCTF", "corCTF", "justCTF", "SekaiCTF", "SECCON", "HitCon", "CSAW"
- **Intermediate**: keyword matches for "intermediate", "medium", "HackTheBox"
- **Varied**: default when no tier-indicating keyword is present

## Limitations

1. **Search-result cap.** Each of the 86 queries returned at most 20 results, yielding a theoretical ceiling of 1,720 raw mentions. After de-duplication, 364 unique sources were identified. The long tail of smaller personal archives (likely numbering in the tens of thousands) is not enumerated here; a more exhaustive enumeration would require direct use of the GitHub Search API.

2. **GitHub README fetch.** Initial attempts to use a generic page-reader CLI hit rate limits after ~3 successful fetches. The fallback approach — fetching raw README files via curl from `raw.githubusercontent.com` — succeeded for 114 of 120 GitHub repos (95%).

3. **Category detection heuristic.** Category assignment is based on keyword matching against the title and snippet. A small fraction of assignments may be false positives.

4. **Star counts.** GitHub star counts were fetched via the authenticated API at one point in time. They are accurate as of the fetch date but will drift over time.

5. **Static analysis only.** All analysis is based on README content and search snippets. The actual writeup content within each resource was not fetched and analyzed at scale; per-resource quality assessments are inferred from README depth and category coverage rather than direct reading of individual writeup files.
