# :game_die: SQL Injection Tactics: Achieving Code Execution for your OSCP Skillset

> **Original Source:** [SQL Injection Tactics: Achieving Code Execution for your OSCP Skillset](https://infosecwriteups.com/sql-injection-tactics-achieving-code-execution-for-your-oscp-skillset-ef3d7667c1b0)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SQL Injection Tactics: Achieving Code Execution for your OSCP Skillset


Leveraging SQL Injection for OSCP skillset


*MSSQL*


OSCP is all about pushing boundaries to gain remote code execution. When facing web vulnerabilities like SQL injection, the endgame isn’t just extracting data — it’s about *executing commands on the target system.* Or better yet, *getting that sweet reverse shell* so we can move laterally, escalate privileges, and own our objectives. Today, I’ll take you through a targeted operation using MSSQL.

## Step 1: Locate the Injection Point


The first step in any SQL injection attack is finding a parameter you can control. Typically, this happens where user input is processed, such as login forms, comment boxes, or any web form. Let’s illustrate.

## Example: Login Portal


When you see a login page that requests a username and password, try throwing in an apostrophe (`'`) as your username or password to see if the server responds with an error. Intercepting with a proxy tool like Burp Suite or OWASP ZAP can expose helpful clues directly in the response or source code.

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-tactics-achieving-code-execution-for-your-oscp-skillset-ef3d7667c1b0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
