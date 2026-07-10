# :globe_with_meridians: Burp Suite? No Thanks! Blind SQLi in DVWA With Python (Part 3) — StackZero

---

# Burp Suite? No Thanks! Blind SQLi in DVWA With Python (Part 3) — StackZero

>



![img_1.jpeg](images/burp-suite-no-thanks-blind-sqli-in-dvwa-with-python-part-3-stackzero-911545003f0/img_1.jpeg)
This article was originally published at [https://www.stackzero.net/blind-sql-injection-dvwa-high-python/](https://www.stackzero.net/blind-sql-injection-dvwa-high-python/)

Hey hackers!
In this article, we are going to use Python to exploit [DVWA](https://github.com/digininja/DVWA) by using a Blind SQL Injection attack on a high level of security.

You probably would remember from previous articles or maybe your background what is Blind SQL Injection.
Anyway, just as a refresher, SQL Injection it’s an attack that takes advantage of bad input management from the server.
This flaw allows the hacker to inject a SQL payload that potentially gives him full control of the database (it also depends on the database user privileges).

Blind SQL Injection is nothing more than an SQL Injection attack where the attacker cannot see the result on the output but have to infer that from the application behaviour.

I know that it might sound complicated, but it is not.
In this article, I will take many things for granted, so if you find this reading too hard, I invite you to read my previous posts.

## In-Band SQL injection

---
