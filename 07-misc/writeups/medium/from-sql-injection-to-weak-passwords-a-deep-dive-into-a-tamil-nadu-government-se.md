# :game_die: From SQL Injection to Weak Passwords 🔓: A Deep Dive into a Tamil Nadu Government Security Flaw 🚨

> **Original Source:** [From SQL Injection to Weak Passwords 🔓: A Deep Dive into a Tamil Nadu Government Security Flaw 🚨](https://infosecwriteups.com/from-sql-injection-to-weak-passwords-a-deep-dive-into-a-tamil-nadu-government-security-flaw-1b648d62d457)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# From SQL Injection to Weak Passwords 🔓: A Deep Dive into a Tamil Nadu Government Security Flaw 🚨


One morning, coffee in hand ☕, I began testing a new target from the Tamil Nadu Government and spotted signs of SQL injection. I ran SQLmap, which showed it was a time-based flaw. Here’s how, with just my coffee and SQLmap, I uncovered a vulnerability that let me view user data on a Tamil Nadu government website.

### How did I find?


As you might already know, we usually add some special characters in the input fields to see how the web server reacts. If the website throws an error, then boom 💥 — it’s a sign that there’s an SQL injection.


In my case, when I placed a single quote (`'`) into the GET input, instead of the website handling it smoothly, the server threw a 500 Internal Server Error. This type of error usually means that the server couldn't process the request properly, often because something broke in the backend.


Seeing this made me almost certain that the input was directly interacting with the database without proper validation or sanitisation — a classic sign of SQL injection. I smiled, sipped my coffee ☕, and thought, “Well, well, looks like we’re onto something juicy!” 😎


Without wasting any more time, with half a cup of coffee ☕ and full curiosity 🕵️‍♂️, I fired up SQLmap and launched it with the following command. 🚀


```
sqlmap -u "https://example.com/backend/generateKey.php?username=" --batch --threads=10 --level=3
```


I sat back, let SQLmap do its magic, and… boom 💥!


It didn’t take long before I discovered the type of injection present in that organisation’s system.


This revealed that by using the — dump command, I could pull data straight from the organisation’s database. 😎
Now, for those who are curious, here are some of the most powerful (and, let’s be honest, *malicious*) commands in SQLmap:


```
sqlmap -u "https://example.com/backend/generateKey.php?username=" --batch --threads=10 --level=3 --dump
sqlmap -u "https://example.com/backend/generateKey.php?username=" --batch --threads=10 --level=3 --dump-all --tables
sqlmap -u "https://example.com/backend/generateKey.php?username=" --batch --threads=10 --level=3 --sql-shell
sqlmap -u "https://example.com/backend/generateKey.php?username=" --batch --threads=10 --level=3 -D <database_name> --tables
```


If in the wrong hands, these commands can be a hacker’s dream, allowing anyone to easily access the database. 🕵️‍♂️💻

### Another Overlooked Issue: Weak Passwords


When I dumped one of the tables, I stumbled upon the user database, which contained a table full of sensitive usernames and hashed passwords. But here’s where it got interesting — I decided to search those hashes using a simple Google dork. And to my surprise, I uncovered something *incredibly important*: the password wasn’t just weak, it was *ancient*, like something set back in the days of Adam and Eve! 🕵️‍♂️🔓


## Get B4LOGI’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


When I tried the username and password combo, I couldn’t believe my eyes — I was in! 😱 I had just logged into one of the most critical organisations in Tamil Nadu. Not only that, but I was the superadmin of the application now. I had full control — I could add new users, delete old ones, and do anything I wanted. The web application was now my playground. 🏰🚀


The database I accessed contained a massive amount of Personally Identifiable Information (PII) — everything from details about the employees, their presence and absence records, to the services they provided. This means that anyone with access to this simple username and password could log in and wreak havoc on the system. It’s terrifying to think that something so sensitive could be exposed so easily. 😬


But, being the ethical hacker I am, I didn’t take advantage of the situation. Instead, I responsibly reported the vulnerability to the CERT-In, ensuring they were aware of the issue and could fix it before anyone else could exploit it. 🛡️💻


📢 Disclaimer: The knowledge shared here is strictly for educational purposes. The usage of these commands to perform malicious actions is a serious offence and punishable by law. 🚨

---

*Originally published on [Medium](https://infosecwriteups.com/from-sql-injection-to-weak-passwords-a-deep-dive-into-a-tamil-nadu-government-security-flaw-1b648d62d457). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
