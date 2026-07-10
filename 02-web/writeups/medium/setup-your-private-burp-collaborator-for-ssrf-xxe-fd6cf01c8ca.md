# :globe_with_meridians: Setup Your Private Burp Collaborator for SSRF/XXE

> **Original Source:** [Setup Your Private Burp Collaborator for SSRF/XXE](https://infosecwriteups.com/setup-your-private-burp-collaborator-for-ssrf-xxe-fd6cf01c8ca)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Setup Your Private Burp Collaborator for SSRF/XXE


*Photo by [Hacker Noon](https://unsplash.com/@hackernoon?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Hello Security Researchers & Hackers
In this article I will talk about how you can get your Own Private Collaborator without the needs to buy a new domain or use any other tool


Pr-requirements
All you need is Pro / VPS 5$ is enough , you can get yourself one from DigitalOcean with 100$ Balance for 2 Months [Here](https://m.do.co/c/2bef12838104), We will also need Wireshark you can download it from [Here](https://www.wireshark.org/download.html)


Open Burp-suite and go to Project-Options and Enable Poll over unencrypted HTTP and open Wireshark as well


Before clicking Run Health Check check your connection devise in Wireshark (WIFI / Ethernet) It should look like the one that has spikes which means traffic on for my case I used Ethernet so I click on it


Now go back to burp and Run the Health check and wait a little bit
Once it’s done it will look like this

---

*Originally published on [Medium](https://infosecwriteups.com/setup-your-private-burp-collaborator-for-ssrf-xxe-fd6cf01c8ca). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
