# :globe_with_meridians: Stored XSS Filter Bypass in the Skills section

> **Original Source:** [Stored XSS Filter Bypass in the Skills section](https://infosecwriteups.com/stored-xss-filter-bypass-in-the-skills-section-7bf5e33c8ace)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Stored XSS Filter Bypass in the Skills section


Inspired by my recent post on LinkedIn, I’m excited to share my first-ever write-up on Medium. In this article, I’ll take you through my experience of finding a stored Cross-Site Scripting (XSS) vulnerability by getting around filters. Let’s dive into the details of my journey. For non-premium medium members, here you can read it for free: https://infosecwriteups.com/stored-xss-filter-bypass-in-the-skills-section-7bf5e33c8ace?source=friends_link&sk=2ce56c0e6ed7356d0365210c756f16b1


So let’s get started.


- Finding the Target:


I chose a target website and explored it as a regular user. After signing up and logging in, I checked out the different sections available to users with accounts.


2. Exploring the Vulnerable Section:


Among the options, I clicked on “Settings” and then “Profile Summary.” Here, I found a place where users could list their skills, which seemed like a good spot to test for an XSS exploit.

---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-filter-bypass-in-the-skills-section-7bf5e33c8ace). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
