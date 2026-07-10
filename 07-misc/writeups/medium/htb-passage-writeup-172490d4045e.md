# :game_die: Medium

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
