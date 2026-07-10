# :game_die: HTB Time [writeup]. Exploiting the RCE and SSRF…

> **Original Source:** [HTB Time [writeup]. Exploiting the RCE and SSRF…](https://infosecwriteups.com/htb-time-writeup-1c5b51a82eb7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Time [writeup]


## RCE and SSRF Vulnerabilities


## Reconnaissance & Enumeration


Nmap TCP/UDP Scan Output


## Foothold


PORT 80/tcp http Apache httpd 2.4.41 (Ubuntu) *


This is an Online JSON parser Site. There were two options under the dropdown menu. (1.) Beautify (2.) Validate(beta!)


When I typed a simple “Test This Site” in the Beautify textbox, The output was Null.


But, when I included the same text under the “Validate (beta!)”, it throws some error message.


Upon Google search, I came across quite a few CVE related to ‘com.fasterxml.jackson.core.JsonParseException’. However, upon several tried and tested attempted using their Steps to Reproduce, the one that worked for me was the CVE-2019–12384. This exploits the RCE and SSRF vulnerabilities.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-time-writeup-1c5b51a82eb7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
