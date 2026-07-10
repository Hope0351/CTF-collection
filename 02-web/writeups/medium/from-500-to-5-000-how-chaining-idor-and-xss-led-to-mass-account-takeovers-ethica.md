# :globe_with_meridians: “From $500 to $5,000: How Chaining IDOR and XSS Led to Mass Account Takeovers (Ethical Hacking Case Study)”

> **Original Source:** [“From $500 to $5,000: How Chaining IDOR and XSS Led to Mass Account Takeovers (Ethical Hacking Case Study)”](https://infosecwriteups.com/from-500-to-5-000-how-chaining-idor-and-xss-led-to-mass-account-takeovers-ethical-hacking-a55de6e59a71)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# “From $500 to $5,000: How Chaining IDOR and XSS Led to Mass Account Takeovers (Ethical Hacking Case Study)”


As a security researcher, I’ve uncovered dozens of vulnerabilities, but one particular finding stands out — where a simple IDOR flaw snowballed into a critical account takeover chain. This case study reveals how modern web defenses can fail and why proper security layers matter.


[friend link | free link](https://amannsharmaa.medium.com/from-500-to-5-000-how-chaining-idor-and-xss-led-to-mass-account-takeovers-ethical-hacking-a55de6e59a71?sk=90c226902d080fa5e222716ccb930f7e)


## The Discovery: A Seemingly Harmless IDOR


While testing a popular SaaS platform’s widget feature, I noticed each widget was accessed via:


```
https://app.target.com/widgets/edit?uuid=123e4567-e89b-12d3-a456-426614174000
```


Changing the UUID granted me full editing rights to any user’s widget. No permission checks. No warnings. Just unfettered access — a textbook Insecure Direct Object Reference (IDOR) vulnerability.


Why This Was Dangerous:


- Widgets could be embedded on public websites

- The platform served over 100,000 businesses

- No secondary authentication for sensitive operations

## From IDOR to Stored XSS: The JavaScript Pseudo-Protocol Trick

---

*Originally published on [Medium](https://infosecwriteups.com/from-500-to-5-000-how-chaining-idor-and-xss-led-to-mass-account-takeovers-ethical-hacking-a55de6e59a71). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
