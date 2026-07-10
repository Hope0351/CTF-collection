# :sleuth_or_spy: Full GitHub Dorking guide: for OSINT and BugBounty (Reconnaissance)

> **Original Source:** [Full GitHub Dorking guide: for OSINT and BugBounty (Reconnaissance)](https://infosecwriteups.com/full-github-dorking-guide-for-osint-and-bugbounty-reconnaissance-27557fb67ee0)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

# Full GitHub Dorking guide: for OSINT and BugBounty (Reconnaissance)


Here you will learn how to improve your level in OSINT , examples and ready search queries will be given .
(You can complete me if I forgot something in the comments).

## What is it and what does it serve?


GithubDorking is an extremely important part of a site reconnaissance or bugbounty program .
If you are familiar with GoogleDorking, they are very similar and serve the same purpose — keyword search in the system .

## What can be found through GithubDorking ?


## 1. Sensitive authorization data:


API keys (Google, AWS, Azure, Twitter, Stripe, etc.).
Access tokens (OAuth, JWT, etc.).
Logins and passwords in code or configuration files.
SSH keys (especially private keys).
.env files containing secrets.

## 2. Confidential Files:


Application configuration files (config.php, .env, web.config).
Error or deploy logs (error.log, debug.log).
Database files (database.sql, .sqlite).

## 3. server information:


IP addresses of servers or internal hosts.
Deployment secrets (such as Ansible Vault or Kubernetes Secrets)…

---

*Originally published on [Medium](https://infosecwriteups.com/full-github-dorking-guide-for-osint-and-bugbounty-reconnaissance-27557fb67ee0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
