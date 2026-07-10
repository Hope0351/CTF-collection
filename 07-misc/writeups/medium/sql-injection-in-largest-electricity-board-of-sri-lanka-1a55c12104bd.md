# :game_die: SQL injection in largest Electricity Board of Sri Lanka

> **Original Source:** [SQL injection in largest Electricity Board of Sri Lanka](https://infosecwriteups.com/sql-injection-in-largest-electricity-board-of-sri-lanka-1a55c12104bd)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SQL injection in largest Electricity Board of Sri Lanka


## In this article I’ll describe how I found SQL injection vulnerabilities by bypassing WAF with origin IP, IDOR and information disclosure bugs.


## Introduction


SQL Injection is a technique used by attackers to take advantage of vulnerabilities in a websites database. By inserting harmful SQL code into inputs such as forms or search fields they can reach, modify or even erase sensitive information. This vulnerability may result in unauthorized entry, data compromise, or complete server control categorizing SQLi as one of the most significant and prevalent cybersecurity threats.

### Story


One day a subscriber reached out and asked if I could test for SQL injection vulnerabilities on their national Electricity Board website which was protected by Cloudflare WAF. As many of you know I often share techniques and methods for identifying SQL injection vulnerabilities so I decided to take on the challenge. So let’s begin with how I discovered this!

## How i find this vulnerability


I visited the website and used the Wappalyzer extension to check the site technology stack. The extension revealed that the site was built…

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-in-largest-electricity-board-of-sri-lanka-1a55c12104bd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
