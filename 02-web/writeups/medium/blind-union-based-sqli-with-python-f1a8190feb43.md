# :globe_with_meridians: Blind UNION-based SQLi with Python

> **Original Source:** [Blind UNION-based SQLi with Python](https://infosecwriteups.com/blind-union-based-sqli-with-python-f1a8190feb43)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Blind UNION-based SQLi with Python


See how Python can beat Burp Suite in brute-forcing speed and boost your hacking efficiency.


*Retrieved from [www.analyticsinsight.net](http://www.analyticsinsight.net)*

### [Scenario]


Once, I was sharpening my skills on blind SQL injection by enumerating a vulnerable web application. I found the trivial username ‘administrator’ and his password length using conditional statements within the cookie field:


`‘ UNION SELECT ‘a’ FROM users WHERE username=’administrator’ AND length(password)=20--`


What was the indication that this is a successful SQLi hunt? Let’s see what the BurpSuite Comparer has to offer:

---

*Originally published on [Medium](https://infosecwriteups.com/blind-union-based-sqli-with-python-f1a8190feb43). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
