# :game_die: Write-up of Devel - An easy-rated Windows machine on HTB

> **Original Source:** [Write-up of Devel - An easy-rated Windows machine on HTB](https://infosecwriteups.com/write-up-of-devel-an-easy-rated-windows-machine-on-htb-527f37decf99)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Enumeration


Hope you have learned what this means. We start with the basic Nmap scan:


```
sudo nmap -p- 10.10.10.5 -T4 --min-rate 1750 -vv

[SNIP]
PORT STATE SERVICE REASON
21/tcp open ftp syn-ack ttl 127
80/tcp open http syn-ack ttl 127
```


Initial enumeration shows ports 21 (FTP) and 80 (HTTP) open. With further enumeration, we obtain the following information:


```
sudo nmap -p 21,80 -sC -sV 10.10.10.5 -T4 -vv --min-rate 1750

PORT STATE SERVICE REASON VERSION
21/tcp open ftp syn-ack ttl 127 Microsoft ftpd
| ftp-syst:
|_ SYST: Windows_NT
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
| 03-18-17 02:06AM <DIR> aspnet_client
| 03-17-17 05:37PM 689 iisstart.htm
|_03-17-17 05:37PM 184946 welcome.png
80/tcp open http syn-ack ttl 127 Microsoft IIS httpd 7.5
|_http-title: IIS7
|_http-server-header: Microsoft-IIS/7.5
| http-methods:
| Supported Methods: OPTIONS TRACE GET HEAD POST
|_ Potentially risky methods: TRACE
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows
```


We have `anonymous` access to the FTP server and we know the web server version now. Since the FTP server appears to have the same root as the web server, we might have a file upload.


## Get Echo_Slow’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We test that theory by generating a file like `echo "pwned" > pwned.txt` and uploading it to the FTP server via `put pwned.txt`. Once we have done that we can visit the web server like `[http://10.10.10.6/pwned.txt](http://10.10.10.6/pwned.txt.)`[.](http://10.10.10.6/pwned.txt.)

*We see our text on the web server. This means we have file upload.*


To abuse this file upload, we first need to know if we need an `asp` or `aspx` payload. The difference between the two file types is: **ASP **is based on **VBScript**, while **ASPX **uses **C#**. It’s more likely that the correct payload is the `aspx` file, but if in doubt, generate both and try to execute each.

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-of-devel-an-easy-rated-windows-machine-on-htb-527f37decf99). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
