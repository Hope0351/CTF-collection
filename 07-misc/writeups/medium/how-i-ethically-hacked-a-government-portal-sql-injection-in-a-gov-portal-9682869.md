# :game_die: How I Hacked a Government Portal: SQL Injection in a Gov. Portal

> **Original Source:** [How I Hacked a Government Portal: SQL Injection in a Gov. Portal](https://infosecwriteups.com/how-i-ethically-hacked-a-government-portal-sql-injection-in-a-gov-portal-9682869e5999)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How I Hacked a Government Portal: SQL Injection in a Gov. Portal


[Free Link](https://myselfakash20.medium.com/how-i-ethically-hacked-a-government-portal-sql-injection-in-a-gov-portal-9682869e5999?sk=a8572f3378c9bf783c962851e9a7a1f5)


As a security researcher, I constantly test public-facing applications for vulnerabilities to help strengthen cybersecurity. During one such assessment, I identified a SQL Injection vulnerability in the search functionality of Government Portal, It’s a government website. If left unpatched, this could have been exploited to access sensitive government records, extract user credentials, or even manipulate database entries. 😱


This write-up will walk you through how I discovered, confirmed, and responsibly reported this vulnerability. If you’re a bug bounty hunter, penetration tester, or security enthusiast, this is for you! 💻🔥

## 1️⃣ Finding the Vulnerability


## 🔍 Observing Suspicious Behavior


While casually testing the search function on XYZGov Portal, I entered a random string (`myselfakash20`), expecting a normal "No results found" response. Instead, I was greeted with a database error message:


```
A Database Error Occurred
Error Number: 1064
You have an error in your SQL syntax...
```

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-ethically-hacked-a-government-portal-sql-injection-in-a-gov-portal-9682869e5999). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
