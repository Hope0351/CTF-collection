# :globe_with_meridians: Getting started with XSS: Cross-Site Scripting Attacks

> **Original Source:** [Getting started with XSS: Cross-Site Scripting Attacks](https://infosecwriteups.com/getting-started-with-xss-cross-site-scripting-attacks-822c82b7cd82)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Getting started with XSS: Cross-Site Scripting Attacks


Let’s get started with XSS, in order to get those critical bugs- CSRF, SSRF, RCE. Most of the time, an XSS flaw is the cause of a vulnerability that is exploited and escalated to a critical find.


First and foremost, the structure: we will start by learning about the basics of XSS, then: the thing you should know- How a browser & website function, later: types of XSS- understanding the impactful XSSs’, and lastly: XSS in Bug Hunting.


## What is XSS?


I know you know. But do you know, what you don’t know? XSS is a Cross-Site Scripting attack, a very basic one for a Security Tester. But still, no harm in re-reading(or skipping). Remember that- Learn, Unlearn & Re-learn. So, here it is.


Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end-user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it — OWASP.

---

*Originally published on [Medium](https://infosecwriteups.com/getting-started-with-xss-cross-site-scripting-attacks-822c82b7cd82). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
