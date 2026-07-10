# :game_die: HTB — Included

---

# HTB — Included

## Can you enumerate your way to the top?

*Photo by [Conor Sheridan](https://unsplash.com/@mrconorsheridan?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Recon

## Nmap scan

```
➜ ~ sudo nmap -sC -sV -T4 -p- 10.129.95.185

Starting Nmap 7.94SVN ( <https://nmap.org> ) at 2024-11-08 21:42 EST
Nmap scan report for 10.129.95.185
Host is up (0.094s latency).
Not shown: 65534 closed tcp ports (reset)
PORT STATE SERVICE VERSION
80/tcp open http Apache httpd 2.4.29 ((Ubuntu))
|_http-server-header: Apache/2.4.29 (Ubuntu)
| http-title: Site doesn't have a title (text/html; charset=UTF-8).
|_Requested resource was <http://10.129.95.185/?file=home.php>
Service detection performed. Please report any incorrect results at <https://nmap.org/submit/> .
Nmap done: 1 IP address (1 host up) scanned in 208.96 seconds
```

Running a UDP scan with Nmap shows an open port that wasn’t revealed in the initial scan

```
➜ ~ sudo nmap -sV -sU -T4 included.htb -vv

Discovered open port 69/udp on 10.129.95.185 [0/761]
Completed NSE at 14:21, 0.18s elapsed
NSE: Starting runlevel 2 (of 2) scan.
Initiating NSE at 14:21
Completed NSE at 14:21, 1.01s elapsed
Nmap scan report for included.htb (10.129.95.185)
Host is up, received echo-reply ttl 63 (0.097s latency).
Scanned at 2024-11-09 14:02:47 AST for 1151s
Not shown: 982 closed udp…
```

---
