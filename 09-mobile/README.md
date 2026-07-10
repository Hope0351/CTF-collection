# Mobile Security

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Reverse engineering of Android (APK) and iOS (IPA) applications, Frida-based dynamic instrumentation, and analysis of native libraries via JNI. The least-documented CTF category due to the difficulty of open-sourcing mobile challenge artifacts.

This category contains **18 curated sources** from across the CTF ecosystem: 17 internal archives, 0 Medium articles, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 1 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Difficulty |
|---:|---|---|
| 1 | [corCTF 2025 - corphone](https://u1f383.github.io/android/2025/09/08/corCTF-2025-corphone.html) | Advanced |

## 🔬 Sub-Topic Deep Dive

The Mobile Security category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### APK reverse engineering

apktool, jadx, dex2jar.

Top resources for this sub-topic:

- [1GN1tE/CTF_Writeups](../30-archetypes/archives/personal-collections/CTF_Writeups-1GN1tE) - Writeups including mobile RE - 📚 Repository

### IPA reverse engineering

class-dump, Hopper, Ghidra.

Top resources for this sub-topic:

- [1GN1tE/CTF_Writeups](../30-archetypes/archives/personal-collections/CTF_Writeups-1GN1tE) - Writeups including mobile RE - 📚 Repository

### Frida dynamic instrumentation

hooking Java methods, native function hooking.

*No directly-matching resources in this collection — consult the broader category list above.*

### Native library analysis

JNI, ARM reverse engineering.

*No directly-matching resources in this collection — consult the broader category list above.*

### Certificate pinning bypass

Frida scripts, objection.

*No directly-matching resources in this collection — consult the broader category list above.*

## 🎯 Suggested Learning Order

If you're new to mobile security, work through the resources in this order:

1. **Start with a structured learning platform.** Begin with the OWASP MSTG (Mobile Security Testing Guide), then work through the DIVA (Damn Insecure and Vulnerable App) and OWASP MASTG test apps.

2. **Build a personal writeup habit.** Every time you solve a challenge, write a 2-paragraph summary. Commit these to a personal archive — over time, this becomes your portfolio.
3. **Study elite writeups.** After each major CTF, read the top-placing teams' writeups within 1 week. The team archives at `p4-team/ctf`, `r3kapig/writeup`, and `theori-io/ctf` are the strongest references.
4. **Play live.** Join [CTFtime](https://ctftime.org/) and play at least one CTF per month. There is no substitute for live competition.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
