# :globe_with_meridians: Bug Bounty Bootcamp #37: SSRF in PDFs, Screenshots, and Bypassing Localhost Filters

> **Original Source:** [Bug Bounty Bootcamp #37: SSRF in PDFs, Screenshots, and Bypassing Localhost Filters](https://infosecwriteups.com/bug-bounty-bootcamp-37-ssrf-in-pdfs-screenshots-and-bypassing-localhost-filters-0607d263333f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bug Bounty Bootcamp #37: SSRF in PDFs, Screenshots, and Bypassing Localhost Filters


## You found a PDF generator that fetches URLs. The developer blocked `localhost` and `127.0.0.1`. Game over? Not even close. Learn the art of representing the same IP address in a dozen ways – and watch the firewall crumble.


[Free Link](https://amannsharmaa.medium.com/bug-bounty-bootcamp-37-ssrf-in-pdfs-screenshots-and-bypassing-localhost-filters-0607d263333f?sk=ec2611f12472d4a3ed559377ac887596)


Welcome back to the Bug Bounty Bootcamp. You’ve learned the basics of SSRF: confirm server-side requests with an external monitor, then probe localhost and internal networks. But what happens when the application *knows* about SSRF and blocks obvious addresses like `127.0.0.1` and `localhost`? That’s when the real fun begins. This lesson focuses on two advanced SSRF scenarios: PDF/screenshot generation services (where input is a URL that gets rendered into a document) and bypassing common localhost blacklists using alternative representations, custom domains, and clever services.

## The Hidden SSRF Goldmine: PDF, Screenshot, and Media Generation


Any feature that takes a URL and produces a server-side artifact — PDF, screenshot, video thumbnail, image — is a prime SSRF candidate. The course highlights:


- PDF generators: “Convert this webpage to PDF” tools.

- Screenshot services: “Capture a preview of this site” widgets.

---

*Originally published on [Medium](https://infosecwriteups.com/bug-bounty-bootcamp-37-ssrf-in-pdfs-screenshots-and-bypassing-localhost-filters-0607d263333f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
