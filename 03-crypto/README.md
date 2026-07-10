# Cryptography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

From classical ciphers (Caesar, Vigenère) to modern attacks on RSA (Bleichenbacher, Coppersmith, Hastad), ECC (invalid curve, Pohlig-Hellman), lattice-based schemes (LLL, Coppersmith), and bespoke cryptographic constructions. The most mathematically demanding category; SageMath is the dominant solution tool.

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
