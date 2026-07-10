# :link: Critical | Vulnerabilities in DrayTek Vigor Routers| Over 700,000 Devices Exposed to Remote Exploits…

> **Original Source:** [Critical | Vulnerabilities in DrayTek Vigor Routers| Over 700,000 Devices Exposed to Remote Exploits…](https://infosecwriteups.com/critical-vulnerabilities-in-draytek-vigor-routers-over-700-000-devices-exposed-to-remote-exploits-2f3f731b50d9)
> **Platform:** infosecwriteups.com | **Category:** `BLOCKCHAIN`

---

# Critical Vulnerabilities in DrayTek Vigor Routers: Over 700,000 Devices Exposed to Remote Exploits -$$$$ Bounty


A series of critical vulnerabilities have been discovered in DrayTek Vigor routers, potentially affecting over 700,000 devices globally. These vulnerabilities include remote code execution (RCE), XSS, Information disclosure ,privilege escalation, and authentication bypass etc, which could allow attackers to take full control of the affected routers. Exploiting these flaws could lead to network breaches, data theft, and further attacks on connected systems.


Forescout’s analysis revealed that over 704,000 DrayTek routers have their Web UI exposed to the internet, creating a rich attack surface for malicious actors. The majority of these exposed instances are located in the U.S., followed by Vietnam, the Netherlands, Taiwan, and Australia.


“**CVE-2024–41592** addresses a buffer overflow vulnerability in the ‘GetCGI()’ function of the Web UI, which can lead to a denial-of-service (DoS) or remote code execution (RCE) when handling query string parameters.


Another critical vulnerability, **CVE-2024–41585 (CVSS score: 9.1),** involves an OS command injection flaw in the ‘recvCmd’ binary, used for communication between the host and guest operating systems.”

---

*Originally published on [Medium](https://infosecwriteups.com/critical-vulnerabilities-in-draytek-vigor-routers-over-700-000-devices-exposed-to-remote-exploits-2f3f731b50d9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of blockchain CTF writeups.*
