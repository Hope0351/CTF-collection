# 📚 Repository Archetypes — Cross-Index

> Part of **CTF-collection** — see [master README](../README.md) for context.

This directory cross-indexes the corpus by repository archetype. The 376 sources in this collection classify into seven structural archetypes (a single repository may belong to multiple).

## Archetype Overview

| # | Archetype | Description | Page |
|---:|---|---|---|
| 1 | Personal Writeup Collections | Individual players' writeup archives. The bulk of the ecosystem by count; quality varies enormously… | [`personal-collections.md`](personal-collections.md) |
| 2 | Team Writeup Archives | Aggregated writeups from competitive CTF teams. Among the highest-signal sources in the ecosystem b… | [`team-archives.md`](team-archives.md) |
| 3 | Event-Organizer Challenge Source Releases | The actual challenge source code, deployment infrastructure, and intended-solution writeups publish… | [`event-organizer-sources.md`](event-organizer-sources.md) |
| 4 | Aggregators / Archives | Repositories that collect and organize CTF challenges and/or writeups from many events. Unlike awes… | [`aggregators.md`](aggregators.md) |
| 5 | Awesome-Lists / Resource Directories | Curated directories of CTF resources — frameworks, tools, writeups, practice platforms, and learnin… | [`awesome-lists.md`](awesome-lists.md) |
| 6 | Practice Platforms / Wargames | Repositories (or the backends for web platforms) that host always-on challenges designed for self-p… | [`practice-platforms.md`](practice-platforms.md) |
| 7 | Toolkits | Reusable infrastructure for solving CTF challenges — typically Docker images pre-loaded with the st… | [`toolkits.md`](toolkits.md) |

## Why Archetype Matters

A practitioner's use-case determines which archetype they should consult first:

- **Newcomers** should start with `practice-platforms.md` and `awesome-lists.md`.
- **Intermediate players** should consult `personal-collections.md` for portfolio models.
- **Elite competitors** should consult `team-archives.md` and `event-organizer-sources.md`.
- **CTF organizers** should consult `event-organizer-sources.md` for publication models.
- **Security researchers** should consult `aggregators.md` for corpus-scale datasets.
- **Tool builders** should consult `toolkits.md` for existing infrastructure.
