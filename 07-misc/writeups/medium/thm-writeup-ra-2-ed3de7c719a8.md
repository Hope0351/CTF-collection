# :game_die: Thm Writeup Ra 2 Ed3De7C719A8

---

## Web Enumeration

Based on the output from NMAP, I can see that port 443 is open and is hosting a website.

```
443/tcp open ssl/http Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
|_http-server-header: Microsoft-HTTPAPI/2.0
|_http-title: Not Found
| ssl-cert: Subject: commonName=fire.windcorp.thm
| Subject Alternative Name: DNS:fire.windcorp.thm, DNS:selfservice.windcorp.thm, DNS:selfservice.dev.windcorp.thm
| Issuer: commonName=fire.windcorp.thm
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2020-05-29T03:31:08
| Not valid after: 2028-05-29T03:41:03
| MD5: 804b dc39 5ce5 dd7b 19a5 851c 01d1 23ad
|_SHA-1: 37f4 e667 cef7 5cc4 47c9 d201 25cf 2b7d 20b2 c1f4
|_ssl-date: 2022-04-15T13:35:16+00:00; -1s from scanner time.
| tls-alpn:
|_ http/1.1
```

I can also see three hostnames called “*fire.windcorp.thm*” “*selfservice.windcorp.thm*” and “*selfservice.dev.windcorp.thm*”, which I added to my hosts file.

```
10.10.138.163 fire.windcorp.thm selfservice.windcorp.thm selfservice.dev.windcorp.thm
```

I started by visiting the “*fire.windcorp.thm*” website. On the main page, I can see a message from the management team stating that they no longer use unsafe IM software, a reference to the first [THM Ra machine](https://tryhackme.com/room/ra). They also mention that they are using certificates everywhere.

*Message from Management.*

I can also see a button that links to “*selfservice.windcorp.thm*”, which leads to a login popup.

*Self service login.*

Using Burpsuite, I can see that NTLM authorization is being used when users attempt to login through the portal but other than that, I see nothing else of interest.

*Burpsuite intercepts self-service login.*

I can see that there is a list of IT support staff on the main page. I can also see that the icons appear to change color, which may indicate when a user is active or not (i.e. green, amber, gray).

*IT Support Staff List.*

Viewing the page source for the main website, I can also see a list of potential user that exist on the target machine.

*Potential users.*

Moving further down the website, I can also see three additional employees.

*Employee Images.*

Opening these employee images in a new tab provides more potential usernames.

```
https://fire.windcorp.thm/img/Emilieje.jpg
https://fire.windcorp.thm/img/lilyleAndSparky.jpg
https://fire.windcorp.thm/img/kirkug.jpg
```

I continued my enumeration by performing a quick search for any hidden directories or webpages with FFuF tool.

```
ffuf -c -u [https://fire.windcorp.thm/FUZZ](https://fire.windcorp.thm/FUZZ) -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -e .php,.bak,.old -icimg [Status: 301, Size: 153, Words: 9, Lines: 2]
css [Status: 301, Size: 153, Words: 9, Lines: 2]
vendor [Status: 301, Size: 156, Words: 9, Lines: 2]
IMG [Status: 301, Size: 153, Words: 9, Lines: 2]
CSS [Status: 301, Size: 153, Words: 9, Lines: 2]
Img [Status: 301, Size: 153, Words: 9, Lines: 2]
powershell [Status: 302, Size: 165, Words: 6, Lines: 4]
```

I can see that there is a hidden Windows PowerShell Web Access page but I do not currently have any credentials to login.

*Windows PowerShell Web Access Page.*

Moving on, I started looking at “*selfservice.dev.windcorp.thm”. *Navigating to this address, I can see that the site is still under construction.

*Website under construction.*

I performed another search for any hidden directories or webpages with FFuF tool.

```
ffuf -c -u [https://selfservice.dev.windcorp.thm/FUZZ](https://selfservice.dev.windcorp.thm/FUZZ) -w /usr/share/wordlists/dirb/common.txt -e .php,.bak,.oldaspnet_client [Status: 301, Size: 174, Words: 9, Lines: 2]
backup [Status: 301, Size: 167, Words: 9, Lines: 2]
index.html [Status: 200, Size: 106, Words: 3, Lines: 6]
```

I can see that there is a hidden folder called “*backup*” that is accessible. Inside, I can see two files called “*cert.pfx*” and “*web.config*”.

*Backup folder contents.*

According to [HackTricks](https://book.hacktricks.xyz/cryptography/certificates):

>

The PKCS#12 or PFX format is a binary format for storing the server certificate, intermediate certificates, and the private key in one encryptable file. PFX files usually have extensions such as .pfx and .p12. PFX files are typically used on Windows machines to import and export certificates and private keys.

I can use openssl to view the certificate details, but unfortunately, it is password protected.

```
$ openssl pkcs12 -info -in cert.pfx Enter Import Password:
MAC: sha256, Iteration 2000
MAC length: 32, salt length: 20
Mac verify error: invalid password?
```

I decided to see if there was a way to extract the information stored inside this certificate. I found a tool called [crackpkcs12](https://github.com/crackpkcs12/crackpkcs12), which is a tool that can be used to crack PKCS#12 files passwords (extension .p12 or .pfx). I used this tool and the rockyou password list to perform a dictionary attack.

```
crackpkcs12 -d rockyou.txt cert.pfx
```

*Certificate password.*

This works and I retrieved the password used when creating the cert, however, I’m not too sure what I can do with this yet. I decided to perform some more enumeration of the available services.

---
