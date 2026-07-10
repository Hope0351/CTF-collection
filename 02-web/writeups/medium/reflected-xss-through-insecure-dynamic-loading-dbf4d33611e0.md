# :globe_with_meridians: Reflected XSS Through Insecure Dynamic Loading

> **Original Source:** [Reflected XSS Through Insecure Dynamic Loading](https://infosecwriteups.com/reflected-xss-through-insecure-dynamic-loading-dbf4d33611e0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Reflected XSS Through Insecure Dynamic Loading


## Finding A Unique and Complex Payload To Load Remote Scripts


STOP! Before reading this article, I encourage you to try this XSS Challenge for yourself. I’ve incorporated the core elements of the vulnerability into a simple static page here: [https://d11dkd80d59ds1.cloudfront.net/](https://d11dkd80d59ds1.cloudfront.net/). While this article will walk you through the full exploit, I’ll warn you that it is far more complicated than the typical injection and as such the solution might make more sense if you take the time to try it yourself.


*Try this XSS Challenge for yourself before reading this article. While this article will walk you through the full exploit, I’ll warn you that it is far more complicated than the typical injection and as such the solution might make more sense if you take the time to try it yourself.*


Recently while hunting a private program on [Bugcrowd](https://bugcrowd.com/gregaai) I discovered both the user’s email address and security questions could be modified WITHOUT password verification or any other security checks in place. This combination would allow an attacker to successfully perform an account takeover; however, I needed a remote exploit to justify a submission.


For those new to or unfamiliar with Bug Bounty hunting, vulnerabilities in and of themselves do not translate to accepted submissions. In this case, I’d discovered a P5 Lack of Password Confirmation — Change Email Address¹. P5’s are the lowest severity level (with P1 being the highest) and one that typically does not receive a bounty. To truly demonstrate an impact you need a working, and importantly remote,exploit, but as it stood, an…

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-through-insecure-dynamic-loading-dbf4d33611e0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
