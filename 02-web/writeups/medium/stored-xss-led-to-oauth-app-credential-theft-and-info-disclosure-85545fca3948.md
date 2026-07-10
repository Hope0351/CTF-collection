# :globe_with_meridians: Stored XSS Led to OAuth App Credential Theft and Info Disclosure

> **Original Source:** [Stored XSS Led to OAuth App Credential Theft and Info Disclosure](https://infosecwriteups.com/stored-xss-led-to-oauth-app-credential-theft-and-info-disclosure-85545fca3948)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Stored XSS Led to OAuth App Credential Theft and Info Disclosure


Free Article Link: Click for free!


Hello folks,


I hope you’re doing great! I’m Ehtesham, and today I’m sharing an exciting bug bounty case where I discovered a Stored Cross-Site Scripting (XSS) vulnerability that led to the theft of OAuth credentials and sensitive organizational details.


Let’s walk through how this bug was found, exploited, and responsibly disclosed.

## Introduction


During one of my bug bounty hunts on target.com (domain anonymized for confidentiality), I found a critical stored XSS vulnerability that allowed me to:


- Steal organization details of any user.

- Extract OAuth application credentials (Client ID and Secret).

- Execute JavaScript in the context of other users visiting the malicious page.


What started as a basic payload test quickly escalated into a serious vulnerability with real-world impact.

## Understanding the Vulnerability


The vulnerability existed in the organization name field. This field accepted and stored unsanitized user input, which was later rendered on a public-facing storefront page. This made it possible for malicious…

---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-led-to-oauth-app-credential-theft-and-info-disclosure-85545fca3948). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
