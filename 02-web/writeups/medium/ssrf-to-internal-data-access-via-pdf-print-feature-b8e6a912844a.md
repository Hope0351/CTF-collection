# :globe_with_meridians: SSRF To Internal Data Access Via PDF Print Feature

> **Original Source:** [SSRF To Internal Data Access Via PDF Print Feature](https://infosecwriteups.com/ssrf-to-internal-data-access-via-pdf-print-feature-b8e6a912844a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF To Internal Data Access Via PDF Print Feature


Introduction: Server-Side Request Forgery (SSRF) is a web security vulnerability that occurs when an attacker manipulates a server into making unauthorized HTTP or other protocol-based requests to unintended destinations. This exploit typically arises when an application fetches remote resources based on user-supplied input without adequately validating or sanitizing the input.

### Hunting SSRF in a Financial Application


Most of the time, I focus on a single program when hunting for vulnerabilities. Sticking to one program allows me to understand its core functionalities and business logic more thoroughly. In this case, I was working on a private program related to finance. This application used different internal domains for handling financial data, fetching the data via iframes.


Initially, I overlooked testing for CSRF or other bugs because I assumed the requests were encrypted. However, after digging deeper, I realized that the “encrypted” requests were merely Base64-encoded! That discovery led to the reporting of a few CSRF vulnerabilities and XSS bugs, even though some of them were on out-of-scope domains. These domains, however, directly impacted the main scope host and were used in the web application.

## The SSRF Discovery


While exploring the application further, I found a Print functionality. This feature converts the page into HTML, encodes it in Base64, and sends it for printing. This reminded me of SSRF techniques from NahamSec’s and other security researcher write-ups and videos, especially around PDF conversion features, which often have SSRF potential.


I started experimenting with payloads to check for SSRF. Initially, I used commands aimed at AWS metadata endpoints and Linux file paths, such as:


```
"><iframe src="http://169.254.169.254/latest/meta-data" height=2500 width=500>
"><iframe src="cat /etc/passwd" height=2500 width=500>
```


However, I faced issues with the height and width parameters in the iframe, which distorted the output. After some trial and error, I figured out the correct structure for these parameters.


## Get Bishal Shrestha’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Later, I identified that the backend server was running Windows OS. This discovery shifted my focus to testing Windows-specific directories. I used payloads like:


```
"><iframe src="C:\Windows\debug\NetSetup.LOG" height=2500 width=500>
"><iframe/src="C:/Windows/win.ini">
```


I then encoded this payload into Base64:


```
Ij48aWZyYW1lL3NyYz0iQzpcV2luZG93c1xkZWJ1Z1xOZXRTZXR1cC5MT0ciIGhlaWdodD0yNTAwIHdpZHRoPTUwMD4=
Ij48aWZyYW1lL3NyYz0iQzpcV2luZG93c1xkZWJ1Z1xOZXRTZXR1cC5MT0ciIGhlaWdodD01MDAgd2lkdGg9NzAwPg==
```


This payload was successfully executed at the following endpoint:


```
https://aa.REDACTED.com/REDACTED/Print/PrintToPDF
```


*HTTP Request with encoded payload*


## Hit-and-Trial for Exploitation:


With this breakthrough, I tested various other payloads to explore the backend further. Each time, I adjusted the parameters and encoded the payload in Base64 to ensure it executed properly. Eventually, I successfully retrieved sensitive data and confirmed the SSRF vulnerability.


This experience underscored the importance of persistence and creative thinking in bug hunting, as even initially overlooked features can lead to significant discoveries when explored thoroughly.


*Response from Program owner behind reducing the priority.*


Initially, the issue was triaged as a P1 by one of Bugcrowd’s Application Security Engineers (ASE) under the `server_side_injection.file_inclusion.local` category in the VRT. However, the program owner later reclassified it as a P2, providing additional explanation for the downgrade.


I always feel that until we discover these bugs ourselves, it doesn’t feel real. :D This was my first SSRF bug ever! Thank you for taking the time to read this write-up. Keep learning and happy hacking!

## Timeline:


*Reported →*(22 Mar 2024 15:55:11 UTC)


*Triaged →*(27 Mar 2024 06:10:41 UTC)


*Resolved →(*17 May 2024 17:58:02 UTC)

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-to-internal-data-access-via-pdf-print-feature-b8e6a912844a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
