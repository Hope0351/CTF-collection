# :globe_with_meridians: $500 Bounty: XSS via JavaScript: URLs

> **Original Source:** [$500 Bounty: XSS via JavaScript: URLs](https://infosecwriteups.com/500-bounty-xss-via-javascript-urls-a04900631701)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $500 Bounty: XSS via JavaScript: URLs


## A simple login redirect turned into a dangerous XSS vector — complete with video PoC and attack chain potential.


### Introduction


Open redirect vulnerabilities are often overlooked as “low severity,” but what happens when they become the first domino in an XSS chain? This is exactly what happened on Reddit’s login page, where a regression in the sanitization of the dest parameter allowed attackers to inject javascript: URLs and trigger XSS.

>

The Vulnerability


Reddit’s login page has a dest parameter designed to redirect users after authentication. While it previously sanitized inputs to block dangerous schemes, a regression allowed javascript: schemes to slip through.


Example Payload


```
https://www.reddit.com/login/?dest=javascript:alert(document.domain);
```


This payload would execute alert(document.domain) after a user logs in.

>

Proof of Concept


Video PoC: [https://hackerone.com/reports/1962951](https://hackerone.com/reports/1962951)


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The video demonstrates how, after modifying the dest parameter to a javascript: URL and successfully logging in, the browser triggers an alert pop-up — clear evidence of XSS.

### Steps to Reproduce


- Visit the Reddit login page: [https://www.reddit.com/login/?dest=https%3A%2F%2Fwww.reddit.com%2F](https://www.reddit.com/login/?dest=https%3A%2F%2Fwww.reddit.com%2F)

- Change the dest parameter to: javascript:alert(document.domain);

- Login with valid credentials.

- Upon successful login, the browser attempts to redirect to the javascript: URL, triggering XSS.

>

Impact


- XSS via Open Redirect: This shows how open redirects aren’t just phishing vectors — they can lead directly to script injection.

- Potential cookie theft: The attacker could steal session cookies or tokens by replacing the payload with a malicious script.

- Phishing attack chains: This vulnerability could be part of a larger multi-step attack combining XSS, CSRF, and phishing.

### References


- HackerOne Report #1962951

- BrightSec: Open Redirect Vulnerabilities

### Final Thoughts


This bug is a classic reminder: open redirects are not just harmless quirks. When they allow javascript: schemes, they become XSS in disguise. Always sanitize and validate redirect parameters — your users’ safety depends on it.


If you want, I can help generate a thumbnail image idea, create tags/

>

THANK YOU ✨

---

*Originally published on [Medium](https://infosecwriteups.com/500-bounty-xss-via-javascript-urls-a04900631701). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
