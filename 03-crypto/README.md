# Cryptography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

From classical ciphers (Caesar, Vigenère) to modern attacks on RSA (Bleichenbacher, Coppersmith, Hastad), ECC (invalid curve, Pohlig-Hellman), lattice-based schemes (LLL, Coppersmith), and bespoke cryptographic constructions. The most mathematically demanding category; SageMath is the dominant solution tool.

This category contains **66 curated sources** from across the CTF ecosystem: 50 internal archives, 11 Medium articles, 1 YouTube video walkthrough, 1 CTFtime event entries, and 3 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Difficulty |
|---:|---|---|
| 1 | [picoCTF Cryptography Track Write-up: Cheese, Ciphers & Cracked](https://medium.com/@akumar54/picoctf-cryptography-track-write-up-cheese-ciphers-cracked-keys-c6908c2dca75) | Beginner |
| 2 | [Crypto CTF 2020: Classic Writeup](https://ctftime.org/writeup/23014) | Elite |
| 3 | [PlaidCTF 2023 Writeups](https://siunam321.github.io/ctf/PlaidCTF-2023) | — |
| 4 | [CTF-Writeups - crypto](https://saurav3199.github.io/CTF-writeups/DragonSectorCTF) | — |
| 5 | [CTF Challenges: Cryptography-101](https://rohit170590.medium.com/ctf-challenges-cryptography-101-cc56156662ca) | Beginner |
| 6 | [Midnight Flag CTF Writeups (Forensics, Web3, Crypto, Reverse)](https://medium.com/@shoaibbinrashid11/midnight-flag-ctf-writeups-forensics-web3-crypto-reverse-9e8e49e36153) | — |
| 7 | [LA CTF WriteUp](https://medium.com/@rizkidsaputra9/la-ctf-writeup-d3a5b065d7dd) | — |
| 8 | [squ1rrel CTF 2024 Writeup for Cryptography Challenges](https://medium.com/@jooelsaka/squ1rrel-ctf-2024-writeup-for-cryptography-challenges-16d7cb77e8ce) | — |
| 9 | [ICMTC CTF — Cryptography Challenge Writeup "Simple Cipher"](https://medium.com/@motarekk/icmtc-ctf-cryptography-challenge-writeup-simple-cipher-b3047b0837a3) | Beginner |
| 10 | [Houseplant CTF Write Up Part 2](https://medium.com/zh3r0/houseplant-ctf-write-up-part-2-2abc1621510a) | — |
| 11 | [UrchinSec Aware CTF 2024 Cryptography — All Challs Writeups](https://medium.com/@shikhargupta435/urchinsec-aware-ctf-2024-cryptography-all-challs-writeups-bba9430e94d3) | — |
| 12 | [ICMTC CTF Finals — Cryptography Challenge Writeup "Broken RSA"](https://medium.com/@motarekk/icmtc-ctf-finals-cryptography-challenge-writeup-broken-rsa-3d6c1715027a) | — |
| 13 | [CryptoHack Blog | Updates about the CryptoHack Platform](https://blog.cryptohack.org) | Beginner |
| 14 | [DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn)](https://www.youtube.com/watch?v=CGbPWSVm99k) | Advanced |

## 🔬 Sub-Topic Deep Dive

The Cryptography category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### RSA attacks

small e, common modulus, Wiener, Bleichenbacher, Coppersmith, Hastad.

*No directly-matching resources in this collection — consult the broader category list above.*

### Elliptic Curve Cryptography

invalid curve, Pohlig-Hellman, anomalous curves, Smart's attack.

Top resources for this sub-topic:

- [picoCTF Cryptography Track Write-up: Cheese, Ciphers & Cracked](https://medium.com/@akumar54/picoctf-cryptography-track-write-up-cheese-ciphers-cracked-keys-c6908c2dca75) — ✍️ Medium
- [hackthebox/cyber-apocalypse-2025: Official writeups for  - the collection](../20-events/archives/hackthebox/cyber-apocalypse-2025) — 📚 Repository
- [CryptoHack CTF Archive - the collection](../03-crypto/archives/cryptohack-archive) — 📚 Repository

### Lattice-based cryptography

LLL reduction, Coppersmith's method, hidden number problem.

Top resources for this sub-topic:

- [picoCTF Cryptography Track Write-up: Cheese, Ciphers & Cracked](https://medium.com/@akumar54/picoctf-cryptography-track-write-up-cheese-ciphers-cracked-keys-c6908c2dca75) — ✍️ Medium
- [CryptoHack CTF Archive - the collection](../03-crypto/archives/cryptohack-archive) — 📚 Repository

### Block cipher modes

ECB block reordering, CBC padding oracle, bit-flipping.

Top resources for this sub-topic:

- [blockthreat/blocksec-ctfs - the collection](../30-archetypes/archives/awesome-lists/blocksec-ctfs) — 📚 Repository
- [A summary and solutions for 200+ CTF blockchain challenges - the collection](../08-blockchain-web3/archives/ctf-blockchain) — 📚 Repository
- [picoCTF Cryptography Track Write-up: Cheese, Ciphers & Cracked](https://medium.com/@akumar54/picoctf-cryptography-track-write-up-cheese-ciphers-cracked-keys-c6908c2dca75) — ✍️ Medium

### Hash functions

length extension, collision attacks, rainbow tables.

*No directly-matching resources in this collection — consult the broader category list above.*

### Diffie-Hellman

Pohlig-Hellman, small subgroup attacks, number field sieve.

*No directly-matching resources in this collection — consult the broader category list above.*

## 🎯 Suggested Learning Order

If you're new to cryptography, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [CryptoHack](https://cryptohack.org/) — work through the Introduction, Block Ciphers, Asymmetric Cryptography, and Elliptic Curves modules.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
