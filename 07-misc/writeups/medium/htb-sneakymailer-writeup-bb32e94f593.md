# :game_die: HTB SneakyMailer [writeup]. Mass Email Phishing | PyPi Package…

> **Original Source:** [HTB SneakyMailer [writeup]. Mass Email Phishing | PyPi Package…](https://infosecwriteups.com/htb-sneakymailer-writeup-bb32e94f593)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB SneakyMailer [writeup]


## Mass Email Phishing | PyPi Package files Abuse | pip3


## Summary


This machine has taught me some interesting attack path but especially how to setup a phishing email to extract the user credentials. The machine has an open FTP, so I uploaded the shell script and executed via the FTP sub-domain browser.


After retrieving the low privileged shell, I used the user credentials found through phishing email and using it to escalate to a developer’s account.


During the lateral movement, I found the pypi server was running on this machine and its credentials was exposed too. Configure this server to achieve escalate to another user. Using a guide found on the internet, I managed to get the shell.


Root escalation was pretty simple if basic enumeration is performed to exploit that vulnerability.

### Tools Used:


- `nmap -sCVS 10.10.10.197 -p- > nmap.txt`

- `gobuster`

- `dirsearch.py`

- `wfuzz`

- Evolution - IMAP Client


Web Server: nginx/1.14.2


Server side Language: PHP


Scripting Language: Python


Nmap TCP Scan Output

---

*Originally published on [Medium](https://infosecwriteups.com/htb-sneakymailer-writeup-bb32e94f593). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
