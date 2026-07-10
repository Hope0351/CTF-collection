# :globe_with_meridians: SSRF via Flawed Request Parsing Leads to Internal Admin Access

> **Original Source:** [SSRF via Flawed Request Parsing Leads to Internal Admin Access](https://infosecwriteups.com/ssrf-via-flawed-request-parsing-leads-to-ssrf-and-internal-admin-access-ffac4b3103db)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF via Flawed Request Parsing Leads to Internal Admin Access


Exploiting Misconfigured Routing to Breach Internal Networks through SSRF.


🔓 [Free Link](https://bashoverflow.com/ffac4b3103db?sk=89fe34340f4325ccbd31d0e174ad4d67)


*SSRF via Flawed Request Parsing Leads to SSRF and Internal Admin Access*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.


It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.


## Table of Contents


- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability


The vulnerability arises from inconsistent parsing of the request host, particularly in how different components of a web application (like front-end reverse proxies, load balancers, or the backend logic) interpret the Host header and other URL parts.


In this specific lab environment from [PortSwigger’s Web Security Academy](https://portswigger.net/web-security/host-header/exploiting/lab-host-header-ssrf-via-flawed-request-parsing), the application suffers from…

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-via-flawed-request-parsing-leads-to-ssrf-and-internal-admin-access-ffac4b3103db). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
