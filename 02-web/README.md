# Web Exploitation

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Server-side (SQLi, SSRF, SSTI, RCE, deserialization, file inclusion) and client-side (XSS, CSRF, prototype pollution) vulnerabilities, plus modern web3 integrations and bespoke web app exploitation. The broadest category, requiring fluency in HTTP, web frameworks, browser security model, and modern web tooling (Burp, semgrep, ffuf).

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
