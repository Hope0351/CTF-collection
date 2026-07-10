# :globe_with_meridians: DOM XSS in `document.write` Sink Using Source `location.search` Inside a `<select>` Element

> **Original Source:** [DOM XSS in `document.write` Sink Using Source `location.search` Inside a `<select>` Element](https://infosecwriteups.com/dom-xss-in-document-write-sink-using-source-location-search-inside-a-select-element-6df5304d9b11)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# DOM XSS in `document.write` Sink Using Source `location.search` Inside a `<select>` Element


Learn how `document.write()` combined with `location.search` leads to a DOM-based XSS vulnerability inside a `<select>` element.


🔓 [Free Link](https://bashoverflow.com/6df5304d9b11?sk=ec05561a6cab03de011fa1227013116e)


*DOM XSS in (`document.write)` Sink Using Source (`location.search)` Inside a `<select>` Element*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.


It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.


## Table of Contents


- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability


In this scenario, the vulnerable application uses JavaScript’s `document.write` to dynamically generate part of a page, including a `<select>` dropdown. The values injected into this `select` element are not properly sanitized and originate from `location.search`, which reflects any query string passed via the…

---

*Originally published on [Medium](https://infosecwriteups.com/dom-xss-in-document-write-sink-using-source-location-search-inside-a-select-element-6df5304d9b11). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
