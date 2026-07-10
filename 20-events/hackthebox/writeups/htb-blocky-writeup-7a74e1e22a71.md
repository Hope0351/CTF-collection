# 🌐 HTB: Sau (Writeup)

> **Original Source:** [HTB: Sau (Writeup)](https://medium.com/@priscillabigail/htb-blocky-writeup-7a74e1e22a71)
> **Platform:** medium.com | **Category:** `WEB` | **Event:** HackTheBox CTF

---

## 📝 Full Writeup

**HTB: Sau (Writeup)**[![Priscilla Abigail](https://web.archive.org/web/20251126142424im_/https://miro.medium.com/v2/resize:fill:64:64/1*BQhn29Z3Fr_1H_ryAjkuVg.jpeg)

](/web/20251126142424/https://medium.com/@priscillabigail?source=post_page---byline--7a74e1e22a71---------------------------------------)

[Priscilla Abigail](/web/20251126142424/https://medium.com/@priscillabigail?source=post_page---byline--7a74e1e22a71---------------------------------------)

·
Apr 26, 2025

[

](/web/20251126142424/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F7a74e1e22a71&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40priscillabigail%2Fhtb-blocky-writeup-7a74e1e22a71&user=Priscilla+Abigail&userId=ec4afd43b814&source=---header_actions--7a74e1e22a71---------------------clap_footer------------------)

--



Sau is a Linux machine on Hack The Box that provides a great opportunity to practice SSRF (Server-Side Request Forgery) and Unauthenticated Command Injection vulnerabilities. In this writeup, I’ll walk through the steps I took and how I escalated my privileges to root.

> 
***OWASP Correlation***

*WSTG-INPV-12: Testing for Server-Side Request Forgery*

*WSTG-INPV-11: Testing for Command Injection*

I start with Nmap which shows 3 open ports. Port 22 is typically reserved for remote login via SSH, and 80 is standard for web services. Port 55555 stood out, likely a non-standard web or API service.

Browsing to [http://10.10.10.224](https://web.archive.org/web/20251126142424/http://10.10.10.224/) returned nothing useful. However, navigating to [http://10.10.10.224:55555](https://web.archive.org/web/20251126142424/http://10.10.10.224:55555/) revealed a web application named Request Baskets.

This app lets users create “baskets” to capture HTTP requests. When I created a new basket, I was given a token, and opening the basket revealed a UI to view incoming requests.

After identifying the request-baskets version, I searched for known vulnerabilities and found this CVE, This version allowed unauthenticated users to force the server to make HTTP requests to internal services.

Used the exploit from [https://github.com/entr0pie/CVE-2023-27163](https://web.archive.org/web/20251126142424/https://github.com/entr0pie/CVE-2023-27163).

Visiting the newly created bucket revealed this page, which has a suspiciously obvious version clue for Mailtrail.

Which leads me to find this RCE vulnerability.

Using that exploit, it triggered a reverse shell back to my machine using Netcat.

I got a shell as user Puma** **and retrieved the first flag.

Upgrading shell and looking for sudo permissions.

Followed this article to spawn a shell in the pager.

This command opens a pager (like less or more), which can be escaped by using !sh to spawn a root shell.

Now I am able to retrieve the root flag.

**Final Thoughts 🙇🏻‍♀️💬**

I learned how to chain simple vulnerabilities to gain full access to a machine. This box taught me the importance of checking all open ports, using SSRF to reach internal services, and identifying known exploits based on software versions. I also learned the importance of checking sudo permissions after getting a shell, which helped me escalate to root.

---

*📖 Originally published on [Medium](https://medium.com/@priscillabigail/htb-blocky-writeup-7a74e1e22a71). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
