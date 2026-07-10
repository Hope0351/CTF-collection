# :game_die: How to perform a basic SQL Injection Attack? - Ethical Hacking

> **Original Source:** [How to perform a basic SQL Injection Attack? - Ethical Hacking](https://infosecwriteups.com/how-to-perform-a-basic-sql-injection-attack-ethical-hacking-f59e5ccbe51f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How to perform a basic SQL Injection Attack? — Ethical Hacking


## How does a SQL Injection attack work?


SQL injection attack is possible when a website exposes inputs to be taken from the user and uses the user input to directly run a query in MySQL. In this blog, I will be demonstrating how to perform a basic SQL Injection Attack on a website, and at the end, I will talk about a tool `SQLmap` , which automates the entire process.

>

If you don’t know what SQL Injection Attack is, you can visit this link. [https://www.w3schools.com/sql/sql_injection.asp](https://www.w3schools.com/sql/sql_injection.asp)


There’s a website [http://testphp.vulnweb.com/listproducts.php?cat=1](http://testphp.vulnweb.com/listproducts.php?cat=1%27) which is open for testing php vulnerablities. I will be using this website to perform SQLi attack.

## 1. Discovering if the website is vulnerable to SQL Injection attacks


The most basic and simple way is to check the URLs of pages you are visiting. If the URL is something of the form [http://testphp.vulnweb.com/listproducts.php?cat=1](http://testphp.vulnweb.com/listproducts.php?cat=1%27), it is a potential target. To check if the webpage is actually using a SQL backend, you can append `\` or a single inverted quote `‘`at the end of URL and see if anything in the page breaks or you get an SQL error. For most cases the error is something like this:

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-perform-a-basic-sql-injection-attack-ethical-hacking-f59e5ccbe51f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
