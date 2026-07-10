# :game_die: “Bug Bounty Bootcamp #28: Boolean-Based Blind SQL Injection - Extracting Data One True/False at a Time”

> **Original Source:** [“Bug Bounty Bootcamp #28: Boolean-Based Blind SQL Injection - Extracting Data One True/False at a Time”](https://infosecwriteups.com/bug-bounty-bootcamp-28-boolean-based-blind-sql-injection-extracting-data-one-true-false-at-a-abe69e3de702)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# “Bug Bounty Bootcamp #28: Boolean-Based Blind SQL Injection — Extracting Data One True/False at a Time”


## When the application only answers “yes” or “no,” you’d think data extraction is impossible. Think again. Learn to play 20 Questions with the database and walk away with all its secrets.


[Free Link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-28-boolean-based-blind-sql-injection-extracting-data-one-true-false-at-a-abe69e3de702?sk=22687a37457830bd2cbdb980ce1f3dc3)


Welcome back to the Bug Bounty Bootcamp. You’ve conquered error-based and UNION-based SQL injection, where data flows back to you directly. But what happens when the application is blind — when it only returns a simple `true` or `false`, with no error messages, no data dumps, just a binary signal? This is the realm of Boolean-Based Blind SQL Injection, one of the most elegant and methodical attacks in a hacker's arsenal. By asking the database a series of true/false questions, you can reconstruct entire databases, tables, and records, one painstaking character at a time.

## The Scenario: An API That Only Says “Taken” or “Available”


Imagine a signup form that checks if a username is already taken. You type in “admin,” and it returns `{"taken": true}`. You type "asdfgh123," and it returns `{"taken": false}`. Behind the scenes, the application is running a…

---

*Originally published on [Medium](https://infosecwriteups.com/bug-bounty-bootcamp-28-boolean-based-blind-sql-injection-extracting-data-one-true-false-at-a-abe69e3de702). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
