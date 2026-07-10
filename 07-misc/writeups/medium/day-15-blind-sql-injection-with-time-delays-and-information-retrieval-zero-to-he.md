# :game_die: Day 15: Blind SQL injection with time delays and information retrieval - Zero to Hero Time-Based Blind SQL Injection - Portswigger

> **Original Source:** [Day 15: Blind SQL injection with time delays and information retrieval - Zero to Hero Time-Based Blind SQL Injection - Portswigger](https://infosecwriteups.com/day-15-blind-sql-injection-with-time-delays-and-information-retrieval-zero-to-hero-time-based-75f93027eebf)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

*Used *`*' || (SELECT pg_sleep(5) FROM pg_tables WHERE schemaname = 'public' AND SUBSTRING(tablename, 1, 1) = 'u') --*`* and it was delayed by 5 seconds, which means the first character of the table name is 'u'. This is how we can enumerate it. Well, well, we already knew that the table name is 'users', but I wanted to show you how we could do it if we didn’t know.*


## Get RayofHope’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


*This is how we can enumerate the username as well, along with the number of columns and other details. Now, let’s get back to the topic and find out whether the administrator user exists or not.*

---

*Originally published on [Medium](https://infosecwriteups.com/day-15-blind-sql-injection-with-time-delays-and-information-retrieval-zero-to-hero-time-based-75f93027eebf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
