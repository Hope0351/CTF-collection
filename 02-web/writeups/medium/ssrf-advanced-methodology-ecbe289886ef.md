# :globe_with_meridians: SSRF Advanced Methodology✨. By Abhijeet Kumawat, Jr. Security…

> **Original Source:** [SSRF Advanced Methodology✨. By Abhijeet Kumawat, Jr. Security…](https://infosecwriteups.com/ssrf-advanced-methodology-ecbe289886ef)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF Advanced Methodology✨


*By Abhijeet Kumawat, Jr. Security Consultant, Bug Bounty Hunter*

## What is SSRF? 🛡️🔥


Server-Side Request Forgery (SSRF) allows attackers to manipulate a server into sending malicious requests, often bypassing firewalls to access sensitive data, cloud metadata, internal APIs, or internal networks. 🛠️💻


## Why is SSRF Critical? ❓💥


- 🧱 Access internal services and hidden endpoints.

- ☁️ Obtain cloud instance metadata (AWS, GCP).

- 🕵️‍♂️ Perform internal network scans.

- 🧨 Exploit further by chaining SSRF with RCE.

## Detailed SSRF Methodology 📚🔍


### 1. Subdomain Enumeration 🔍🗺️


- Tools: 🛠️ Subfinder, Amass, Assetfinder, CRT.sh, Chaos.

- Where to Find Bugs: 🐛 Look for internal subdomains like `dev.target.com`, `staging.target.com`, or `api.target.com`. Test staging environments as they often have misconfigured SSRF protections.

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-advanced-methodology-ecbe289886ef). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
