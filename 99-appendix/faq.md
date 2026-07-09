# ❓ FAQ — Frequently Asked Questions

> Part of **CTF-collection** — see [`99-appendix/full-repo-index.md`](full-repo-index.md) for the corpus.

## General

### Q: What is a CTF?

A CTF (Capture The Flag) is a security competition where participants solve challenges to find hidden "flags" — typically a string of the form `flag{...}` or `picoCTF{...}`. Challenges are organized into categories like pwn, web, crypto, reverse engineering, forensics, OSINT, and more. See [`00-start-here/README.md`](../00-start-here/README.md) for the full introduction.

### Q: I'm new to CTFs. Where do I start?

Read [`00-start-here/learning-path.md`](../00-start-here/learning-path.md). The short version: sign up at picoCTF, work through 20 beginner challenges, install pwntools and Ghidra, then follow the structured learning path.

### Q: Do I need to know how to code?

Yes — at minimum, basic Python. For most categories, you'll also need to read code in C, JavaScript, or assembly. The learning path in [`00-start-here/learning-path.md`](../00-start-here/learning-path.md) includes a Python fundamentals step.

### Q: What programming language should I learn first?

Python. It's the lingua franca of CTFs — used for pwntools (pwn), angr (RE), SageMath (crypto), requests/web scraping (web), and most exploit scripts.

### Q: How long does it take to get good at CTFs?

This depends on your starting point and how much time you invest. A reasonable estimate:

- **Beginner tier** (can solve easy picoCTF challenges): 1–2 months of evenings.
- **Intermediate tier** (can place in mid-tier CTFs): 6–12 months of consistent practice.
- **Advanced tier** (can place in top-tier CTFs): 2–3 years of consistent practice.
- **Elite tier** (can compete at DEF CON CTF level): 5+ years of consistent practice.

## Specific Categories

### Q: Which category should I specialize in?

Pick the one that matches your background:

- **Background in C / systems programming → Pwn**
- **Background in web development → Web**
- **Background in mathematics → Crypto**
- **Background in compilers / low-level → Reverse Engineering**
- **Background in networking → Network/Pcap or Cloud**
- **Background in Solidity / DeFi → Blockchain**

See [`00-start-here/learning-path.md`](../00-start-here/learning-path.md) Phase 3 for category-specific curricula.

### Q: Is pwn harder than web?

It depends on your background. Pwn has a steeper learning curve because it requires assembly, ABI details, and exploit-development tooling. Web has a broader surface area because there are more vulnerability classes. Most beginners find web easier to start with, but pwn rewards deeper investment.

### Q: Do I need to know assembly for CTFs?

For pwn and reverse engineering: yes. For web, crypto, forensics, OSINT, misc, blockchain, cloud: no (though it helps for some challenges).

### Q: Which CTFs should I play as a beginner?

- **picoCTF** — the canonical beginner CTF. Always-on.
- **TryHackMe** — structured learning with browser-based labs.
- **pwn.college** — structured pwn learning path.
- **OverTheWire Bandit** — Linux command-line fundamentals.
- **HackTheBox (easy tier)** — once you're comfortable with the basics.

### Q: Which CTFs should I play as an elite competitor?

DEF CON CTF (and its qualifier), Google CTF, hxp CTF, 0CTF/TCTF, RealWorldCTF, HitCon CTF, PlaidCTF. These are the S-tier events where the world's top teams compete.

## Tooling

### Q: What tools do I need to install?

See [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) for the condensed cheat sheet. The short version: pwntools, Ghidra, Burp Suite, Wireshark, Volatility, and a Linux VM.

### Q: Windows or Linux?

Linux. Ubuntu 22.04 LTS is the safe default. If you're on Windows, use WSL2 or run Linux in a VM.

### Q: Do I need IDA Pro?

No. Ghidra is free and comparable in capability for most CTF challenges. IDA Pro is the industry standard for professional reverse engineering, but it's expensive (~$2000/year for the cheapest commercial license) and unnecessary for CTFs.

### Q: pwntools or ropper?

Both. pwntools is the standard library for exploit development (sockets, packed integers, ROP chain builders, shellcraft). ropper is a specific tool for finding ROP gadgets. They complement each other.

## Contributing

### Q: Can I contribute to this collection?

Yes! See [`CONTRIBUTING.md`](../CONTRIBUTING.md). The short version: check for duplicates, use the standard entry format, open a pull request.

### Q: I found a broken link. What do I do?

Open an issue with the broken link and (if possible) the new URL. We'll fix it within a week.

### Q: My writeup repository isn't listed. Can I add it?

Yes — open a pull request adding it to the relevant category page(s). Use the standard entry format from [`CONTRIBUTING.md`](../CONTRIBUTING.md).

### Q: Can I translate this collection into another language?

Yes — the MIT license permits this. We recommend forking the repository and translating in the fork. If the translation is high-quality, let us know and we'll link to it from the main README.

## About This Repository

### Q: How was this collection compiled?

See [`99-appendix/methodology.md`](methodology.md). The short version: 86 web-search queries across 8 thematic axes, de-duplicated and ranked by cross-search relevance, enriched with the collection API metadata.

### Q: How often is this collection updated?

The initial curation was completed in July 2026. Ongoing updates depend on community contributions and maintainer availability. See [`CHANGELOG.md`](../CHANGELOG.md) for the change log.

### Q: Is this collection affiliated with any CTF organization?

No. This is an independent, community-maintained collection. It is not affiliated with DEF CON, Google, HackTheBox, or any other CTF organizer.
