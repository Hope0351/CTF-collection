# :game_die: HTB Blunder [writeup]

---

# HTB Blunder [writeup]

## Bludit 3.9.2 Password Brute Force | Security Policy Bypass

## Summary

The machine - 10.10.10.191 is running bludit web-application v3.9.2 on port 80. This application is vulnerable to its PHP code for anti-brute force function; modifying this code allows password bruteforce attack meaning, the attacker does not get locked out even after several failed attempts to login. Password was successfully retrieved by exploiting this bludit anti-bruteforce function.

For vertical escalation privilege, checking for the user sudo permission revealed that the user can run all the commands and as any user except root. However, the sudo does not check for a specific user id in negative value and is able to bypass this exclusion to gain root.

### Computing Platform: Linux Ubuntu

### Tools Used:

- Reconnaissance — `cewl` | `source code review`

- Enumeration — `Nmap` | `wfuzz` | `dirb` | `msfconsole`

- Exploit — Bludit password Brute-Force script | Bludit CMS Arbitrary File Upload (CVE-2019–16113)

### Key words: Bludit | PHP | sudo | source code

## Reconnaissance & Enumeration

---
