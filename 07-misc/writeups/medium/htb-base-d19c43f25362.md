# :game_die: HackTheBox Base Walkthrough

> **Original Source:** [HackTheBox Base Walkthrough](https://infosecwriteups.com/htb-base-d19c43f25362)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HackTheBox Base Walkthrough


## Exploiting strcmp() for Root


*Photo by [Jeswin Thomas](https://unsplash.com/@jeswinthomas?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Enumeration


## Nmap


```
└──╼ [★]$ nmap -T5 -p- -sCV --script exploit base.htb
Starting Nmap 7.94SVN ( <https://nmap.org> ) at 2025-07-09 07:29 CDT
Nmap scan report for base.htb (10.129.95.184)
Host is up (0.086s latency).
Not shown: 65533 closed tcp ports (reset)
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 7.6p1 Ubuntu 4ubuntu0.7 (Ubuntu Linux; protocol 2.0)
80/tcp open http Apache httpd 2.4.29 ((Ubuntu))
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-dombased-xss: Couldn't find any DOM based XSS.
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.
| http-csrf:
| Spidering limited to: maxdepth=3; maxpagecount=20; withinhost=base.htb
| Found the following possible CSRF vulnerabilities:
|
| Path: <http://base.htb:80/>
| Form id: name
| Form action: forms/contact.php
|
| Path: <http://base.htb:80/>
| Form id:
| Form action:
|
| Path: <http://base.htb:80/index.html>
| Form id: name
| Form action: forms/contact.php
|
| Path: <http://base.htb:80/index.html>
| Form id:
| Form action:
|
| Path: <http://base.htb:80/login/login.php>
| Form id: login-form
| Form action:
|
| Path: <http://base.htb:80/login/login.php>
| Form id:
|_ Form action:
Service Info: OS…
```

---

*Originally published on [Medium](https://infosecwriteups.com/htb-base-d19c43f25362). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
