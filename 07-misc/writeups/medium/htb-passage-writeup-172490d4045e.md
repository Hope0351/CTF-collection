# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/htb-passage-writeup-172490d4045e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Passage [writeup]


## Unrestricted file upload | RCE | weak password | d-bus vulnerability


### Enumeration


Nmap TCP Scan Output


### FOOTHOLD


** PORT 80 HTTP **


The IP is running on port 80 and has a web-page. At the bottom of the main page, it says powered by **CuteNews - PHP News Management System.**


Enter ‘CuteNews’ on the URL and you will see its login portal page.


Notice the CuteNews version 2.1.2 and search for the [exploit](https://www.exploit-db.com/exploits/48458)!


CuteNews 2.1.2 is vulnerable to ‘avatar’ Remote Code Execution

### Reverse Shell

---

*Originally published on [Medium](https://infosecwriteups.com/htb-passage-writeup-172490d4045e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
