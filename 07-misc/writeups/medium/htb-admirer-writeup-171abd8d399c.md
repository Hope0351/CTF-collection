# :game_die: HTB Admirer [Writeup]

> **Original Source:** [HTB Admirer [Writeup]](https://infosecwriteups.com/htb-admirer-writeup-171abd8d399c)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Admirer [Writeup]


## Sensitive File Disclosure | Python Library Hijacking


## Summary:


For this machine, using `gobuster` command exposed the credentials to access the open FTP port which led to finding out about the vulnerable MySQL database that allows foreign server to import arbitrary data exposing credentials. i.e. you could implement a local database and table giving full privilege and connect it to the vulnerable MYSQL database.


For root, a script was found to execute as root using `sudo` command. Upon reviewing the script code, the Python Library Hijacking technique was then attempted to escalate privilege to get root.

### Tools Used:


- `Nmap`

- `gobuster`

- `gunzip` and `tar -xvf`

- `mysql -h localhost -u <username> -p`

- `sudo -l`

- `nc`

- Custom python script exploit

## Enumeration


Nmap TCP Output


* PORT 80 HTTP *

---

*Originally published on [Medium](https://infosecwriteups.com/htb-admirer-writeup-171abd8d399c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
