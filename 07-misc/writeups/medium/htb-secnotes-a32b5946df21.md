# :game_die: Htb Secnotes A32B5946Df21

> **Original Source:** [Htb Secnotes A32B5946Df21](https://infosecwriteups.com/htb-secnotes-a32b5946df21)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/SecNotes).


*SecNotes*

### Skill Learned


- SQLi authentication bypass

- Windows Subsystem for Linux (WSL) Enumeration

## NMAP/ Rustscan


IP: 10.10.10.97

*rustscan -a 10.10.10.97*


*nmap scan for 80,445 and 8808*

### Port 80


*port 80*


Let’s run Gobuster for .php


```
gobuster dir -u http://10.10.10.97/ -w /usr/share/seclists/Discovery/Web-Content/common.txt -x php
```


*gobuster*


Let’s try admin: admin

*admin:admin*


Let’s try for SQL injection

*SQL Injection*


It’s giving no username account


Let’s try to make one and login


*login as ‘ OR 1 OR ‘*


this means we have SQL injection in sign up/ login and we found some cred for Tyler

*tyler creds*

## Foothold/ shell


Since we get the password for Tyler we can try psexec with the cred


```
psexec.py tyler:'92g!mA8BGjOirkL%OG*&'@10.10.10.97
```


*psexec.py tyler:’92g!mA8BGjOirkL%OG*&’@10.10.10.97*


It is giving an error, but we found a share *new-site* Let’s try smbclient


```
smbclient \\10.10.10.97\new-site -U tyler
```


*smbclient \\10.10.10.97\new-site -U tyler*


We saw port 8080 have IIS configured We can try to run for reverse shell,


- and upload the [nc.exe](https://github.com/int0x33/nc.exe/blob/master/nc.exe) to the server.

- upload rev.php to the server.

*rev.phpput rev.php*


Start nc listener and Load the [http://10.10.10.97:8808/rev.php](http://10.10.10.97:8808/rev.php)


```
nc -nlvp 1234
```


we have the shell


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Found the user.txt

*user.txt*

## Priv Esc


We found bash.exe and wsl.exe


```
where /R c:\windows bash.exe
where /R c:\windows wsl.exe
```


Let’s run the bash.exe and spawn tty


```
python3 -c 'import pty; pty.spawn("/bin/bash")'
```


We found admin cred

*admin cred*


we can connect via smbclient

*smbclient*


Let’s try to get a shell via Psexec

*psexec*


and we have a shell Found root.txt

*root.txt*

---

*Originally published on [Medium](https://infosecwriteups.com/htb-secnotes-a32b5946df21). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
