# :globe_with_meridians: Web Cache Poisoning via Ambiguous Requests Lead to XSS

> **Original Source:** [Web Cache Poisoning via Ambiguous Requests Lead to XSS](https://infosecwriteups.com/web-cache-poisoning-via-ambiguous-requests-lead-to-xss-aa9f9f59c079)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Web Cache Poisoning via Ambiguous Requests Lead to XSS


Discover how subtle inconsistencies in Host header processing can poison caches and compromise users.


🔓 [Free Link](https://bashoverflow.com/aa9f9f59c079?sk=94613e02afae24503cff6d747e92dc59)


*Web Cache Poisoning via Ambiguous Requests Lead to XSS*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.


It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.


## Table of Contents


- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability


This lab, as referenced from PortSwigger’s resource, highlights a web cache poisoning vulnerability that stems from inconsistent handling of ambiguous HTTP requests between the cache layer (e.g., CDN or reverse proxy) and the back-end server.


The key discrepancy lies in how the Host headers are interpreted. Specifically, when a request includes two…

---

*Originally published on [Medium](https://infosecwriteups.com/web-cache-poisoning-via-ambiguous-requests-lead-to-xss-aa9f9f59c079). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
