# :globe_with_meridians: “Bug Bounty Bootcamp #38: SSRF Chaining - Bypassing Domain Whitelists with Open Redirects and PDF Injections”

> **Original Source:** [“Bug Bounty Bootcamp #38: SSRF Chaining - Bypassing Domain Whitelists with Open Redirects and PDF Injections”](https://amannsharmaa.medium.com/bug-bounty-bootcamp-38-ssrf-chaining-bypassing-domain-whitelists-with-open-redirects-and-pdf-8c344246a1c7)
> **Platform:** amannsharmaa.medium.com | **Category:** `WEB`

---

# “Bug Bounty Bootcamp #38: SSRF Chaining — Bypassing Domain Whitelists with Open Redirects and PDF Injections”


## You found an SSRF, but the server only allows URLs from `trusted.com`. Game over? Not if `trusted.com` has an open redirect. Learn to chain a lowly redirect with SSRF to reach internal networks – and how PDF invoices can become your stealthy exfiltration channel.


[Free Link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-38-ssrf-chaining-bypassing-domain-whitelists-with-open-redirects-and-pdf-8c344246a1c7?sk=6d1e886b09da560b9e3c123423cb3953)


Welcome back. You’ve learned to confirm SSRF and bypass naive localhost blocks. Now we enter the big leagues: domain whitelists. The developer got smart — only URLs from `*.target.com` are allowed. Your external IPs and `nip.io` tricks are blocked. But every castle has a weak gate. If `target.com` itself has an open redirect vulnerability, that gate is wide open. This lesson will show you exactly how to chain an open redirect with SSRF, plus a bonus scenario: exploiting SSRF through a PDF invoice generator where your profile HTML becomes the attack vector.

## The Whitelist Wall: When Only One Domain Is Allowed


Imagine an SSRF endpoint with a strict whitelist:
`https://target.com/proxy?url=https://api.target.com/fetch`

---

*Originally published on [Medium](https://amannsharmaa.medium.com/bug-bounty-bootcamp-38-ssrf-chaining-bypassing-domain-whitelists-with-open-redirects-and-pdf-8c344246a1c7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
