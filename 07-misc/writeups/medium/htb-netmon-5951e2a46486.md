# :game_die: HTB - Netmon. Default creds for the win!

---

# HTB — Netmon

## Default creds for the win!

*Photo by [Morthy Jameson](https://unsplash.com/@theothermorthy?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

Starting with an Nmap scan we see which ports are open for us to inspect

```
┌─[us-dedivip-1]─[10.10.14.8]─[dfaultssec@htb-ssnmgik0rc]─[~]
└──╼ [★]$ nmap -sT -T4 -sC -sV -p- 10.129.6.42
Starting Nmap 7.93 ( <https://nmap.org> ) at 2024-02-21 04:33 GMT
Warning: 10.129.6.42 giving up on port because retransmission cap hit (6).
Nmap scan report for netmon.htb (10.129.6.42)
Host is up (0.24s latency).
Not shown: 65521 closed tcp ports (conn-refused)
PORT STATE SERVICE VERSION
21/tcp open ftp Microsoft ftpd
| ftp-syst:
|_ SYST: Windows_NT
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
| 02-02-19 11:18PM 1024 .rnd
| 02-25-19 09:15PM <DIR> inetpub
| 07-16-16 08:18AM <DIR> PerfLogs
| 02-25-19 09:56PM <DIR> Program Files
| 02-02-19 11:28PM <DIR> Program Files (x86)
| 02-03-19 07:08AM <DIR> Users
|_11-10-23 09:20AM <DIR> Windows
80/tcp open http Indy httpd 18.1.37.13946 (Paessler PRTG bandwidth monitor)
| http-title: Welcome | PRTG Network Monitor (NETMON)
|_Requested resource was /index.htm
|_http-trane-info: Problem with XML parsing of /evox/about
|_http-server-header: PRTG/18.1.37.13946
135/tcp open msrpc Microsoft Windows RPC
139/tcp open netbios-ssn Microsoft Windows…
```

---
