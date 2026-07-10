# :game_die: Mastering SQL Injection Recon: Step-by-Step Guide for Bug Bounty Hunters

> **Original Source:** [Mastering SQL Injection Recon: Step-by-Step Guide for Bug Bounty Hunters](https://infosecwriteups.com/mastering-sql-injection-recon-step-by-step-guide-for-bug-bounty-hunters-9f493fb058dd)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Mastering SQL Injection Recon: Step-by-Step Guide for Bug Bounty Hunters


## A practical guide to uncovering SQL injection flaws using automation, payloads and deep reconnaissance techniques.


## Introduction


SQL Injection remains one of the most critical web vulnerabilities, allowing attackers to manipulate backend databases through unsanitized inputs. Effective reconnaissance is key to identifying potential SQLi points before exploitation. This article walks you through a practical, step-by-step SQLi reconnaissance methodology using popular tools and payloads.

## Step 1: Recon the Target Subdomains


Before testing for SQLi you need to discover the attack surface the subdomains and URLs that might be vulnerable.


For a single domain use:


```
subfinder -d example.com -all -silent | httpx-toolkit -td -sc -silent | grep -Ei 'asp|php|jsp|jspx|aspx'
```


For multiple subdomains listed in a file (subdomains.txt):


```
subfinder -dL subdomains.txt -all -silent | httpx-toolkit -td -sc -silent | grep -Ei 'asp|php|jsp|jspx|aspx'
```

---

*Originally published on [Medium](https://infosecwriteups.com/mastering-sql-injection-recon-step-by-step-guide-for-bug-bounty-hunters-9f493fb058dd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
