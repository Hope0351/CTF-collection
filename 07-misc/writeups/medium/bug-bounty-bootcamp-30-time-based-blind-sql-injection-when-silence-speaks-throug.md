# :game_die: “Bug Bounty Bootcamp #30: Time-Based Blind SQL Injection - When Silence Speaks Through Delays”

> **Original Source:** [“Bug Bounty Bootcamp #30: Time-Based Blind SQL Injection - When Silence Speaks Through Delays”](https://infosecwriteups.com/bug-bounty-bootcamp-30-time-based-blind-sql-injection-when-silence-speaks-through-delays-7e2107b6dc18)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# “Bug Bounty Bootcamp #30: Time-Based Blind SQL Injection — When Silence Speaks Through Delays”


## The application never shows an error, never says “true” or “false” — just “email added” every time. Yet you can still drain the database. Learn to use database sleep commands as your covert data exfiltration channel.


[Free Link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-30-time-based-blind-sql-injection-when-silence-speaks-through-delays-7e2107b6dc18?sk=ddd2e13f14db07a3d3dd7fe04d7002d4)


Welcome back to the Bug Bounty Bootcamp. You’ve mastered boolean blind SQL injection, where true/false responses guide your extraction. But what happens when even those binary signals are gone — when every request returns the same generic success message? This is Time-Based Blind SQL Injection, one of the most challenging and stealthy attack vectors. You ask the database a yes/no question, but instead of reading a visible answer, you measure time. A delayed response means “yes.” An immediate response means “no.” By sending hundreds or thousands of these timed queries, you reconstruct the entire database — one character at a time — without ever seeing a single piece of data directly.

## The Scenario: The Silent Newsletter Signup


Imagine a newsletter subscription form. You enter any email, and the page simply says “Email…

---

*Originally published on [Medium](https://infosecwriteups.com/bug-bounty-bootcamp-30-time-based-blind-sql-injection-when-silence-speaks-through-delays-7e2107b6dc18). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
