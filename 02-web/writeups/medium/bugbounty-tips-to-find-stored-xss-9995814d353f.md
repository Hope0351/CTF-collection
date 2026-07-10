# :globe_with_meridians: [BugBounty] Tips to Find Stored XSS

> **Original Source:** [[BugBounty] Tips to Find Stored XSS](https://infosecwriteups.com/bugbounty-tips-to-find-stored-xss-9995814d353f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# [BugBounty] Tips to Find Stored XSS


## Intro


Today, I would like to share some simple and quick ways to find stored XSS (Cross-site Scripting) vulnerabilities as well as 2 stored XSS vulnerabilities that I reported in [HackerOne](https://hackerone.com/) private programs.


For anyone who is new to AppSec or Bug Bounty, the stored XSS (aka persistent XSS) occurs when an application receives user-input data and save that data within the application’s later HTTP response and renders it in an unsafe way. For example, if a user is allowed to enter any data into a comment section of a web application, she can insert an XSS payload such as `<script>alert('XSS')</script>` into the vulnerable comment section. If the web application saves that untrusted user-supplied XSS payload as-is and also renders it without any sanitization, the payload will be executed on any other user’s browser that is visiting the affected page.

## 1. Finding Different Rendering Areas


Many times I attempt to find a XSS or HTML Injection vulnerability using manual approach. For example, if there is a user input field such as user name field of the profile page, I inject a simple payload like `<h1>test</h1>` and check different rending pages within the application. If you get lucky, you can find a stored XSS this way. This is because for a complex application, it will be difficult for…

---

*Originally published on [Medium](https://infosecwriteups.com/bugbounty-tips-to-find-stored-xss-9995814d353f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
