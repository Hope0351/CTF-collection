# :game_die: HTB Academy [writeup]

> **Original Source:** [HTB Academy [writeup]](https://infosecwriteups.com/htb-academy-writeup-bf518031e7f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Academy [writeup]


## Business Logic Vulnerability | ADM Group


## Summary


This machine is about the business logic issues, vulnerable framework and exposed credentials. To begin with, — During registration, I was able to change the role id via burpsuite to make myself the admin and successfully login to admin page. Moving forward, the sub-domain found on the admin page leaks error details of a vulnerable PHP Laravel Framework and its APP Key Hash was exposed. Exploiting that got me the low reverse shell. Through this shell, a user credential was found which I used it to login and gain access. I then found another user credentials in that user account and gained further vertical privilege escalation.


For Root, the user was able to execute a command with superuser privilege exploiting which got me the root.


Computing Platform: Ubuntu


Keywords: PHP | MySQL | PHP Laravel Framework

## Reconnaissance & Enumeration


Nmap TCP Scan Output


### Port 80/tcp open http Apache httpd 2.4.41

---

*Originally published on [Medium](https://infosecwriteups.com/htb-academy-writeup-bf518031e7f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
