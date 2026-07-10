# :game_die: HTB Buff [writeup]. Unauthenticated RCE | Buffer Exploit |…

> **Original Source:** [HTB Buff [writeup]. Unauthenticated RCE | Buffer Exploit |…](https://infosecwriteups.com/htb-buff-writeup-5d118ab695c0)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Buff [writeup]


## Unauthenticated RCE | Buffer Exploit | Port Forwarding


## Summary


This machines teaches you how to exploit a simple application that is vulnerable to unauthenticated RCE to get user shell. For root exploitation, it require modifying the buffer exploit code and port forwarding techniques.


Tools Used:`nmap` | `curl` | `nc` | `chisel`

## Reconnaissance and Enumeration


Nmap TCP Scan Output


## Foothold


PORT 8080 HTTP *


Under */contact.php*, we can see what it looks like could be username.


The web application is running Gym Management Software v1.0 which is vulnerable to [Remote Code Execution (RCE)](https://www.exploit-db.com/exploits/48506). The exploit works by uploading a malicious php file to /upload.php that bypasses the image upload filters.

## Reverse Shell


After downloading the exploit code and attempting to execute it, I got the following errors. However, it just required simple fix:

---

*Originally published on [Medium](https://infosecwriteups.com/htb-buff-writeup-5d118ab695c0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
