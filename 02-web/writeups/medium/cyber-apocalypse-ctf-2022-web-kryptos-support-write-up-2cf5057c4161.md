# :globe_with_meridians: Cyber Apocalypse CTF 2022 — Web — Kryptos Support Write-up

> **Original Source:** [Cyber Apocalypse CTF 2022 — Web — Kryptos Support Write-up](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-web-kryptos-support-write-up-2cf5057c4161)
> **Platform:** infosecwriteups.com | **Category:** `WEB` | **Year:** 2022

---

# Cyber Apocalypse CTF 2022 — Web — Kryptos Support Write-up


Prompt:


Kryptos Support
The secret vault used by the Longhir’s planet council, Kryptos, contains some very sensitive state secrets that Virgil and Ramona are after to prove the injustice performed by the commission. Ulysses performed an initial recon at their request and found a support portal for the vault. Can you take a look if you can infiltrate this system?


Start:


## Get zer0dac’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


It is a web challange and there is no source code to download and test it locally. So we will attack without any code review..


The website looks like that.


As it is ticket system, first thought was we are sending something to admin and he will review it. So it is good point to try XSS.


I’m opening a webhook website and writing my payload to check if admins click it.


And yes, I steal the cookie.. So from developer tools, we can set our cookie to login as admin..


We are seeing the tickets but they are not interactive, so I’m clickling to settings and there is a portal which helps to change our password.


When I examine it via burp, I saw there is only uid and password datas going to the server, so we can’t understand even we change the uid.. But as you know, almost all website admin has 1 or sometimes 0 for uid. So I’m changing it to 1..


And Boom.. There is an idor vulnerability which helps us to change admin’s password..


We are logging in as admin from /login path


and we are catching the flag of this challenge..


---

*Originally published on [Medium](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-web-kryptos-support-write-up-2cf5057c4161). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
