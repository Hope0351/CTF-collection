# :game_die: H7CTF Boot2Root Challenge Experience.

> **Original Source:** [H7CTF Boot2Root Challenge Experience.](https://infosecwriteups.com/h7ctf-boot2root-challenge-experience-34bc8a939f8a)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# H7CTF Boot2Root Challenge Experience.


In this engagement I was working in a CTF category called boot2root the description of the challenge is as follows:


megatron wanted to share the files he hacked from U.S government to his co-bots. He deployed a password mechanism for sharing the files. He took a word from a small SMB article in Wikipedia, reversed it and put it in our CTF Flag format. Seems like he loved our CTF 🥹🥹


as always we start by scanning the target for open ports then follow that with Enumeration and exploitation if we find any juicy information for initial access.

>

INFORMATION GATHERING :


Scanning with nmap gives us this results :


I can see 3 open ports, 22 SSH, 139 and 445 , SSH is closed for now so lets skip this vector.

>

22 SSH


139 netbios-ssn


445 SMB


then my immediate guess when I see port 445 and 139 open is poking over SMB, SMB is just like any language, computer programmers have created different SMB dialects use for different purposes. For example, Common Internet File System (CIFS) is a specific implementation of SMB that enables file sharing. Many people mistake CIFS as a different protocol than SMB, when in fact they use the same basic architecture.


my go tool in SMB is metasploit and the auxiliary module SMB Version as a starter to get an idea of which version is the current SMB.


*Scanning with auxiliary scanner smb version*


next I try the next auxiliary module which is smb login , to bruteforce logins, maybe we will have luck and find easy juicy information.


our tool that will be used is smb login to bruteforce smb for logins against a password list


BINGO! we found some credentials ;


root:123456
admin: 123456
test: 123456


*Found credentials.*


I found these credentials but they seem to be false, as in me rolling down the rabbit hole, so I decided to get myself back up and get out of the rabbit hole I’m falling into.


After initiating a full nmap scan I found the following results:


## Get Cyb0rgBytes’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


new ports were found:


```
Scanned at 2024–09–26 16:26:19 EDT for 238s
Not shown: 65529 filtered tcp ports (no-response)
PORT STATE SERVICE REASON VERSION
22/tcp closed ssh reset ttl 63
139/tcp open netbios-ssn syn-ack ttl 63 Samba smbd 4.6.2
445/tcp open netbios-ssn syn-ack ttl 63 Samba smbd 4.6.2
44444/tcp closed cognex-dataman reset ttl 63
54321/tcp open ssh syn-ack ttl 63 OpenSSH 8.2p1 Ubuntu 4ubuntu0.11 (Ubuntu Linux; protocol 2.0)
```
```


some findings worth mentioning using enum4linux :


```

Looking up status of 10.10.255.210
H7TEX <00> - B <ACTIVE> Workstation Service
H7TEX <03> - B <ACTIVE> Messenger Service
H7TEX <20> - B <ACTIVE> File Server Service
..__MSBROWSE__. <01> - <GROUP> B <ACTIVE> Master Browser
WORKGROUP <00> - <GROUP> B <ACTIVE> Domain/Workgroup Name
WORKGROUP <1d> - B <ACTIVE> Master Browser
WORKGROUP <1e> - <GROUP> B <ACTIVE> Browser Service Elections

```


next I found some interesting info using nbtscan tool :


*NBTSCAN*


Something called KENOBI and H7TEX looks like a domain.


more information with crackmapexec :


*Crackmapexec results.*


```
```
┌──(root💀CSEC)-[/home/cyborgbytes/Documents/CTFEvents/H7CTF]
└─# crackmapexec smb 10.10.255.210 --users -u admin -p 123456
[*] First time use detected
[*] Creating home directory structure
[*] Creating default workspace
[*] Initializing RDP protocol database
[*] Initializing SMB protocol database
[*] Initializing MSSQL protocol database
[*] Initializing FTP protocol database
[*] Initializing SSH protocol database
[*] Initializing LDAP protocol database
[*] Initializing WINRM protocol database
[*] Copying default configuration file
[*] Generating SSL certificate
SMB 10.10.255.210 445 H7TEX [*] Windows 6.1 Build 0 (name:H7TEX) (domain:H7TEX) (signing:False) (SMBv1:False)
SMB 10.10.255.210 445 H7TEX [+] H7TEX\admin:123456
SMB 10.10.255.210 445 H7TEX [-] Error enumerating domain users using dc ip 10.10.255.210: socket connection error while opening: [Errno 110] Connection timed out
SMB 10.10.255.210 445 H7TEX [*] Trying with SAMRPC protocol
SMB 10.10.255.210 445 H7TEX [+] Enumerated domain user(s)
SMB 10.10.255.210 445 H7TEX H7TEX\megatron
SMB 10.10.255.210 445 H7TEX [+] Enumerated domain user(s)
SMB 10.10.255.210 445 H7TEX H7TEX\megatron


```
```


```
```
S-1-22-1-1000 Unix User\megatron (Local User)
S-1-22-1-1001 Unix User\optimus (Local User)
S-1-22-1-1002 Unix User\h7tex (Local User)

```
```


>

cewl -w wordlist.txt -d 1-m 5


after running the bruteforce again I found some juicy information a credential for a user called optimus:


*Finding the Password.*


H7CTF{swodniW}


after brute forcing using smblogin we are able to find credential for megatron user, later I stumbled across a text file which has a private key , which got us initial access on the box :


*SMBmap results.*


after using the credentials with smbclient we can list the shares :


```
```
smbclient //10.10.169.17/ILoveYou -U megatron%H7CTF{noitaugibmasiD}
```
```


Credits to my teammate TroyLynx for finding the password and being more patient than me in cracking it, I spent a reasonable time trying to crack it with no use.


With the password I was able to get initial foothold via SSH, and retrieve the User Flag, unfortunately the CTF finished before I managed to get the root flag.


Thanks everyone for reading my article, if you like what you’re reading pleases clap and share it so it reach more people, thanks alot and cheers!


---

*Originally published on [Medium](https://infosecwriteups.com/h7ctf-boot2root-challenge-experience-34bc8a939f8a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
