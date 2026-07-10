# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/learning-sql-injection-using-sqlmap-and-dvwa-97d72a2e5cf6)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Learning SQL Injection Using Sqlmap and DVWA


## Getting Started with Sqlmap — Learning SQL Injection the Easy Way


*Photo by [Samuel Quek](https://unsplash.com/@samuelqyx?utm_content=creditCopyText&utm_medium=referral&utm_source=unsplash) on [Unsplash](https://unsplash.com/photos/a-plane-that-is-sitting-in-the-dirt-j2MGpXCAM6o?utm_content=creditCopyText&utm_medium=referral&utm_source=unsplash)*


It’s been a while since I last wrote about DVWA — two years, to be exact! This time, I want to go a little deeper into SQL Injection. Nothing too heavy, just a hands-on walkthrough with sqlmap.

## Why DVWA


If you are just starting with hacking, Damn Vulnerable Web Application (DVWA) is the best playground for learning ethical hacking. It’s a purposely insecure web app designed to help you practice common web security vulnerabilities.


In this tutorial, I already set up the app on VirtualBox (IP: `192.168.1.105`) and will walk you through performing SQL Injection on the login page using `sqlmap`. This guide is for educational purposes only — never try this on real websites without permission.


⚠️ **Disclaimer:** This guide is for educational purposes only. Never attempt these techniques on real websites without legal consent.

>

You could read this article for free — [Click Here](https://medium.com/bugbountywriteup/learning-sql-injection-using-sqlmap-and-dvwa-97d72a2e5cf6?sk=6b4489e15b3e2fc4d25bb0e8fa95dbaa) 💖


## Powering Up


Since I already installed DVWA, I can easily access it by opening the IP address.

---

*Originally published on [Medium](https://infosecwriteups.com/learning-sql-injection-using-sqlmap-and-dvwa-97d72a2e5cf6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
