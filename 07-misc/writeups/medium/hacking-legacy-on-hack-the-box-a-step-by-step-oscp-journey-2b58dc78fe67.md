# :game_die: Hacking Legacy on Hack the Box: A Step by Step OSCP Journey

---

# Hacking Legacy on Hack the Box: A Step by Step OSCP Journey

A Windows box with 2 direct exploit paths.

🔥 FREE VERSION: Free Article🔥

*Legacy*

We’re going through Legacy this time. A windows box with 2 exploit paths and 2 famous and critical CVEs.. Let’s get to work.

I’ll begin with an nmap scan to see what ports we’re working with:

```
sudo nmap -sC -sV -A -T4 10.10.10.4 -p135,139,445
Starting Nmap 7.94SVN ( https://nmap.org ) at 2025-01-02 13:57 CST
Stats: 0:00:08 elapsed; 0 hosts completed (1 up), 1 undergoing Service Scan
Service scan Timing: About 0.00% done
Stats: 0:00:12 elapsed; 0 hosts completed (1 up), 1 undergoing Script Scan
NSE Timing: About 97.87% done; ETC: 13:57 (0:00:00 remaining)
Nmap scan report for 10.10.10.4
Host is up (0.0094s latency).

PORT STATE SERVICE VERSION
135/tcp open msrpc Microsoft Windows RPC
139/tcp open netbios-ssn Microsoft Windows netbios-ssn
445/tcp open microsoft-ds Windows XP microsoft-ds
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Aggressive OS guesses: Microsoft Windows XP SP2 or SP3 (96%), Microsoft Windows XP SP3 (96%), Microsoft Windows Server 2003 SP1 or SP2 (94%), Microsoft Windows Server 2003 SP2 (94%), Microsoft Windows Server 2003 SP1 (94%), Microsoft Windows 2003 SP2 (94%), Microsoft Windows 2000 SP4 or Windows…
```

---
