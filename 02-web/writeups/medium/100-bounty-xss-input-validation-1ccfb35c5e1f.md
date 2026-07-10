# :globe_with_meridians: $100 bounty — XSS & Input Validation

> **Original Source:** [$100 bounty — XSS & Input Validation](https://infosecwriteups.com/100-bounty-xss-input-validation-1ccfb35c5e1f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $100 bounty — XSS & Input Validation


I discovered a private programme via google dork. It was a coding platform.


[Link](https://medium.com/bugbountywriteup/100-bounty-xss-input-validation-1ccfb35c5e1f?sk=afc6134ea6abfc6a23d88bdec3495a35) for friends


I found RCE and got a bounty for it. Soon after that I reported 2 XSS. But first of all I would like to say fck* taxes.

## #1 XSS :


After creating a profile there was a upload resume section.


I upload a pdf file from : [https://github.com/luigigubello/PayloadsAllThePDFs/tree/main/pdf-payloads](https://github.com/luigigubello/PayloadsAllThePDFs/tree/main/pdf-payloads)


and achieved XSS. Reported and got paid for it.


## #2 Input validation:


When I joined a challenge hosted on the website. In the team_name section I was restricted to 15 chars but when I used Burp I was able to inject fuck load of chars XD . Resulting in DoS

---

*Originally published on [Medium](https://infosecwriteups.com/100-bounty-xss-input-validation-1ccfb35c5e1f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
