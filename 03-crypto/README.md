# Cryptography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

From classical ciphers (Caesar, Vigenère) to modern attacks on RSA (Bleichenbacher, Coppersmith, Hastad), ECC (invalid curve, Pohlig-Hellman), lattice-based schemes (LLL, Coppersmith), and bespoke cryptographic constructions. The most mathematically demanding category; SageMath is the dominant solution tool.

This category contains **66 curated sources** from across the CTF ecosystem: 50 the collection repositories, 11 Medium articles, 1 YouTube video walkthroughs, 1 CTFtime event entries, and 3 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond the collection repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [picoCTF Cryptography Track Write-up: Cheese, Ciphers & Cracked](https://medium.com/@akumar54/picoctf-cryptography-track-write-up-cheese-ciphers-cracked-keys-c6908c2dca75) | ✍️ Medium | n/a | Whether you're a fellow CTF participant or just curious about cryptographic puzzles, I hope these write-ups provide bot… |
| 2 | [Crypto CTF 2020: Classic Writeup - CTFtime](https://ctftime.org/writeup/23014) | 🏆 CTFtime | 2020–2020 | This is my first time joining a CTF that is purely focused on cryptography. As I saw the challenges, I was discouraged … |
| 3 | [PlaidCTF 2023 Writeups - siunam's Website](https://siunam321.github.io/ctf/PlaidCTF-2023) | 📝 Blog | 2023–2023 | The Plaid Flag is the 2023 edition of PlaidCTF, an annual capture the flag competition run by PPP. Categories: web; rev… |
| 4 | [CTF-Writeups - crypto](https://saurav3199.github.io/CTF-writeups/DragonSectorCTF) | 📝 Blog | 2020–2020 | CTF-Writeups. Writeups for the past CTF challenges. View. Writeup for solved challenge in DragonSectorCTF 202… |
| 5 | [Forensics & Steganography Challenges — CTF Writeups](https://medium.com/@santhoshr3512/forensics-steganography-challenges-ctf-writeups-0f71112ddf4a) | ✍️ Medium | n/a | This challenge shows how visual cryptography can hide data across multiple images. Individually the images appear as ra… |
| 6 | [CTF Challenges: Cryptography-101 - ROHIT CHOUHAN - Medium](https://rohit170590.medium.com/ctf-challenges-cryptography-101-cc56156662ca) | ✍️ Medium | n/a | The Caesar Cipher is a very simple and common encryption method which does not appear often in full-fledged CTFs but fo… |
| 7 | [Midnight Flag CTF Writeups (Forensics, Web3, Crypto, Reverse)](https://medium.com/@shoaibbinrashid11/midnight-flag-ctf-writeups-forensics-web3-crypto-reverse-9e8e49e36153) | ✍️ Medium | n/a | The solver uses an Overbeck-style method to remove the “distortion” and decode. · The decoded message becomes an AES ke… |
| 8 | [LA CTF WriteUp - Medium](https://medium.com/@rizkidsaputra9/la-ctf-writeup-d3a5b065d7dd) | ✍️ Medium | n/a | LA CTF is an exciting cybersecurity competition that tests participants in various challenges, including web exploitati… |
| 9 | [squ1rrel CTF 2024 writeup for Cryptography Challenges - Medium](https://medium.com/@jooelsaka/squ1rrel-ctf-2024-writeup-for-cryptography-challenges-16d7cb77e8ce) | ✍️ Medium | 2024–2024 | Hello It's me youssef a Web/Cryptography CTF player from 0xL4ugh Team I'll be sharing my solutions for the crypto chall… |
| 10 | [ICMTC CTF — Cryptography Challenge Writeup “Simple Cipher”](https://medium.com/@motarekk/icmtc-ctf-cryptography-challenge-writeup-simple-cipher-b3047b0837a3) | ✍️ Medium | n/a | ICMTC CTF — Cryptography Challenge Writeup “Simple Cipher” Introduction Challenge's name indicates that it should be a … |
| 11 | [Houseplant CTF Write Up Part 2 - Medium](https://medium.com/zh3r0/houseplant-ctf-write-up-part-2-2abc1621510a) | ✍️ Medium | n/a | This part will covers some of the Cryptography challenges I did with our Team ZH3R0 for Houseplant CTF organized by Ric… |
| 12 | [UrchinSec Aware CTF 2024 Cryptography — All Challs Writeups](https://medium.com/@shikhargupta435/urchinsec-aware-ctf-2024-cryptography-all-challs-writeups-bba9430e94d3) | ✍️ Medium | 2024–2024 | From this post onwards I will try to cover challenges of each category in each post. This post is about the Cryptograph… |
| 13 | [How I Became the “Reverse Guy” in My CTF Team | by Rusty - Medium](https://rustybladez.medium.com/how-i-became-the-reverse-guy-in-my-ctf-team-c6fc2cef1512) | ✍️ Medium | n/a | I thought I'd become an all-rounder. Binary Exploitation, Cryptography, Forensics, OSINT, Reverse Engineering, you call… |
| 14 | [ICMTC CTF Finals — Cryptography Challenge Writeup “Broken RSA”](https://medium.com/@motarekk/icmtc-ctf-finals-cryptography-challenge-writeup-broken-rsa-3d6c1715027a) | ✍️ Medium | n/a | Challenge's name indicates a weakly-implemented RSA encryption that will lead to a vulnerability that could be exploite… |
| 15 | [CryptoHack Blog | Updates about the CryptoHack platform](https://blog.cryptohack.org) | 📝 Blog | n/a | Updates about the CryptoHack platform, cryptography news, and CTF writeups. |
| 16 | [DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn)](https://www.youtube.com/watch?v=CGbPWSVm99k) | ▶️ YouTube | 2024–2024 | DiceCTF 2024 Challenge Writeups (3x web, 1x crypto, 1x pwn) · Comments. |

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

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal the collection repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
