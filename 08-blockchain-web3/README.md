# Blockchain & Web3

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Smart-contract exploitation on Ethereum-compatible chains and increasingly on Solana, Move, and zero-knowledge VMs. Sub-vulnerabilities include reentrancy, integer overflow/underflow, access-control flaws, flash-loan exploits, oracle manipulation, and signature-replay attacks. Foundry has displaced Hardhat as the dominant exploit-development framework.

This category contains **36 curated sources** from across the CTF ecosystem: 26 the collection repositories, 6 Medium articles, 0 YouTube video walkthroughs, 1 CTFtime event entries, and 3 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond the collection repositories, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [CTFtime.org / Writeups](https://ctftime.org/writeups) | 🏆 CTFtime | 2026–2026 | Open World, blockchain sekaictf2026 writeup sekaictf ctf, Abdelkader · Read ; V1T CTF 2026 · Duck, ctf misc v1t v1tctf … |
| 2 | [TON CTF Writeup - Amber Group - Medium](https://ambergroup.medium.com/ton-ctf-writeup-afdff959433b) | ✍️ Medium | n/a | Unlike Solidity on EVM blockchains, TON smart contracts are written using Tact or FunC. To interact with the blockchain… |
| 3 | [Enterprise Blockchain - Chictf-Writeups](https://yanhuijessica.github.io/Chictf-Writeups/blockchain/paradigm/enterprise_blockchain) | 📝 Blog | n/a | Smart Contract Solutions is proud to introduce the only Enterprise Blockchain that you'll ever need. Challenge Files. S… |
| 4 | [Writeup :: teddyctf - teddy / TheSavageTeddy](https://thesavageteddy.github.io/tags/writeup) | 📝 Blog | 2025–2025 | I managed to get the first blood prizes for both Solidity / EVM Blockchain challenges from Sekai CTF 2025, here are the… |
| 5 | [Midnight Flag CTF Writeups (Forensics, Web3, Crypto, Reverse)](https://medium.com/@shoaibbinrashid11/midnight-flag-ctf-writeups-forensics-web3-crypto-reverse-9e8e49e36153) | ✍️ Medium | n/a | The solver uses an Overbeck-style method to remove the “distortion” and decode. · The decoded message becomes an AES ke… |
| 6 | [The Ethernaut - Medium](https://medium.com/@binnaryninjax/the-ethernaut-ecd7d1f7ee13) | ✍️ Medium | n/a | To solve this CTF you need to set up few things. Like setting up .env and foundary.toml files to link our wallet in sep… |
| 7 | [[CTF Writeup] DownUnderCTF 2023 Writeups | by zzzmilky - Medium](https://medium.com/@zzzmilky/downunderctf-2023-writeups-533dd6546c28) | ✍️ Medium | 2023–2023 | Without knowing what to do with the information, I found a smart contract development toolchain named “Foundry” (https:… |
| 8 | [Web3 Hacking: Paradigm CTF 2022 Writeup | by Amber Group](https://medium.com/amber-group/web3-hacking-paradigm-ctf-2022-writeup-3102944fd6f5) | ✍️ Medium | 2022–2022 | Paradigm CTF is one of the most challenging Web3-focused security competitions — amazing for blockchain security folks,… |
| 9 | [Sherlock blockchain CTF challenge — Writeup | by Luke - Medium](https://luk3tech.medium.com/sherlock-blockchain-ctf-challenge-writeup-c2f61a0c7585) | ✍️ Medium | n/a | Here's my first writeup of a blockchain security challenge. Solving it allowed me to learn about accessing and inspecti… |
| 10 | [Chovid99's Blog](https://chovid99.github.io) | 📝 Blog | 2024–2024 | 28 minutes. Writeup, GreyCTF, Blockchain, Evm, Uniswap · 0CTF 2024. Writeup for 0CTF 2024. Dec 23, 2024 · ... |

## 🔬 Sub-Topic Deep Dive

The Blockchain & Web3 category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Reentrancy

the canonical Solidity vulnerability;DAO-style recursive calls.

*No directly-matching resources in this collection — consult the broader category list above.*

### Integer overflow/underflow

pre-0.8.0 Solidity; SafeMath bypass.

*No directly-matching resources in this collection — consult the broader category list above.*

### Access control flaws

missing onlyModifier, public storage leakage.

Top resources for this sub-topic:

- [Sherlock blockchain CTF challenge — Writeup | by Luke - Medium](https://luk3tech.medium.com/sherlock-blockchain-ctf-challenge-writeup-c2f61a0c7585) — ✍️ Medium

### Flash loan exploits

manipulating oracles via borrowed capital.

Top resources for this sub-topic:

### Oracle manipulation

price-feed manipulation, single-block TWAP.

*No directly-matching resources in this collection — consult the broader category list above.*

### Signature replay

ECDSA signature malleability, cross-chain replay.

*No directly-matching resources in this collection — consult the broader category list above.*

### MEV / sandwich attacks

front-running, back-running, JIT liquidity.

Top resources for this sub-topic:

- [CTFtime.org / Writeups](https://ctftime.org/writeups) — 🏆 CTFtime
- [r3kapig/writeup: CTF challenges writeup - the collection](../30-archetypes/archives/team-archives/writeup-r3kapig) — 📚 Repository
- [blockthreat/blocksec-ctfs - the collection](../30-archetypes/archives/awesome-lists/blocksec-ctfs) — 📚 Repository
- [Hack The Box Writeups - The Ultimate HTB Resource - the collection](../20-events/archives/hackthebox/htb-writeups) — 📚 Repository
- [orangetw/My-CTF-Web-Challenges - the collection](../02-web/archives/My-CTF-Web-Challenges) — 📚 Repository

## 🎯 Suggested Learning Order

If you're new to blockchain & web3, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [Ethernaut](https://ethernaut.openzeppelin.com/) — work through all 28 levels. Then move to [Damn Vulnerable DeFi](https://www.damnvulnerabledefi.xyz/) for DeFi-specific challenges.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal the collection repository — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
