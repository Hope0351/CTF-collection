# :game_die: OSCP Proving Grounds - Cockpit. Aight folks, here’s another write-up…

---

## Enumeration

Starting off with a nmap scan like always, we see there are three ports open; 22 (ssh), 80 (http), and 9090 (zeus-admin).

```
Nmap scan report for 192.168.178.10
Host is up, received user-set (0.24s latency).
Scanned at 2024-03-24 03:36:58 EDT for 944s
Not shown: 65532 closed tcp ports (reset)
PORT STATE SERVICE REASON VERSION
22/tcp open ssh syn-ack ttl 61 OpenSSH 8.2p1 Ubuntu 4ubuntu0.5 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 3072 98:4e:5d:e1:e6:97:29:6f:d9:e0:d4:82:a8:f6:4f:3f (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQCmPOfERLKCxx+ufQz7eRTNuEEkJ+GX/hKPNPpCWlTiTgegmjYoXQ7MA5ibTRoJ6vxpPEggzNszJKbBrSVAbRuT2sBg4o7ywiGUy7vsDBpObMrBMsdKuue3gpkaNF8DL2pB3v/XAxtavq1Mh4vz4yj99cc2pX1GhSjpQTWlsK8Rl9DmBKp7t0XxEWwq3juQ9JiN5yAttMrbTDjwMNxcipsYv0pMudDBE6g4gQyiZGwuUfBn+HirxnfRr7KkxmBaEpZgukXSJ7fXYgpQVgNP2cvd2sy/PYe0kL7lOfYwG/DSLWV917RPIdsPPQYr+rqrBL7XQA2Qll30Ms9iAX1m9S6pT/vkaw6JQCgDwFSwPXrknf627jCS7vQ8mh8UL07nPO7Hkko3fnHIcxyJggi/BoAAi3GseOl7vCZl28+waWlNdbR8gaiZhDR1rLvimcm3pg3nv9m+0qfVRIs9fxq97cOEFeXhaGHXvQL6LYGK14ZG+jVXtPavID6txymiBOUsj8M=
| 256 57:23:57:1f:fd:77:06:be:25:66:61:14:6d:ae:5e:98 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBAweAzke7+zPt3Untb06RlI4MEp+vsEJICUG+0GgPMp+vxOdxEhcsVY0VGyuC+plTRlqNi0zNv1Y0Jj0BYRMSUw=
| 256 c7:9b:aa:d5:a6:33:35:91:34:1e:ef:cf:61:a8:30:1c (ED25519)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIPJP5z2Scxa02tfhI1SClflg5QtVdhMImHwY7GugVtfY
80/tcp open http syn-ack ttl 61 Apache httpd 2.4.41 ((Ubuntu))
|_http-server-header: Apache/2.4.41 (Ubuntu)
|_http-title: blaze
| http-methods:
|_ Supported Methods: GET POST OPTIONS HEAD
9090/tcp open ssl/zeus-admin? syn-ack ttl 61
| ssl-cert: Subject: commonName=blaze/organizationName=d2737565435f491e97f49bb5b34ba02e
| Subject Alternative Name: IP Address:127.0.0.1, DNS:localhost
| Issuer: commonName=blaze/organizationName=d2737565435f491e97f49bb5b34ba02e
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2024-03-24T07:36:32
| Not valid after: 2124-02-29T07:36:32

...<SNIP>...
```

I won’t even bother with port 22 yet, I’ll start at port 80 and have a poke around to get a feel for what I’m working with.

Its a static webpage with no working links, you know what that means, oh yeah, its directory busting time.

From the results of the scan, there’s only really a couple of things that stand out to me, `login.php` and `db_config.php` the latter of which is empty.

```
200 GET 278l 506w 5366c http://192.168.178.10/css/index.css
200 GET 78l 321w 3349c http://192.168.178.10/
200 GET 29l 60w 477c http://192.168.178.10/css/type.css
200 GET 10l 28w 233c http://192.168.178.10/blocked.html
200 GET 65l 128w 1108c http://192.168.178.10/css/style.css
200 GET 18l 77w 1323c http://192.168.178.10/css/
200 GET 78l 321w 3349c http://192.168.178.10/index.html
200 GET 707l 4190w 598838c http://192.168.178.10/img/blaze.png
200 GET 16l 58w 935c http://192.168.178.10/img/
200 GET 29l 85w 913c http://192.168.178.10/js/index.js
200 GET 16l 60w 932c http://192.168.178.10/js/
200 GET 28l 63w 769c http://192.168.178.10/login.php
200 GET 0l 0w 0c http://192.168.178.10/db_config.php
```

Navigating to the login page, wouldn’t you expect it, we see a login page. There appears to be a hostname in the bottom left corner of the page so I added that to my hosts file before continuing just in case I would need it later. I tried the usual default credentials like admin:admin but to no avail so decided to try some SQLi login bypasses. The page, however, appears to be doing some form of regex filtering as the usual `'or 1=1-- -` payload redirects the user to the blocked.html page. The payload `'and 2=2-- -` worked just fine though.

If you get blocked here just keep trying as I find the blocking is very inconsistent, the ‘or 1=1’ payload worked just fine while I was writing this.

Anyway, once we bypass the login screen we see two usernames and two respective base64 encoded passwords. We can simply base64 decode the passwords with a tool such as [cyberchef](https://gchq.github.io/CyberChef/)or by using the command:

```
echo Y2FudHRvdWNoaGh0aGlzc0A0NTUxNTI= | base64 -d
```

From here we have a couple of credentials, they don’t work on ssh so lets see if they might work on the zeus-admin interface on port 9090 we found earlier. Using the credentials `james:canttouchhthiss@455152` we can enter the web interface. From here there are a number of options, but since this is a CTF the thing that catches my eye is the ‘Terminal’ button which gives us direct access to a shell on the system.

From here we have a bash shell through the web interface, and although you can absolutely do the rest of the box from here, I highly recommend using this opportunity to practice ways to get reverse shells because you never know if in the future you may need some obscure way to get a proper shell. What if this one was highly restricted for example?

---
