# :game_die: HTB OpenkeyS [writeup]. OpenBSD Authentication Bypass | HTTP…

---

# HTB OpenkeyS [writeup]

## OpenBSD Authentication Bypass | HTTP Header Tampering | Kernel OS Local Root Exploit

## **SummaryUser -** This machine is running an OpenBSD httpd site which has a login portal with only a sign-in feature working. Upon research, it was found to have a vulnerability that exposes the user’s private key enabling us to login using SSH.

**Root -** A local exploit was found for openbsd; executing which gave me the root!

**Tools Used: **`nmap` | `ssh` | `dirbuster` | `wget`

**CVE(s): **[CVE-2019-19520](https://github.com/bcoles/local-exploits/blob/master/CVE-2019-19520/openbsd-authroot) | [CVE-2019–19521](https://github.com/bcoles/local-exploits/blob/master/CVE-2019-19520/openbsd-authroot)

**Keywords: **openbsd httpd | ssh | jennifer

## Reconnaissance an Enumeration

**Nmap Scan TCP Output** PORT 80 OpenBSD httpd ***

This site has a login portal.

Attempted some common used credentials but nothing worked.

---
