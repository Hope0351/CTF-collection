# :globe_with_meridians: Source Thm Box Writeup 7B54454D8365

> **Original Source:** [Source Thm Box Writeup 7B54454D8365](https://infosecwriteups.com/source-thm-box-writeup-7b54454d8365)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

In Every Penetration testing engagement we start with recon, thereby we start by scanning the target for open ports.


I tried the full scan and found two open ports :


SSH = 22
Webmin = 10000

*Scanning port 10000*


after that lets do a service scan for this port to see what service is running :


## Get Cyb0rgBytes’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


nmap -sC -sV -p 10000 10.10.14.207 -oA servicewebmin


*Service Scan of the Port.*


if we look closer we can find that port 10000 has Webmin httpd, it’s version is 1.890 which seems vulnerable to a known exploit.


lets search with searchsploit to see if the exploit is available in exploitdb.


*Searching ExploitDB with SearchSploit.*


We can clearly find that there is an exploit for this version, lets use metasploit get a shell on the box.


*GOT Root.*


Thanks for Reading Everyone & Stay Tuned for the next Writeups.

---

*Originally published on [Medium](https://infosecwriteups.com/source-thm-box-writeup-7b54454d8365). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
