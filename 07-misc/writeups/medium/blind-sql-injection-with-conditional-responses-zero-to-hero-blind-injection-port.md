# :game_die: Blind SQL injection with conditional responses - Zero to Hero Blind Injection - Portswigger

> **Original Source:** [Blind SQL injection with conditional responses - Zero to Hero Blind Injection - Portswigger](https://infosecwriteups.com/blind-sql-injection-with-conditional-responses-zero-to-hero-blind-injection-portswigger-dad0cab48d57)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

- We covered the basics of SQL in the first blog, which I recommend you read. In this post, we’ll dive into the concept of Blind SQL Injection.


What is Boolean: —


Boolean in terms of programming simply means True or False. Or we can say, while performing blind injections, we are asking the server to respond to us as either true or false.


What is Blind Injection: —


Blind Injections or Blind SQL Injections. As the name suggests, these injections are used where we are successfully able to fetch critical data, but somehow the extracted data is not visible on the website, which may be attributed to how the website is built.


What is Blind Boolean SQL Injection: —


Blind SQL Boolean Injection is a type of SQL Injection attack where the attacker can’t directly see the results of their query. Instead, they rely on the application’s responses to determine whether their queries are true or false.


How to Identify Blind SQL Injection:

>

Find a injection point: — Identify a part of the application that interacts with a database (like a form field, URL parameter, or cookies)


Craft a Simple SQL Injection: — Test Start with input that doesn’t break the query, such as adding a single quote C) to see if the application reacts with an error. Like:- ‘OR ‘1’=’1Send a Boolean-based Query: — Use a condition that is always true and one that is always false to see if the response changes.
True: ‘ OR 1=1 — —
False ‘ OR 1=2 — —Observe Differences in Responses: — If the response to a true condition (like 1=1) is different from the false condition (like 1=2), there is a potential Blind Boolean-based SQL Injection


Well, well, well! We now know what Blind SQL-based Injection is. Therefore, we will go ahead and perform the exploitation, and at the end of the write-up, I’m gonna cover the mitigations too.


This is how the application looks:

---

*Originally published on [Medium](https://infosecwriteups.com/blind-sql-injection-with-conditional-responses-zero-to-hero-blind-injection-portswigger-dad0cab48d57). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
