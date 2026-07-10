# :game_die: HTB - Jerry. What do you say Tom, can you catch me?

> **Original Source:** [HTB - Jerry. What do you say Tom, can you catch me?](https://infosecwriteups.com/htb-jerry-0947990ec3ca)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB — Jerry


## What do you say, Tom, can you catch me?


Starting with an Nmap scan we find 1 open port


```
# Nmap 7.93 scan initiated Wed Jan 24 01:18:54 2024 as: nmap -sV -sC -Pn -p 8080 -o nmap.txt jerry.htb
Nmap scan report for jerry.htb (10.129.145.195)
Host is up (0.097s latency).

PORT STATE SERVICE VERSION
8080/tcp open http Apache Tomcat/Coyote JSP engine 1.1
|_http-server-header: Apache-Coyote/1.1
|_http-favicon: Apache Tomcat
|_http-title: Apache Tomcat/7.0.88
Service detection performed. Please report any incorrect results at <https://nmap.org/submit/> .
# Nmap done at Wed Jan 24 01:19:06 2024 -- 1 IP address (1 host up) scanned in 12.54 seconds
```


Let’s try and see if the currently installed version of Apache Tomcat is vulnerable


```
$searchsploit Tomcat 7.0.88
------------------------------------------------------------------------------------------------------------------------------------------------------------ ---------------------------------
Exploit Title | Path
------------------------------------------------------------------------------------------------------------------------------------------------------------ ---------------------------------
Apache Tomcat < 9.0.1 (Beta) /…
```

---

*Originally published on [Medium](https://infosecwriteups.com/htb-jerry-0947990ec3ca). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
