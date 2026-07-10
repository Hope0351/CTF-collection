# :globe_with_meridians: The terrifying world of Cross-Site Scripting (XSS) (Part 2) — StackZero

> **Original Source:** [The terrifying world of Cross-Site Scripting (XSS) (Part 2) — StackZero](https://infosecwriteups.com/the-terrifying-world-of-cross-site-scripting-xss-part-2-stackzero-cc7fa7e8dcbb)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The terrifying world of Cross-Site Scripting (XSS) (Part 2) — StackZero


## Introduction


I already discussed the vulnerability in the [XSS Intro](https://www.stackzero.net/xss/) in Part 1 of the article. Anyway, just for a quick refresh, XSS is a vulnerability that enables attackers to inject malicious code into webpages viewed by other users.
There are 3 types of XSS:


What I’m going to do in the 2nd part of the article is just build a simple vulnerable application and then try to exploit them. Even if it will contain just what is necessary to understand, I’ll try to implement all types of vulnerabilities.


Let’s try together to reach the goal and better understand XSS.


Before starting here a list of related articles for a quick navigation:

## Requirements

---

*Originally published on [Medium](https://infosecwriteups.com/the-terrifying-world-of-cross-site-scripting-xss-part-2-stackzero-cc7fa7e8dcbb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
