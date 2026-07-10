# :game_die: HTB — Bashed

---

# HTB — Bashed

*Photo by [Roman Synkevych](https://unsplash.com/@synkevych?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

Once the initial Nmap scan completes we see that we only have one open port on the machine

```
┌─[eu-dedivip-2]─[10.10.14.75]─[dfaultssec@htb-lfdv1ngaec]─[~]
└──╼ [★]$ nmap -sT -sC -sV -T 4 -p- 10.129.29.122
Starting Nmap 7.93 ( <https://nmap.org> ) at 2024-03-31 14:18 BST
Warning: 10.129.29.122 giving up on port because retransmission cap hit (6).
Nmap scan report for 10.129.29.122
Host is up (0.16s latency).
Not shown: 65483 closed tcp ports (conn-refused), 51 filtered tcp ports (no-response)
PORT STATE SERVICE VERSION
80/tcp open http Apache httpd 2.4.18 ((Ubuntu))
|_http-title: Arrexel's Development Site
|_http-server-header: Apache/2.4.18 (Ubuntu)
Service detection performed. Please report any incorrect results at <https://nmap.org/submit/> .
Nmap done: 1 IP address (1 host up) scanned in 701.95 seconds

```

Going into the web app on port 80 we see a site referencing `phpbash`

Checking with `ffuf` we get a few directories we can try out for vulnerabilities

```
┌─[eu-dedivip-2]─[10.10.14.75]─[dfaultssec@htb-lfdv1ngaec]─[~]
└──╼ [★]$ ffuf -u <http://10.129.29.122/FUZZ> -w…
```

---
