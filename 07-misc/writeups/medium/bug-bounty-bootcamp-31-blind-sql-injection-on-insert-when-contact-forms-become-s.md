# :game_die: “Bug Bounty Bootcamp #31: Blind SQL Injection on INSERT — When Contact Forms Become Silent Data Mines”

> **Original Source:** [“Bug Bounty Bootcamp #31: Blind SQL Injection on INSERT — When Contact Forms Become Silent Data Mines”](https://infosecwriteups.com/bug-bounty-bootcamp-31-blind-sql-injection-on-insert-when-contact-forms-become-silent-data-dfa5f8ddffe8)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# “Bug Bounty Bootcamp #31: Blind SQL Injection on INSERT — When Contact Forms Become Silent Data Mines”


## No error messages, no data reflection, just a polite “thanks for your message.” Yet with a well-placed sleep command, you can prove database access and exfiltrate secrets — one delayed second at a time.


[Free link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-31-blind-sql-injection-on-insert-when-contact-forms-become-silent-data-dfa5f8ddffe8?sk=34b2416c3249215c9963c7e14d02e03f)


Welcome back to the Bug Bounty Bootcamp. You’ve conquered error-based and UNION-based SQL injection, and you’ve mastered boolean and time-based blind attacks on SELECT queries. Now, we tackle one of the trickiest scenarios: blind SQL injection on INSERT statements. Think of contact forms, newsletter signups, support tickets — anywhere your input gets stored but never shown back to you. The application only says “submitted successfully” or nothing at all. No data comes out. Yet you can still prove the vulnerability and extract sensitive information using time delays. This is the art of making the database talk when it’s been sworn to silence.

## The Silent Form: When Every Response Looks the Same


Imagine a “Contact Us” page with fields for name, email, and message. You submit it. The page says “Thanks for your message.” Every…

---

*Originally published on [Medium](https://infosecwriteups.com/bug-bounty-bootcamp-31-blind-sql-injection-on-insert-when-contact-forms-become-silent-data-dfa5f8ddffe8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
