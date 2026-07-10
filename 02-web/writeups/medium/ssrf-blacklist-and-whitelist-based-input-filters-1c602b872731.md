# :globe_with_meridians: SSRF: Blacklist and Whitelist-Based Input Filters

> **Original Source:** [SSRF: Blacklist and Whitelist-Based Input Filters](https://infosecwriteups.com/ssrf-blacklist-and-whitelist-based-input-filters-1c602b872731)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF: Blacklist and Whitelist-Based Input Filters


## Explain and Try To Bypass Blacklist and Whitelist Input Filters


Server-Side Request Forgery (SSRF) is a web security vulnerability that enables an attacker to manipulate a server-side application into making HTTP requests to arbitrary destinations. This can lead to unauthorized interactions with internal systems, potentially exposing sensitive information or allowing further exploitation.

### Types of SSRF:*SSRF Targeting the Server:* Attackers manipulate the application to send HTTP requests to the server’s loopback adapter. For instance, by modifying a request in an eCommerce app, they can access admin pages and bypass access controls.


*SSRF Targeting the Back End:* Attackers interact with backend systems, typically with private IP addresses and weaker security, to access protected functionalities like administrative interfaces.


*Blind SSRF:* These attacks focus on performing malicious actions without visible data return. For example, repeatedly requesting a large file can crash the server, causing a denial of service (DoS).

### Risks of SSRF:


A successful Server-Side Request Forgery (SSRF) attack can manipulate a web server to perform malicious actions or…

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-blacklist-and-whitelist-based-input-filters-1c602b872731). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
