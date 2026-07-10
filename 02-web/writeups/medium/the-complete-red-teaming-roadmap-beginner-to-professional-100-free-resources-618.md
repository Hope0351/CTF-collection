# :globe_with_meridians: The Complete Red Teaming Roadmap Beginner To Professional 100 Free Resources 618

> **Original Source:** [The Complete Red Teaming Roadmap Beginner To Professional 100 Free Resources 618](https://infosecwriteups.com/the-complete-red-teaming-roadmap-beginner-to-professional-100-free-resources-6183e451ee4a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

When I started, I Googled “how to become a red teamer” and got overwhelmed.


Too many courses. Too many tools. No clear order. No one telling me what to learn *first*.


This roadmap fixes that.


I’ve laid out every skill you need — from absolute zero to professional Red Teamer — in the exact sequence that makes sense. Every resource is free. Every YouTube channel is verified. Every step builds on the last.


Bookmark this. Come back to it every week. Follow it in order.


Let’s go. 🔴

## What Is Red Teaming? (30 Second Explanation)


A Red Team is a group of ethical hackers hired by a company to attack their own systems — before real criminals do.


Unlike basic penetration testing (which tests specific systems), Red Teaming simulates a full real-world attack — from initial recon, to getting inside the network, to reaching the crown jewels (databases, domain controllers, executive emails) — without being detected.


Red Teamers think, act, and operate exactly like real threat actors.[[youtube](https://www.youtube.com/watch?v=OtcP8c4wZys)]​


Your end goal: Be able to conduct a full Red Team engagement — initial access, persistence, lateral movement, privilege escalation, and reporting — independently and professionally.

## The Complete Roadmap — 6 Phases


```
Phase 1: Foundations (2–3 months)
↓
Phase 2: Web Application Hacking (2–3 months)
↓
Phase 3: Network & Active Directory Attacks (3–4 months)
↓
Phase 4: Red Team Tradecraft (2–3 months)
↓
Phase 5: Practice Labs & CTFs (Ongoing)
↓
Phase 6: Certifications & Career (When Ready)
```


## ⚡ Phase 1 Foundations


*Duration: 2–3 months | Difficulty: Beginner*


Before you hack anything, you must understand how things work. Skipping this phase is the #1 mistake beginners make.

## 1.1 Linux Command Line


Every Red Team operation runs on Linux. You must be comfortable in the terminal.


What to Learn:


- File system navigation (`cd`, `ls`, `pwd`, `find`)

- File permissions (`chmod`, `chown`)

- Process management (`ps`, `kill`, `top`)

- Networking commands (`ifconfig`, `netstat`, `curl`, `wget`)

- Shell scripting basics (Bash)

- Text processing (`grep`, `awk`, `sed`)


📺 YouTube Resources:


## 1.2 Networking Fundamentals


Red Teamers live in networks. You must understand how data flows.


What to Learn:


- OSI Model (7 layers)

- TCP/IP, UDP, HTTP/S, DNS, FTP, SMB

- Subnetting and CIDR notation

- How firewalls and proxies work

- Wireshark — packet analysis basics

- Nmap — network scanning


📺 YouTube Resources:


## 1.3 Python & Bash Scripting


You will write tools, automate tasks, and build payloads. Scripting is non-negotiable.


What to Learn:


- Python: variables, loops, functions, file I/O, sockets, requests library

- Bash: loops, conditionals, piping, automation scripts

- Writing simple port scanners, recon tools, payload stagers


📺 YouTube Resources:


## 1.4 Set Up Your Hacking Lab


Before touching any real target, build a safe home lab.


What You Need (All Free):


- VirtualBox or VMware Workstation Player (free) — for running VMs

- Kali Linux — your primary attack OS (`kali.org` — free)

- Metasploitable 2 — intentionally vulnerable Linux VM (free)

- DVWA (Damn Vulnerable Web App) — web hacking practice (free)

- Windows Server 2019 Eval — for Active Directory lab (180-day free trial from Microsoft)


📺 YouTube Resources:


## 🌐 Phase 2 Web Application Hacking


*Duration: 2–3 months | Difficulty: Beginner–Intermediate*


Web apps are the most common attack surface in Red Team engagements. Master this before moving to networks.

## 2.1 OWASP Top 10


The bible of web security. Learn every vulnerability:


📺 YouTube Resources:


## 2.2 Burp Suite Mastery


Your most important tool as a web hacker. Learn every feature:


- Proxy — intercept and modify HTTP requests

- Repeater — manually test requests

- Intruder — brute force and fuzzing

- Scanner — automated vulnerability detection

- Decoder — encode/decode payloads

- Collaborator — out-of-band SSRF/XXE detection


📺 YouTube Resources:


🔗 Free Practice Platform:

>

*PortSwigger Web Security Academy — *`*portswigger.net/web-security*`*
100% free, best web hacking labs in the world, 250+ labs covering every vulnerability*


## 2.3 Key Web Vulnerabilities (Deep Dive)


Focus on these in order:


- XSS (Cross-Site Scripting) — DOM, Reflected, Stored

- SQL Injection — Error-based, Blind, Time-based

- SSRF — Basic, Cloud metadata, Blind SSRF

- IDOR — Object reference, UUID prediction

- CSRF — Token bypass, SameSite issues

- XXE — XML injection, file read, SSRF via XXE

- Command Injection — OS command execution

- SSTI — Template injection → RCE


📺 YouTube Resources:


## 🏢 Phase 3 Network & Active Directory Attacks


*Duration: 3–4 months | Difficulty: Intermediate*


This is the core of enterprise Red Teaming. 90% of real engagements involve Active Directory.​

## 3.1 Network Penetration Testing


What to Learn:


- Nmap advanced scanning (stealth scans, OS detection, scripts)

- Service enumeration (SMB, FTP, SSH, RDP, SMTP)

- Metasploit Framework — modules, payloads, sessions

- Password attacks (Hydra, CrackMapExec)

- Man-in-the-Middle attacks (Responder)


📺 YouTube Resources:


## 3.2 Active Directory Attacks


This is where real Red Team engagements happen. Corporate networks run on AD.


## Get Hacker MD’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


What to Learn:


- AD fundamentals (Domain, Forest, Trust, GPO, OU)

- Enumeration (BloodHound, ldapdomaindump, PowerView)

- Kerberoasting

- AS-REP Roasting

- Pass-the-Hash (PtH)

- Pass-the-Ticket (PtT)

- DCSync attack

- Golden Ticket / Silver Ticket

- Domain privilege escalation

- Forest trust abuse


📺 YouTube Resources:


ChannelVideo/PlaylistURLThe Cyber MentorPractical Active Directory Attacks`youtube.com/@TCMSecurityAcademy`John HammondAD Attack Walkthroughs`youtube.com/@_JohnHammond`IppSecAD-focused HTB machines`youtube.com/@ippsec`


🔗 Free AD Lab:

>

*GOAD (Game of Active Directory) — *`*github.com/Orange-Cyberdefense/GOAD*`*
Free vulnerable AD lab with multiple domains — best free AD practice environment*


## 3.3 Privilege Escalation


Getting initial access is step one. Getting SYSTEM/root is the goal.


What to Learn:


- Linux PrivEsc (SUID, sudo misconfigs, cron jobs, PATH hijacking)

- Windows PrivEsc (token impersonation, service misconfigs, UAC bypass, DLL hijacking)

- Tools: LinPEAS, WinPEAS, PowerUp


📺 YouTube Resources:


🔗 Free Practice:

>

`*tryhackme.com/room/linuxprivesc*``*tryhackme.com/room/windows10privesc*`


## 🔴 Phase 4 Red Team Tradecraft


*Duration: 2–3 months | Difficulty: Advanced*


This separates penetration testers from Red Teamers. It’s all about operating like a real threat actor — staying undetected.

## 4.1 MITRE ATT&CK Framework


Every Red Teamer must know this inside out.


MITRE ATT&CK is a knowledge base of real adversary tactics, techniques, and procedures (TTPs). It maps how real threat actors operate.14 Tactics to Learn:
Reconnaissance → Resource Development → Initial Access → Execution → Persistence → Privilege Escalation → Defense Evasion → Credential Access → Discovery → Lateral Movement → Collection → Command & Control → Exfiltration → Impact


🔗 Free Resource: `attack.mitre.org` — entire framework free online


📺 YouTube Resources:


ChannelVideoURLJohn HammondMITRE ATT&CK Explained`youtube.com/@_JohnHammond`The Cyber MentorRed Team Fundamentals`youtube.com/@TCMSecurityAcademy`

## 4.2 Initial Access Techniques


How Red Teamers get inside a target:


- Phishing — spear phishing emails, HTML smuggling

- Credential stuffing — breached credential reuse

- Exposed services — VPN, RDP, Citrix exploits

- Supply chain attacks — compromised third-party software

- Physical intrusion — USB drops, badge cloning


📺 YouTube Resources:


## 4.3 Command & Control (C2)


After getting inside, you need a way to communicate with your implant covertly.


What to Learn:


- C2 framework concepts (beacons, listeners, agents)

- Havoc C2 (free, modern) — `github.com/HavocFramework/Havoc`

- Sliver C2 (free) — `github.com/BishopFox/sliver`

- Metasploit Meterpreter — basic C2 (free)

- HTTP/S, DNS, and SMB C2 channels

- Sleep timers, jitter, OPSEC considerations


📺 YouTube Resources:


## 4.4 Defense Evasion & OPSEC


The difference between a Red Teamer and a script kiddie — staying hidden.


What to Learn:


- AV/EDR evasion — payload obfuscation, encryption

- AMSI bypass (Windows Antimalware Scan Interface)

- Living-off-the-land (LOLBins) — using built-in OS tools

- Process injection and hollowing

- Timestomping and log clearing

- Traffic blending (C2 over legit cloud services)


📺 YouTube Resources:


ChannelVideo/PlaylistURLThe Cyber MentorMalware Development Intro`youtube.com/@TCMSecurityAcademy`John HammondAV Evasion Techniques`youtube.com/@_JohnHammond`Sektor7Malware Development Free Intro`youtube.com/@reenz0h`


## 🏋️ Phase 5 Practice Labs & CTFs


*Duration: Ongoing (Parallel with all phases)*


Reading and watching is not enough. You must practice hands-on every week.

## Free Practice Platforms


## TryHackMe Learning Paths (Free)


Follow in this exact order:


- Pre-Security Path → Networking + Linux basics

- Jr Penetration Tester Path → Web + network basics

- Red Teaming Path → Full Red Team methodology

- Offensive Pentesting Path → Advanced offensive skills

## Top YouTube Channels for Walkthroughs


## 🏆 Phase 6 Certifications


*When Ready: After completing Phases 1–5*


Certifications validate your skills to employers. Do them in order:


>

*💡 Budget Tip: Start with PNPT ($399) — it’s practical, respected, and far cheaper than OSCP. Many Indian Red Teamers recommend it as your first paid cert.*


## 🗓️ Week-by-Week Study Schedule


Follow this if you can give 2–3 hours/day:


## The 5 Rules of Becoming a Red Teamer


These rules will save you months of wasted effort:


Rule 1 — Practice beats theory every time.
One hour in a lab beats five hours watching videos. Always be hands-on.


Rule 2 — Master one thing before moving to the next.
Don’t jump to AD attacks before you understand networking. The roadmap order exists for a reason.


Rule 3 — Document everything.
Keep a notes repo (Obsidian, Notion, or even Markdown files). Your notes are your second brain. The best Red Teamers have years of organized personal knowledge bases.


Rule 4 Join communities.


- TryHackMe Discord

- HackTheBox Discord

- Reddit: `r/netsec`, `r/redteamsec`, `r/hacking`

- Twitter/X: Follow `@_JohnHammond`, `@TCMSecurity`, `@ippsec`


Rule 5 — Build in public.
Write about what you learn — on Medium, GitHub, or Twitter. This builds your reputation before you have a job title.

## Final Thought


There is no shortcut to becoming a Red Teamer.


But there is a clear path. This roadmap is that path.


The ones who make it are not the most talented. They are the most consistent. Show up every day, follow the phases in order, and practice hands-on.


The industry is desperate for skilled Red Teamers. India especially. The jobs are there — you just need the skills.


Start Phase 1 today. One hour. Right now.


🔴 Red Team. No shortcuts.

---

*Originally published on [Medium](https://infosecwriteups.com/the-complete-red-teaming-roadmap-beginner-to-professional-100-free-resources-6183e451ee4a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
