# :globe_with_meridians: Routing-Based SSRF - Host Header Injection Leads to Internal Access

> **Original Source:** [Routing-Based SSRF - Host Header Injection Leads to Internal Access](https://infosecwriteups.com/routing-based-ssrf-host-header-injection-leads-to-internal-access-b65a1c8b1b42)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Routing-Based SSRF — Host Header Injection Leads to Internal Access


Discover how a simple Host header tampering can expose private admin panels and critical internal services.


🔓 [Free Link](https://bashoverflow.com/b65a1c8b1b42?sk=864ad392ab2acc2d818228559ff4b691)


*Routing-Based SSRF — Host Header Injection Leads to Internal Access*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.


It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.


## Table of Contents


- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability


This vulnerability demonstrates a Server-Side Request Forgery (SSRF) attack vector, where Host header manipulation is exploited to bypass internal routing controls.


In this lab from PortSwigger, the backend uses the `Host`header to determine how to route requests. By modifying the `Host`value to mimic an internal IP (such as…

---

*Originally published on [Medium](https://infosecwriteups.com/routing-based-ssrf-host-header-injection-leads-to-internal-access-b65a1c8b1b42). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
