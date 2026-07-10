# :game_die: APPLICATION SECURED ? LET’S CHECK IT WITH SQL INJECTIONS 😈

> **Original Source:** [APPLICATION SECURED ? LET’S CHECK IT WITH SQL INJECTIONS 😈](https://infosecwriteups.com/application-secured-lets-check-it-with-sql-injections-841ee318ed4b)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# APPLICATION SECURED ? LET’S CHECK IT WITH SQL INJECTIONS 😈


Hello guys, I am back again with an interesting blog . Have a look !! 😍


## ~# Table of Content :


🔹What is SQLI


🔹 Tools I used


🔹 The bug I got

## ~# Now, what are SQL Injections or Structured Query Language Injections 💉 ? 🤔


So basically , there is a sql query (request for data or information from a database table or combination of tables) on the web application which is sent to the database and this query is executed on the database and relevant information is returned back to the Web Application …


In SQL Injection, we manipulate the database query by injecting malicious payloads (in the form of strings or encoded strings) in order to make the application perform tasks that are ideally not supposed to be done . So, an attacker can bypass authentication, steal data, modify data, delete data, run arbitrary code and also gain root access …


Now, when a user logs into the web application, API requests are sent to the database . If the credentials match the existing data of that particular user in the database, the user successfully gets logged in. On the other hand, if the credentials don’t match the…

---

*Originally published on [Medium](https://infosecwriteups.com/application-secured-lets-check-it-with-sql-injections-841ee318ed4b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
