# :game_die: HTB Omni [writeup]. Exploiting Windows IoT Core using…

---

# HTB Omni [writeup]

## Exploiting Windows IoT Core using SireRAT

## Summary

This is a windows IoT machine vulnerable to Remote Code Execution (RCE). A Remote Access Trojan (RAT) tool called SirepRAT is used to exploit this vulnerability to get root.

*Photo by [Jorge Ramirez](https://unsplash.com/@jorgedevs?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

**OS: **Windows 10 IOT Core x64bit Architecture

**Tools Used:**

- nmap

- SirepRAT — Windows IOT RCE

### Reconnaissance and Enumeration - NMAP TCP Output

### FOOTHOLD

*** PORT 8080 Microsoft IIS httpd ***

Switching to port 8080, we can see the authentication is required to access this site which says “Windows Device Portal”. I google searched for ‘windows IoT exploit’, and noticed an article where regarding an open-source tool available to exploit this vulnerability.

---
