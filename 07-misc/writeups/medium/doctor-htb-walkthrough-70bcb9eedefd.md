# :game_die: Doctor: HackTheBox Walkthrough. Description

> **Original Source:** [Doctor: HackTheBox Walkthrough. Description](https://infosecwriteups.com/doctor-htb-walkthrough-70bcb9eedefd)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Doctor: HackTheBox Walkthrough


Doctor is a nice VM on [HackTheBox](https://app.hackthebox.eu/machines/278). I must say the easy boxes on HTB are tougher and knowledgeable than medium boxes on TryHackMe. Just add doctors.htb in your /etc/hosts file and you are good to goo.


>

Knowledge Gained


- Enumeration

- Server-Side Template Injection

- Gaining reverse shell in two ways

- Enumerating adm related files

- Privilege escalation using SplunkWhisperer2

>

Port Scanning


As usual start with scanning the network with Nmap for open ports and services.


>

Web Reconnaissance


So Let’s first enumerate port 80. I decided to start a gobuster scan and got something useful.


So we have a login portal.

---

*Originally published on [Medium](https://infosecwriteups.com/doctor-htb-walkthrough-70bcb9eedefd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
