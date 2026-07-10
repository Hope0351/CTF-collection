# Event-Organizer Challenge Source Releases

> Part of **CTF-collection** — see [`30-archetypes/README.md`](README.md) for the full archetype index.

## Overview

The actual challenge source code, deployment infrastructure, and intended-solution writeups published by the teams that organized the event.

These are the gold standard for studying CTF challenges because they reveal the intended solve path. Since 2022, the trend toward same-day or next-day open-sourcing has accelerated sharply — Nautilus Institute (DEF CON), dicegang (DiceCTF), Crusaders-of-Rust (corCTF), justcatthefish (justCTF), and project-sekai-ctf (SekaiCTF) all now publish source within days of their events concluding.

## Curated Repositories (5)

| # | Repository | Stars | Categories | Year Range | Why It Matters |
|---:|---|---:|---|---|---|
| 1 | dicegang/dicectf-quals-2024-challenges | 30 ⭐ | Crypto, Reverse Engineering, Pwn | 2024–2024 | All challenges from DiceCTF Quals 2024.…|
| 2 | Nautilus-Institute/quals-2024 | 76 ⭐⭐ | — | 2024–2024 | This repository contains the open source release for Nautilus Institute's 2024 DEF CON CTF qualifier. We are releasing … |
| 3 | [nautilus-institute/finals-2025](../20-events/archives/def-con-ctf/DEFCON-finals-2025) | 32 ⭐ | — | 2025–2025 | This repository contains the open source release for Nautilus Institute's 2025 DEF CON Final. We are releasing all of t… |
| 4 | [Live-CTF/LiveCTF-DEFCON32](../20-events/archives/def-con-ctf/LiveCTF-DEFCON32) | 23 ⭐ | — | 2024–2024 | This repository contains infrastructure, challenges and solutions for the DEFCON32 LiveCTF. Qualifier Streams Finals Re… |
| 5 | dicegang/dicectf-quals-2025-challenges | 9 ⭐ | Crypto, Reverse Engineering, Pwn | 2025–2025 | All challenges from DiceCTF Quals 2025.…|

> **Note:** `r3kapig/writeup` was previously listed here but has been moved to [`team-archives.md`](team-archives.md) as it is a team writeup archive, not an event-organizer source.

## How to Use These Repositories

Event-organizer source releases are best used as **ground truth**. When studying a past CTF, always check whether the organizers have published the challenge source — if they have, that source is the authoritative reference for the intended solve path.

If you're organizing your own CTF, study the publication models used by Nautilus Institute, dicegang, Crusaders-of-Rust, justcatthefish, project-sekai-ctf, osirislab, SECCON, and chaitin. The standard pattern is: per-event repository, with per-challenge subdirectories containing `challenge/` (source), `deploy/` (infrastructure), and `solve/` (intended solution) folders.

## See Also

- [`30-archetypes/README.md`](README.md) — full archetype index
- [`../99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — complete corpus
