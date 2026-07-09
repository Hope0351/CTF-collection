# Toolkits

> Part of **CTF-collection** — see [`30-archetypes/README.md`](README.md) for the full archetype index.

## Overview

Reusable infrastructure for solving CTF challenges — typically Docker images pre-loaded with the standard toolset for a specific category.

Toolkit repositories are the tooling layer of the ecosystem and are commonly referenced in writeups. `dominicbreuker/stego-toolkit` is the canonical example: a Docker image purpose-built for steganography challenges.

## Curated Repositories (0)

| # | Repository | Stars | Categories | Year Range | Why It Matters |
|---:|---|---:|---|---|---|


## How to Use These Repositories

Toolkits are best used as **environment setup shortcuts**. Rather than installing each tool individually on your system, you can pull a toolkit Docker image and have a complete, isolated CTF environment ready in seconds.

`dominicbreuker/stego-toolkit` is the canonical example: a Docker image pre-loaded with every common steganography tool. The same pattern can be replicated for other categories — pwn, forensics, RE — though few pre-built toolkit images exist for those.

## See Also

- [`30-archetypes/README.md`](README.md) — full archetype index
- [`../99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — complete corpus
