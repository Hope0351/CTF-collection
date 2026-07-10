# :game_die: “Bug Bounty Bootcamp #29: Boolean Blind SQL Injection Part 2 - Extracting Usernames and Passwords One Character at a Time”

> **Original Source:** [“Bug Bounty Bootcamp #29: Boolean Blind SQL Injection Part 2 - Extracting Usernames and Passwords One Character at a Time”](https://infosecwriteups.com/bug-bounty-bootcamp-29-boolean-blind-sql-injection-part-2-extracting-usernames-and-passwords-13447abeb6d6)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# “Bug Bounty Bootcamp #29: Boolean Blind SQL Injection Part 2 — Extracting Usernames and Passwords One Character at a Time”


## I was staring at a clean search page on a private bug bounty program. No errors. No leaked data. Just “No results” or a normal page load


[Free link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-29-boolean-blind-sql-injection-part-2-extracting-usernames-and-passwords-13447abeb6d6?sk=5283bcdbea32ee536f21f3bf5a79b50b)


I typed one innocent-looking payload. The page flipped. True response. False response.


I asked the database a yes/no question… and it answered. Letter by letter I pulled out real usernames. Then their passwords. No union dump. No error messages. No time delays. Just pure boolean logic.


This is **Boolean Blind SQL Injection** — and once you master it, you’ll start seeing it everywhere.

## What Is Boolean Blind SQL Injection?


It’s SQL injection where the app **never shows you the data** and **never throws errors**. But it still lets you ask the database true/false questions.


You inject a condition.


- If your guess is correct → the page behaves one way (true).

- If wrong → it behaves another way (false).

---

*Originally published on [Medium](https://infosecwriteups.com/bug-bounty-bootcamp-29-boolean-blind-sql-injection-part-2-extracting-usernames-and-passwords-13447abeb6d6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
