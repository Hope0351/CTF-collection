# :game_die: Write-up of Lame - An easy-rated HTB machine.

> **Original Source:** [Write-up of Lame - An easy-rated HTB machine.](https://infosecwriteups.com/write-up-of-lame-an-easy-rated-htb-machine-fa695ea2d3ca)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

>

But first, consider giving me a follow as I’ll go into details about the CVEs shown in this write-up in a separate post.


## Summary


This is a short summary of the post:


- Enumeration with Nmap

- Abusing CVEs associated with the services running

- What privilege escalation?

## Enumeration


As with all machines, we should start with a service enumeration via Nmap:


`sudo nmap -p- 10.10.10.4 -vv -T4 --min-rate 1500`


Nmap finds a few services running:


```
PORT STATE SERVICE REASON
21/tcp open ftp syn-ack ttl 63
22/tcp open ssh syn-ack ttl 63
139/tcp open netbios-ssn syn-ack ttl 63
445/tcp open microsoft-ds syn-ack ttl 63
3632/tcp open distccd syn-ack ttl 63
```


We can further enumerate these services with the `-sC` and `-sV` switches in Nmap:


`sudo nmap -sC -sV -p 21,22,139,445,3632 10.10.10.4 -vv -T4 --min-rate 1750`


The output is shown below:


```
PORT STATE SERVICE REASON VERSION [42/122]
21/tcp open ftp syn-ack ttl 63 vsftpd 2.3.4
| ftp-syst:
| STAT:
| FTP server status:
| Connected to 10.10.16.2
| Logged in as ftp
| TYPE: ASCII
| No session bandwidth limit
| Session timeout in seconds is 300
| Control connection is plain text
| Data connections will be plain text
| vsFTPd 2.3.4 - secure, fast, stable
|_End of status
|_ftp-anon: Anonymous FTP login allowed (FTP code 230)
22/tcp open ssh syn-ack ttl 63 OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
[SNIP]
139/tcp open netbios-ssn syn-ack ttl 63 Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp open netbios-ssn syn-ack ttl 63 Samba smbd 3.0.20-Debian (workgroup: WORKGROUP)
3632/tcp open distccd syn-ack ttl 63 distccd v1 ((GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4))
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```


First, we should note the version of the **FTP **server running, in this case, `vsftpd 2.3.4`. Further, we see `Samba 3.0.20` running.


## Get Echo_Slow’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


When you have version numbers of software, it’s always a good idea to run it through `Searcshploit`:


*The FTP service running appears to be backdoored.*


*While the Samba service appears to have remote command execution.*


With this information, we can move to the next stage.

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-of-lame-an-easy-rated-htb-machine-fa695ea2d3ca). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
