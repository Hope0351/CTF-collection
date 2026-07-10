# :game_die: How To Hack With SQL Injection Attacks! DVWA low security — StackZero

> **Original Source:** [How To Hack With SQL Injection Attacks! DVWA low security — StackZero](https://infosecwriteups.com/how-to-hack-with-sql-injection-attacks-dvwa-low-security-stackzero-9286d7d0dfd1)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How To Hack With SQL Injection Attacks! DVWA low security — StackZero


## Introduction


SQL injection is a code injection technique that exploits a security vulnerability occurring in the database layer of an application. The vulnerability is present when user input is either incorrectly filtered for string literal escape characters embedded in SQL statements or user input is not strongly typed and unexpectedly executed.
This could allow an attacker to execute unintended SQL commands that can compromise the security of the database.
You can find a detailed description of the vulnerability in this article: [SQL Injection: What You Need to Know](https://medium.com/codex/sql-injection-what-you-need-to-know-stackzero-abc80bc1ea5e).
In this tutorial we are going to exploit a SQL injection vulnerability on the Damn Vulnerable Web Application (DVWA).


Usually, the attacker has different tools to accomplish his task like:


Those two are the best known, by the way, in this tutorial we don’t need them.


Here is the list of all the articles about SQL injection for quick navigation:

## In-Band SQL injection

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-hack-with-sql-injection-attacks-dvwa-low-security-stackzero-9286d7d0dfd1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
