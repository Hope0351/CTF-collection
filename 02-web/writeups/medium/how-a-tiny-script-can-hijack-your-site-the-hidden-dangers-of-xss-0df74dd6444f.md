# :globe_with_meridians: How a Tiny Script Can Hijack Your Site: The Hidden Dangers of XSS

> **Original Source:** [How a Tiny Script Can Hijack Your Site: The Hidden Dangers of XSS](https://infosecwriteups.com/how-a-tiny-script-can-hijack-your-site-the-hidden-dangers-of-xss-0df74dd6444f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How a Tiny Script Can Hijack Your Site: The Hidden Dangers of XSS


## A practical and beginner-friendly deep dive into Cross-Site Scripting (XSS) attacks and how to prevent them


Non-Members: [Read Here](https://medium.com/@saikatpaul960/0df74dd6444f?sk=f825a1acc6b2db2dbd6d5239c5a20f55)


Cross-Site Scripting (XSS) is one of the most prevalent and dangerous web application vulnerabilities. It occurs when an attacker can inject malicious scripts into web pages viewed by other users. Understanding XSS is crucial for developers, security professionals, and anyone involved in web development.

## What is Cross-Site Scripting?


XSS attacks exploit the trust that users have in a website. When a web application includes untrusted data in a web page without proper validation or escaping, attackers can execute scripts in the victim’s browser. These scripts can access cookies, session tokens, or other sensitive information retained by the browser.

## Types of XSS Attacks


## 1. Stored XSS (Persistent)


Stored XSS occurs when malicious scripts are permanently stored on the target server, such as in a database, message forum, or comment field. Every time a user visits the affected page, the malicious script executes.

---

*Originally published on [Medium](https://infosecwriteups.com/how-a-tiny-script-can-hijack-your-site-the-hidden-dangers-of-xss-0df74dd6444f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
