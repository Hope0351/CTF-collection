# :game_die: Paginator v2- NullCon CTF 2025. Paginator v2 is a web challenge of the…

> **Original Source:** [Paginator v2- NullCon CTF 2025. Paginator v2 is a web challenge of the…](https://infosecwriteups.com/paginator-v2-nullcon-ctf-2025-7bc5f8f445b4)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

# Paginator v2- NullCon CTF 2025


[Paginator v2](https://ctf.nullcon.net/challenges#Paginator%20v2-91) is a web challenge of the [NullCon CTF 2025](https://ctf.nullcon.net/)
Link for challenge: [http://52.59.124.14:5015/](http://52.59.124.14:5015/)

*Paginator v2*


On accessing the link, I got a webpage like the one below:


*Paginator v2 webpage*


On clicking “Show me pages 2–10”, it gives records of pages from ID 2 to 10.


*Pages from ID 2 to 10*


Now, I checked the source code of this webpage.


*Source code of Paginator v2*


Here, in the first try block, it executes a create table command and 10 insert commands. Unlike [Paginator v1](http://52.59.124.14:5012), where the flag was encoded as base64 string in the first record of pages table, here the flag is itself not in the pages table. So, basic SQL injection commands won’t work.


*Basic SQLi payload result*


Therefore, I came to a conclusion that they might have made a new table related to it. So, I checked up on some union-based injection payloads. I guessed the name of the table to be “flag” and since I had no information on the no. of rows or the row in which the flag was present, I had to use an asterisk(*).


## Get Vedant Pillai’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So, the payload became:


```
2,10 UNION SELECT * FROM flag
```


*Union-based SQLi payload result*


BINGO! I got the base64 encoded flag.


Now, I just had to decode it.


*Decode base64 flag*


```
FLAG: ENO{SQL1_W1th_0uT_C0mm4_W0rks_SomeHow_AgA1n_And_Ag41n!}
```


References:
1. [SQL Injection Using UNION](https://www.sqlinjection.net/union/)


2. [Base64 Decode and Encode — Online](https://www.base64decode.org/)

---

*Originally published on [Medium](https://infosecwriteups.com/paginator-v2-nullcon-ctf-2025-7bc5f8f445b4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
