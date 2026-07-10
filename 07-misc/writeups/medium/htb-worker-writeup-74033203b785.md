# :game_die: HTB Worker [writeup]

> **Original Source:** [HTB Worker [writeup]](https://infosecwriteups.com/htb-worker-writeup-74033203b785)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Worker [writeup]


## Issues: open svn port > misconfigured svn system > unrestricted file upload > misconfigured settings


## Summary


In this machine, I learnt to retrieve sensitive information from the SubVersion Control System open port 3690 via both command line and its client application.


For the reverse shell, I had to spend some time understanding how the application system works and how this could potentially be exploited. After some trials and errors, I managed to get the reverse shell of the user.


The story doesn’t end here. I couldn’t retrieve the user.txt file via the shell I got. I had to horizontal escalate to another user to get the user.txt file. After digging through the information in the user shell, I finally found the cleartext password of the another user to which I could escalate to. Using a special tool, I successfully managed to log into the another user shell and got access to the user.txt hash.


Tools Used:


- `nmap`

- `dirsearch.py` to find hidden directories and contents

- `svn info svn://10.10.10.203`, `svn list svn://10.10.10.203` svn which is subversion and is a version control system to keep track of the files and directories information.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-worker-writeup-74033203b785). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
