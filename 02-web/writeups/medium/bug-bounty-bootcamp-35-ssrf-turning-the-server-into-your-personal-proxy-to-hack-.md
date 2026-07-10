# :globe_with_meridians: “Bug Bounty Bootcamp #35: SSRF — Turning the Server Into Your Personal Proxy to Hack Internal Networks”

---

# “Bug Bounty Bootcamp #35: SSRF — Turning the Server Into Your Personal Proxy to Hack Internal Networks”

## Imagine if you could trick a web server into visiting internal websites, reading local files, and even scanning private IP ranges on your behalf. That’s SSRF. And when it works, the entire internal infrastructure becomes your playground.

Free Link

Welcome back to the Bug Bounty Bootcamp. You’ve mastered attacking the frontend, the backend, the database, and even the authorization logic. Now, we go where few vulnerabilities dare: the server’s own network. Server-Side Request Forgery (SSRF) occurs when a web application fetches a remote resource based on user input — like an image proxy or a URL preview feature — without properly validating the destination. An attacker can make the server send requests to internal IP addresses, localhost, cloud metadata endpoints, or even other internal services. The impact? Port scanning, data theft, internal API abuse, and sometimes full cloud compromise.

## The Core Concept: The Server as Your Web Browser

---
