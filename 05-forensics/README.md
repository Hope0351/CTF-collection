# Forensics & Steganography

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Disk-image forensics, memory-dump analysis (Volatility), packet-capture analysis (Wireshark/tshark), and steganography (Aperi'Solve, zsteg, stegsolve). The category with the highest variance in challenge design — challenges range from trivial 'find the hidden flag in metadata' to sophisticated memory-malware-investigation scenarios.

## 🔬 Sub-Topic Deep Dive

The Forensics & Steganography category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### Disk image forensics

TSK, Autopsy, file carving.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [DominicBreuker/stego-toolkit: Collection of steganography tools](../40-tooling/archives/forensics-tools/stego-toolkit) — 📚 Repository
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository

### Memory forensics

Volatility — process list, network connections, malware extraction.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [TCP1P CTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/tcp1pctf2024) — 📝 Blog

### Steganography

LSB, audio stego, spectral stego, steghide, zsteg.

Top resources for this sub-topic:

- [DominicBreuker/stego-toolkit: Collection of steganography tools](../40-tooling/archives/forensics-tools/stego-toolkit) — 📚 Repository
- [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) — 📝 Blog
- [Forensics & Steganography Challenges — CTF Writeups](https://medium.com/@santhoshr3512/forensics-steganography-challenges-ctf-writeups-0f71112ddf4a) — ✍️ Medium
- [ICTF 2025 Writeup - Medium](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) — ✍️ Medium

### Network forensics

pcap analysis, protocol reconstruction, traffic anomaly detection.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [Writeup - ComCyber Recrutement CTF - Root-Me Blog](https://blog.root-me.org/posts/writeup_comcyber) — 📝 Blog

### Metadata forensics

EXIF, document metadata, OLE structures.

Top resources for this sub-topic:

- [Yet another CTF writeups repository. PWN and RE tasks - the collection](../30-archetypes/archives/personal-collections/ctf-writeups-merrychap) — 📚 Repository
- [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) — ✍️ Medium
- [CTF-Writeups - the collection](../30-archetypes/archives/personal-collections/CTF-Writeups-0xETX) — 📚 Repository
- [stefanman125/root-me-challenges - the collection](../30-archetypes/archives/practice-platforms/root-me-challenges) — 📚 Repository
- [TCP1P CTF 2024 - Writeups - warlocksmurf](https://warlocksmurf.github.io/posts/tcp1pctf2024) — 📝 Blog

## 🎯 Suggested Learning Order

If you're new to forensics & steganography, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with HackTheBox's forensics challenges (easy tier), then read the Volatility documentation and work through memory-dump challenges.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
