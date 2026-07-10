# :game_die: HTB ‘Blackfield’ [Writeup]

---

# HTB ‘Blackfield’ [Writeup]

## ASREPRoast | Dictionary attack |

*Photo by [Aaron Burden](https://unsplash.com/@aaronburden?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

### Summary

My first ever hard machine I’ve attempted so far. The user required a lot of enumeration and patience to slowly climb up the ladder. For this machine, the exposed list of users from open SMB port further allowed for active domain reconnaissance to escalate privilege and become root. No exploit was required for this machine.

Computing Platform: Windows

Tools Used: nmap | john the ripper for cracking hashes

CVE(s): n/a

### Enumeration

Nmap TCP Scan Output

nmap result got us the domain name blackfield.local. save this in /etc/hosts file. Also notice the keys words here: Kerberos, msrpc, Active Directory LDAP, domain, smb(microsoft-ds).* PORT 445 microsoft-ds (SMB) *

The machine had an open SMBserver which didn’t require any authentication. Two interesting files found were: Forensic and profile$.

forensic share required authentication but not the profiles$ share.

---
