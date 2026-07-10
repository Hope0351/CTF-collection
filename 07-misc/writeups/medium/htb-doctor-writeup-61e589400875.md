# :game_die: HTB Doctor [writeup]

> **Original Source:** [HTB Doctor [writeup]](https://infosecwriteups.com/htb-doctor-writeup-61e589400875)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Doctor [writeup]


## Server-Side Template Injection | Splunk UF RCE


## Summary


This machine is running a web application on port 80 that is vulnerable to Server-Side Template Injection (SSTI). This attack can be used to directly attack the internal web server, resulting in RCE attack.


The web application running on this machine is using Twig(PHP) template to embed dynamic content in web pages and emails. Using this web application, user can post comment after getting themself registered to this system. Since there is nosanitizationcheck when the user inputs the data, it therefore makes it highly vulnerable to SSTI attack.


For privilege Escalation, during enumeration it was found that the root can be achieved by simply exploiting the splunk universal forwarder RCE exploit. Remember, this machine is running Splunk Atom Feed: Splunkd Rest API on port 8089.


Computing Platform: Ubuntu


Tools Used:


- Enumeration — `nmap` | `gobuster` | `dirsearch.py`

- Linux box Enumeration — `linpeas.sh` | `ps -aux` | `/etc/passwd`

- Exploit — custom code | [pySplunkWhisperer2](https://github.com/DaniloCaruso/SplunkWhisperer2/blob/master/PySplunkWhisperer2/PySplunkWhisperer2_remote.py)


CVE(s):Keywords: Linux | Server: werkzeug/1.0.1 python 3.8.2 | splunkd 8.0.5 | Apache/2.4.41 (Ubuntu) Server | REST API | SSTI

## Enumeration


Nmap TCP Scan Output

---

*Originally published on [Medium](https://infosecwriteups.com/htb-doctor-writeup-61e589400875). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
