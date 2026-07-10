# :game_die: Htb Business Ctf 2024 Submerged Fullpwn Write Up 6Fb5Be96540D

> **Original Source:** [Htb Business Ctf 2024 Submerged Fullpwn Write Up 6Fb5Be96540D](https://infosecwriteups.com/htb-business-ctf-2024-submerged-fullpwn-write-up-6fb5be96540d)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2024

---

## 🔎 Recon


We kick off our recon with a full Nmap scan of all 65,535 TCP ports.


```
$ sudo nmap -p- -v --open -n -T4 submerged.htb -oN nmap_submerged_allports.nmap

--SNIP--

PORT STATE SERVICE
80/tcp open http

Nmap done: 1 IP address (1 host up) scanned in 90.04 seconds
```


- `-p-`: Scans all 65535 ports.

- `-v`: Increases verbosity, providing more detailed output during the scan.

- `--open`: Only shows open ports in the results, filtering out closed and filtered ports.

- `-n`: Disables DNS resolution, speeding up the scan by not resolving IP addresses to hostnames.

- `-T4`: Sets the timing template to level 4, making the scan faster by reducing wait times between probes.

- `-oN`: Outputs the results in normal format to the specified file.

>

💡 Tip: The `-v` Nmap option is particularly useful when scanning all ports with `-p-`, as it allows you to see open ports as they are found. This way, you can start working with the identified open ports immediately, without waiting for the entire scan to complete.


Only TCP port 80 (HTTP) was open. Let’s explore this service further and run a more detailed Nmap scan.


```
$ nmap -A submerged.htb -oN submerged_http_port.nmap

PORT STATE SERVICE VERSION
80/tcp open http nginx 1.18.0 (Ubuntu)
|_http-title: Submerged Blog
|_http-server-header: nginx/1.18.0 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Nmap done: 1 IP address (1 host up) scanned in 16.29 seconds
```


We’ve identified a blog titled “*Submerged *” running on the port.
The web server is running nginx 1.18.0 on an Ubuntu Linux box.


It’s now time to browse to the website and inspect it.


*The Submerged Blog’s main page*


Here’s my checklist for performing basic recon on this website.


🌟 Browse all the pages and links on the website


This will help you gain a better understanding of the website’s layout and different areas.


- Home: (Nothing interesting except for a link at the bottom. We will revisit this in a moment when we dig deeper.

- About: nothing interesting to see here.

- Contact: potentially interesting. A contact form which offers us input opportunities. However, the form input fields are blocked. We will revisit this after some quick recon activities.


🌟 Identify what technologies are supported and used by the website


```
$ whatweb http://submerged.htb | sed 's/,/\n -/g
```


*WhatWeb: identify technologies supported by the website*🌟 Check for any *robots.txt* file on the website


```
$ curl http://submerged.htb/robots.txt
<html>
<head><title>404 Not Found</title></head>
```


🌟 View and inspect the web page’s HTML source code


This can reveal a lot about technologies used by the website, hidden comments, hidden elements etc. It is always worth inspecting.


Browse through the HTML source code for any interesting JavaScript files, internal and external URLs, or web directories you might want to manually explore.


To save you time, nothing particularly interesting was found here except for the Contact form, which we’ll delve into in the upcoming sections.


🌟 Enumerate all unique URLs on the website and sort them into a list


Lynx is a text-based browser which allows you to browse websites from your console. It has handy features to save you time when manually browsing through a site.


```
$ sudo apt update
$ sudo apt install lynx

$ lynx -dump -listonly http://submerged.htb | awk '/http/{print $2}' | sort -u

http://spip.submerged.htb/
http://submerged.htb/about.html
http://submerged.htb/contact.html
http://submerged.htb/index.html
http://submerged.htb/post_1.html
http://submerged.htb/post_2.html
http://submerged.htb/post_3.html
http://submerged.htb/post_4.html
http://submerged.htb/post_5.html
http://submerged.htb/post_6.html
```


>

:Note: We’ve discovered a subdomain of submerged.htb or potentially a Virtual Host (vhost). Save ‘[http://spip.submerged.htb](http://spip.submerged.htb)' in your notes for now.


Browse all the pages and links you found. The only notable pages that I wanted to revisit were the “SPIP” virtual host and the “Contact” page.


🌟 Explore the Contact form


Let’s start with the Contact form. I’ve noticed immediately that the form has all input fields disabled.


*The contact form has input disabled*


This is a trivial control which can easily be bypassed using a web proxy tool such as Burp or using the browser’s Developer or Inspector tools.


*Enable the form input fields using Dev Tools (Inspector)*


Time to play with the form and generate some traffic to be intercepted by Burp.


*Manipulating the disabled form input fields using Burp*


I spent some time on this form trying to identify any opportunities for injections or executing PHP commands. Nothing worked, so I set this aside for now.


🌟 Run web directory enumeration to find interesting web folders


```
$ gobuster dir -u http://submerged.htb/ -w /usr/share/wordlists/dirb/big.txt
===============================================================
Gobuster v3.6
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@firefart)
===============================================================
[+] Url: http://submerged.htb/
[+] Method: GET
[+] Threads: 10
[+] Wordlist: /usr/share/wordlists/dirb/big.txt
[+] Negative Status codes: 404
[+] User Agent: gobuster/3.6
[+] Timeout: 10s
===============================================================
Starting gobuster in directory enumeration mode
===============================================================
/css (Status: 301) [Size: 178] [--> http://submerged.htb/css/]
/img (Status: 301) [Size: 178] [--> http://submerged.htb/img/]
/js (Status: 301) [Size: 178] [--> http://submerged.htb/js/]
Progress: 20469 / 20470 (100.00%)
===============================================================
Finished
===============================================================
```


Having browsed them, nothing of interest was found. Let’s turn our attention to the web server itself.


🌟 Run Nikto web server vulnerability scanner


Now we know Nginx is the web server running, let’s see if we can identify low-hanging fruits or Nginx vulnerabilities we can use.


```
$ nikto -h http://submerged.htb
- Nikto v2.5.0

+ Target IP: 10.129.231.33
+ Target Hostname: submerged.htb
+ Target Port: 80
+ Start Time: 2024-05-23 00:46:21 (GMT1)

+ Server: nginx/1.18.0 (Ubuntu)
+ /: The anti-clickjacking X-Frame-Options header is not present. See: https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Frame-Options
+ /: The X-Content-Type-Options header is not set. This could allow the user agent to render the content of the site in a different fashion to the MIME type. See: https://www.netsparker.com/web-vulnerability-scanner/vulnerabilities/missing-content-type-header/
+ No CGI Directories found (use '-C all' to force check all possible dirs)
+ nginx/1.18.0 appears to be outdated (current is at least 1.20.1).
+ /#wp-config.php#: #wp-config.php# file found. This file contains the credentials.
+ 7962 requests: 0 error(s) and 4 item(s) reported on remote host
+ End Time: 2024-05-23 00:49:05 (GMT1) (164 seconds)

+ 1 host(s) tested
```


>

Note: Remember we had an additional web page that we have not yet explored? The URL we enumerated earlier “*http://spip.submerged.htb*” looks very interesting. In previous CTF events, such findings were rarely coincidental.


It could signal a hint that we need to explore beyond this basic Submerged blog.


🌟 Add an entry to our `/etc/hosts` file for this vhost using the same IP


```
$ sudo sh -c "echo '\n10.129.231.33 spip.submerged.htb spip' >> /etc/hosts"
```


Verify the resolution works and that we can reach the IP address still.

>

Note: Always verify you can reach your target before launching attacks to avoid frustration from changes like instance stops, IP changes, or VPN issues.


```
$ ping spip.submerged.htb -c 1

PING spip.submerged.htb (10.129.231.33) 56(84) bytes of data.
64 bytes from submerged.htb (10.129.231.33): icmp_seq=1 ttl=127 time=37.3 msWe’ll carry out some of the previous checks as before. For the sake or brevity, I will list only the relevant findings and not re-run the checklist above.
```


🌟 Check out the website loads in your browser and inspect it further


*SPIP Home page*🌟 Enumerate all links on the website


```
$ lynx -dump -listonly http://spip.submerged.htb | awk '/http/{print $2}' | sort -u

http://spip.submerged.htb/spip.php?page=backend
http://spip.submerged.htb/spip.php?page=contact
http://spip.submerged.htb/spip.php?page=login&url=./
http://spip.submerged.htb/spip.php?page=plan
https://www.spip.net/
```


🌟 Identify technologies supported


```
$ whatweb http://spip.submerged.htb | sed 's/,/\n -/g'
```


*WhatWeb: technologies supported by the SPIP website*🌟 Web directory enumeration (brute forcing)


```
$ ffuf -u http://spip.submerged.htb/FUZZ -w /usr/share/wordlists/dirb/big.txt

________________________________________________

config [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 18ms]
ecrire [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 17ms]
local [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 24ms]
prive [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 16ms]
squelettes-dist [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 14ms]
tmp [Status: 301, Size: 178, Words: 6, Lines: 8, Duration: 15ms]

:: Progress: [20469/20469] :: Job [1/1] :: 1639 req/sec :: Duration: [0:00:10] :: Errors: 0 ::
```


🌟 Identify the CMS in use


The SPIP website we landed on looks like a CMS web application. Browse to [www.spip.net](https://www.spip.net) to gain more information and a better understanding.


*The official page for the SPIP CMS project*🌟 Establish the version number of the CMS


We can check this in multiple ways. It’s useful to know several methods, as they might help with other CMSs where one approach works and another doesn’t.


- Inspecting the source code:

*Identify the SPIP CMS version number through viewing the source code*


- Enumerating by sending a basic GET request:


```
$ curl -v http://spip.submerged.htb

* Host spip.submerged.htb:80 was resolved.
* IPv6: (none)
* IPv4: 10.129.231.33
* Trying 10.129.231.33:80...
* Connected to spip.submerged.htb (10.129.231.33) port 80
> GET / HTTP/1.1
> Host: spip.submerged.htb
> User-Agent: curl/8.7.1
> Accept: */*
>
* Request completely sent off
< HTTP/1.1 200 OK
< Server: nginx/1.18.0 (Ubuntu)
< Date: Thu, 23 May 2024 13:06:38 GMT
< Content-Type: text/html; charset=utf-8
< Transfer-Encoding: chunked
< Connection: keep-alive
< Vary: Cookie, Accept-Encoding
< Composed-By: SPIP 4.0.0 @ www.spip.net + http://spip.submerged.htb/local/config.txt
< X-Spip-Cache: 86400
< Last-Modified: Thu, 23 May 2024 13:06:38 GMT
```


- Enumerating using SPIPScan:


We can use [SPIPScan](https://github.com/PaulSec/SPIPScan), a tool designed to enumerate SPIP CMS.

>

Note: SPIScan is over 10 years old, unmaintained and still relies on Python2.


```
$ wget https://raw.githubusercontent.com/PaulSec/SPIPScan/master/spipscan.py
```


You can experiment with some of the options such as `--plugins` , `--themes` or `--version`.


```
$ python2 spipscan.py --website=http://spip.submerged.htb --plugins
/usr/share/offsec-awae-wheels/pyOpenSSL-19.1.0-py2.py3-none-any.whl/OpenSSL/crypto.py:12: CryptographyDeprecationWarning: Python 2 is no longer supported by the Python core team. Support for it is now deprecated in cryptography, and will be removed in the next release.
[!] Version (in Headers) is: 4.0.0
[!] Plugin folder is: plugins-dist/
[-] Access forbidden on folder.
```


Let’s scan for some sensitive folders known to exist within SPIP CMS.


```
$ python2 spipscan.py --website=http://spip.submerged.htb --sensitive_folders --verbose
/usr/share/offsec-awae-wheels/pyOpenSSL-19.1.0-py2.py3-none-any.whl/OpenSSL/crypto.py:12: CryptographyDeprecationWarning: Python 2 is no longer supported by the Python core team. Support for it is now deprecated in cryptography, and will be removed in the next release.
Application is located here: http://spip.submerged.htb/
[-] Access forbidden on folder/file: config/
[-] Access forbidden on folder/file: IMG/
[-] Access forbidden on folder/file: local/
[-] Access forbidden on folder/file: prive/
[-] Folder/File config/ecran_securite.php might be interesting
```


At this point, we know we are dealing with SPIP CMS version 4.0.0,which is not the latest version.


We also know we have some default sensitive folders we might want to explore next to see if it exposes its configuration or any stored credentials during installation or for database connectivity.


🌟 Explore the website using your browser


In this step, I typically prefer to route the traffic through Burp while browsing the site manually. You never know what you might discover in the traffic flowing through Burp that you can’t see with the website’s UI.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-business-ctf-2024-submerged-fullpwn-write-up-6fb5be96540d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
