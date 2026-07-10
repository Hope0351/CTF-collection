# Web Exploitation

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Server-side (SQLi, SSRF, SSTI, RCE, deserialization, file inclusion) and client-side (XSS, CSRF, prototype pollution) vulnerabilities, plus modern web3 integrations and bespoke web app exploitation. The broadest category, requiring fluency in HTTP, web frameworks, browser security model, and modern web tooling (Burp, semgrep, ffuf).

This category contains **82 curated sources** from across the CTF ecosystem: 53 internal archives, 12 Medium articles, 3 YouTube video walkthroughs, 0 CTFtime event entries, and 14 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Difficulty |
|---:|---|---|
| 1 | [CTF Day(47). picoCTF Web Exploitation](https://medium.com/@ahmednarmer1/ctf-day-47-efe493fc5e12) | Beginner |
| 2 | [Hack The Boo CTF: A Technical Writeup on Web, Pwn, and Forensics](https://medium.com/@purvansh95b/hack-the-boo-ctf-a-technical-writeup-on-web-pwn-and-forensics-bfb9a2aac997) | — |
| 3 | [CTF@CIT Web Challenge Walkthroughs (2025)](https://www.youtube.com/watch?v=ZBdApaw0r0M) | — |
| 4 | [ICMTC CTF 2023 Web Challenges Walkthrough Writeup](https://itsahmedatef.medium.com/icmtc-ctf-2023-web-challenges-walkthrough-writeup-d812346be71d) | — |
| 5 | [HTB: Editorial](https://0xdf.gitlab.io/2024/10/19/htb-editorial.html) | Intermediate |
| 6 | [Writeup - Root-Me CTF 10k - Perfect Notes](https://blog.root-me.org/posts/writeup_ctf10k_perfect_notes) | — |
| 7 | [Writeup - ComCyber Recrutement CTF](https://blog.root-me.org/posts/writeup_comcyber) | — |
| 8 | [NahamCon CTF 2025 Web Challenges Writeups](https://medium.com/@syed_dawood/nahamcon-ctf-2025-web-challenges-writeups-aad86461ca30) | — |
| 9 | [OWASP Top Ten Web Application Security Risks](https://owasp.org/www-project-top-ten) | — |
| 10 | [OWASP Top 10:2025](https://owasp.org/Top10/2025/en) | — |
| 11 | [All Labs | Web Security Academy](https://portswigger.net/web-security/all-labs) | — |
| 12 | [PlaidCTF 2023 Writeups](https://siunam321.github.io/ctf/PlaidCTF-2023) | — |
| 13 | [HTB: OpenSource](https://0xdf.gitlab.io/2022/10/08/htb-opensource.html) | Intermediate |
| 14 | [NahamCon CTF 2023: Web Challenge Walkthroughs](https://www.youtube.com/watch?v=XHg_sBD0-es) | — |
| 15 | [Web Security Research Papers](https://portswigger.net/research) | — |
| 16 | [OWASP Top 10 - Essentials](https://ctf.hackthebox.com/pack/owasp-top-10-essentials) | Intermediate |
| 17 | [CTF Day(26). picoCTF Web Exploitation: Secrets](https://medium.com/@ahmednarmer1/ctf-day-26-4760e9b83079) | Beginner |
| 18 | [Web Security Academy: Free Online Training from PortSwigger](https://portswigger.net/web-security) | — |
| 19 | [Ritsec CTF: WEB Challenges Writeup](https://medium.com/@Asm0d3us/ritsec-ctf-web-challenges-writeup-e46e4965495f) | — |
| 20 | [ICTF 2025 Writeup](https://medium.com/@erichdryn/ictf-2025-writeup-d732dc1393c5) | — |
| 21 | [[Web] Report Google Wargames.my CTF 2023](https://vicevirus.github.io/posts/report-google-wgmy-2023) | — |
| 22 | [LA CTF WriteUp](https://medium.com/@rizkidsaputra9/la-ctf-writeup-d3a5b065d7dd) | — |
| 23 | [HackTheBox - Usage](https://www.youtube.com/watch?v=cx9Da-PoXG4) | Intermediate |
| 24 | [CAT CTF 25 Web Challenges Writeups](https://medium.com/@0xNayelx/cat-ctf-25-web-challenges-writeups-2655e02b6485) | — |
| 25 | [Top 10 Web Hacking Techniques of 2025](https://portswigger.net/research/top-10-web-hacking-techniques-of-2025) | — |
| 26 | [Web Security Blog](https://portswigger.net/blog) | — |
| 27 | [CTF Day(13). picoCTF Web Exploitation: GET aHEAD](https://medium.com/@ahmednarmer1/ctf-day-13-2ad289797f14) | Beginner |
| 28 | [TryHackMe — Capture!](https://medium.com/@vitalysimx/tryhackme-capture-a5ec27a9e94) | Beginner |
| 29 | [RootMe (CTF Walkthrough). A TryHackMe Lab](https://medium.com/@marduk.i.am/rootme-ctf-walkthrough-efe69ef73510) | Beginner |

## 🔬 Sub-Topic Deep Dive

The Web Exploitation category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### SQL Injection

UNION-based, blind, error-based, time-based; sqlmap automation.

*No directly-matching resources in this collection — consult the broader category list above.*

### Cross-Site Scripting (XSS)

reflected, stored, DOM-based; CSP bypass.

*No directly-matching resources in this collection — consult the broader category list above.*

### Server-Side Request Forgery (SSRF)

internal service access, cloud metadata (169.254.169.254).

*No directly-matching resources in this collection — consult the broader category list above.*

### Server-Side Template Injection (SSTI)

Jinja2, Twig, Freemarker, Velocity.

*No directly-matching resources in this collection — consult the broader category list above.*

### Insecure Deserialization

PHP unserialize, Python pickle, Java ObjectInputStream, .NET BinaryFormatter.

*No directly-matching resources in this collection — consult the broader category list above.*

### Prototype Pollution (JS)

client-side and server-side (Node.js) prototype chain poisoning.

*No directly-matching resources in this collection — consult the broader category list above.*

### File Upload / Inclusion

LFI, RFI, ZIP-slip, .htaccess abuse.

Top resources for this sub-topic:

- [r3kapig/writeup: CTF challenges writeup - the collection](../30-archetypes/archives/team-archives/writeup-r3kapig) — 📚 Repository
- [apsdehal/awesome-ctf: A curated list of CTF frameworks  - the collection](../30-archetypes/archives/awesome-lists/awesome-ctf) — 📚 Repository
- [Hack The Box Writeups - The Ultimate HTB Resource - the collection](../20-events/archives/hackthebox/htb-writeups) — 📚 Repository
- [orangetw/My-CTF-Web-Challenges - the collection](../02-web/archives/My-CTF-Web-Challenges) — 📚 Repository
- [Crypto-Cat/CTF: CTF challenge (mostly pwn) files, scripts etc - the collection](../30-archetypes/archives/personal-collections/CTF-CryptoCat) — 📚 Repository

## 🎯 Suggested Learning Order

If you're new to web exploitation, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with [PortSwigger Web Security Academy](https://portswigger.net/web-security) — work through all Apprentice and Practitioner labs. Then read [`orangetw/My-CTF-Web-Challenges`](../02-web/archives/My-CTF-Web-Challenges) to see how top-tier web challenges are designed.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
