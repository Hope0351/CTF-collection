# :globe_with_meridians: URL Normalization Turns a Harmless Request into a Cache-Poisoned XSS Attack

> **Original Source:** [URL Normalization Turns a Harmless Request into a Cache-Poisoned XSS Attack](https://infosecwriteups.com/url-normalization-turns-a-harmless-request-into-a-cache-poisoned-xss-attack-57d1a68f08d2)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# URL Normalization Turns a Harmless Request into a Cache-Poisoned XSS Attack


Learn how URL normalization flaws can lead to cache poisoning and cross-site scripting (XSS).


🔓 [Free Link](https://bashoverflow.com/57d1a68f08d2?sk=055aedaf71cc12ab530d5258081fd99d)


*URL Normalization Turns a Harmless Request into a Cache-Poisoned XSS Attack*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.


It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.


## Table of Contents


- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability


In this lab, the core weakness lies in how the web cache and browser handle URLs differently. The application contains an XSS vulnerability, but browsers automatically apply URL-encoding, which prevents the payload from executing directly. However, the cache performs *normalization* of the URL before storing and serving it.

---

*Originally published on [Medium](https://infosecwriteups.com/url-normalization-turns-a-harmless-request-into-a-cache-poisoned-xss-attack-57d1a68f08d2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
