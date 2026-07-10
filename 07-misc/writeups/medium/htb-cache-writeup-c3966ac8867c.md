# :game_die: HTB ‘Cache’ [writeup]

> **Original Source:** [HTB ‘Cache’ [writeup]](https://infosecwriteups.com/htb-cache-writeup-c3966ac8867c)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB ‘Cache’ [writeup]


## SQL Injection | unauth Memcached exposed creds | Docker Linux Image Exploit


### Summary


Cache required a combination of enumeration and instincts rather then using extensive range of scanning tools. e.x. mapping the ip address to hms.htb instead of cache.htb; The vulnerability exploited in this machine is the top most common vulnerabilities listed in OWASP Top 10 — The SQL Injection. Exploiting this vulnerability in the web-based application’s (openEMR) login portal exposed the application’s user credentials. Using this, the account was accessed. PHP reverse shell was spun and user.txt was retrieved after logging as user ash.


Achieving root required only one line command once you have enumerated the basics. It’s easy especially when you either already know about this vulnerability or you know where to search for.


Platform: Linux Ubuntu


Tools: `nmap` | `sqlmap` | `docker` | `telnet`


Exploit:[OpenEMR < 5.0.1 Authenticate RCE](https://www.exploit-db.com/exploits/45161) | [Docker Linux Image Exploit](https://gtfobins.github.io/gtfobins/docker/)

### Enumeration


Nmap TCP Scan Output

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cache-writeup-c3966ac8867c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
