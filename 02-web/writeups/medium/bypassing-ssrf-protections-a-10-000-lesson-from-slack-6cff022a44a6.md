# :globe_with_meridians: Bypassing SSRF Protections: A $10,000 Lesson from Slack

> **Original Source:** [Bypassing SSRF Protections: A $10,000 Lesson from Slack](https://infosecwriteups.com/bypassing-ssrf-protections-a-10-000-lesson-from-slack-6cff022a44a6)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bypassing SSRF Protections: A $10,000 Lesson from Slack


## How a Simple DNS Rebinding Attack Led to Internal Network Access


Server-Side Request Forgery (SSRF) vulnerabilities remain one of the most critical security issues in modern web applications. Today, I’m breaking down a fascinating SSRF report that earned a researcher $10,000 from Slack’s bug bounty program, and the valuable lessons we can all learn from it.

## The Vulnerability Overview


Severity: High
Free Read: [Click](https://medium.com/@Aacle/bypassing-ssrf-protections-a-10-000-lesson-from-slack-6cff022a44a6?sk=11db7e23b85c1147e030b74a5a36d383)


This report demonstrates how an attacker could bypass Slack’s SSRF protections using DNS rebinding techniques to access internal network resources that should have been completely isolated from external access.

## Understanding the Attack Surface


Slack, like many modern applications, needs to fetch external resources — think profile images, link previews, or webhook callbacks. However, allowing a server to make arbitrary HTTP requests opens the door to SSRF attacks, where an attacker tricks the server into making requests to internal resources.

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-ssrf-protections-a-10-000-lesson-from-slack-6cff022a44a6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
