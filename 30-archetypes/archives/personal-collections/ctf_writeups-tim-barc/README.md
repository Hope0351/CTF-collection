![Total Writeups](https://img.shields.io/badge/CTF%20Writeups-209-blue?style=flat)
![Endpoint Forensics](https://img.shields.io/badge/Endpoint%20Forensics-82-blue?style=flat)
![Network Forensics](https://img.shields.io/badge/Network%20Forensics-44-blue?style=flat)
![Mobile Forensics](https://img.shields.io/badge/Mobile%20Forensics-3-blue?style=flat)
![IDS/IPS](https://img.shields.io/badge/IDS%2FIPS-2-blue?style=flat)
![SIEM](https://img.shields.io/badge/SIEM-22-blue?style=flat)
![CTI](https://img.shields.io/badge/CTI-8-blue?style=flat)
![Email Analysis](https://img.shields.io/badge/Email%20Analysis-5-blue?style=flat)
![Malware Analysis](https://img.shields.io/badge/Malware%20Analysis-20-blue?style=flat)
![Reverse Engineering](https://img.shields.io/badge/Reverse%20Engineering-3-blue?style=flat)
![Pentesting](https://img.shields.io/badge/Pentesting-20-blue?style=flat)

# CTF Writeups
Welcome to my CTF Writeups repository! Here, I document the solutions and methodologies used to solve various Capture The Flag (CTF) challenges. This repository is intended to serve as a learning resource for others interested in cybersecurity and CTF competitions.
Capture The Flag (CTF) competitions are a popular way to practice and improve cybersecurity skills. These competitions present various challenges that require problem-solving, creativity, and technical knowledge. 

## Writeups
The writeups in this repository (located in the "writeups" folder) are categorised based on the nature of the challenge. Each writeup provides step-by-step solutions, along with explanations of the tools and techniques used. The difficulty rating associated with each challenge matches the difficulty rating given by the platform hosting the challenge/lab/ctf, therefore, take it with a grain of salt as some challenges rated as hard are actually easy, etc. The rating is out of 5, where 5 stars means the challenge is enjoyable and 1 being not enjoyable. Whilst this will of course have personal bias, my rating is not on the basis of whether I enjoyed it, it's more on the quality and realism of the challenge. 

Disclaimer! In all honesty, some of these writeups are written poorly, mainly because I complete them to learn practical skills, not to practice reporting. When it comes to well written writeups, I recommend reading my most recent ones.

## Where to Start
I recommend starting with the easy or medium rated challenges, there is honestly little difference between the two ratings for the most part. You can find challenges associated with each difficulty rating by clicking CTRL + F and pasting one of the following tags:
- 🟢 Easy
- 🟡 Medium
- 🔴 Hard
  
When it comes to what platform to use, that depends on your interests and skill level. For DFIR (digital forensics and incident response) and CTI (cyber threat intelligence) based challenges I highly recommend CyberDefenders, as it provides the most realistic challenges and often requires the use of VMs or a home lab. If you are a beginner, TryHackMe is a great place to start, as it often provides a VM or you can always use the AttackBox which comes preinstalled with a bunch of tools. Lastly, if you are intersted in becoming a blue teamer (stricly SOC operations), I recommend checking out blue team labs online (BTLO).

## Table of Contents
- [Endpoint Forensics](#endpoint-forensics)
- [Network Forensics](#network-forensics)
- [Mobile Forensics](#mobile-forensics)
- [IDS/IPS](#idsips)
- [SIEM (ELK, Splunk, etc.)](#siem-elk-splunk-etc)
- [Cyber Threat Intelligence (CTI)](#cyber-threat-intelligence-cti)
- [Email Analysis](#email-analysis)
- [Malware Analysis](#malware-analysis)
- [Reverse Engineering](#reverse-engineering)
- [Pentesting](#pentesting)
- [Tools Used](#tools-used)
- [Personal Platform Profiles](#personal-platform-profiles)

<br>

### **Endpoint Forensics**
These challenges mainly involve investigating compromised endpoints, primarily Windows and Linux, using a variety of forensic tools. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| KioskExpo7 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/kioskexpo7/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ | `DB Browser for SQLite` `Registry Explorer` `MFTECmd` `Timeline Explorer` `PECmd` `Notepad++` `R-Studio` `MFT Explorer` |
| XMRig Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/xmrig/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ | `Built-in Linux Tools` `VirusTotal` `Photorec` `Linux Forensics` |
| ConfluenceRCE Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/confluencerce/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ | `grep` `uniq` `cut` `VirusTotal` `Built-in Linux Tools` `Linux Forensics` |
| Stealthy Ascent Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/stealthy-ascent/) | 🟡 Medium  | ⭐⭐⭐ | `Built-in Linux Tools` `Linux Forensics` |
| RepoReaper Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/reporeaper/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `FTK Imager` `DB Browser for SQLite` `DCode` `Event Log Explorer` `MFTECmd` `Timeline Explorer` `VirusTotal` `Registry Explorer` `PECmd` `UAC Bypass` `Privilege Escalation` |
| Maranhao Lab| [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/maranhao/) | 🟢 Easy | ⭐⭐⭐⭐⭐ |  `FTK Imager` `EvtxECmd` `Timeline Explorer` `DB Browser for SQLite` `MFTECmd` `VirusTotal` `Infostealer`  |
| TheTruth Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/thetruth/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ | `Autopsy` `DB Browser for SQLite` `DCode` `JADX` `Mobile Forensics` `Android Forensics` |
| Malicious PyPi Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malicious-pypi/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ |  `Notepad++` `Event Log Explorer` `EvtxECmd` `Timeline Explorer` `ProcMon` `Registry Explorer` `PECmd` `VirusTotal` |
| Job Trap Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/job-trap/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ |  `FTK Imager` `DB Browser for SQLite` `DCode` `Olevba` `EvtxECmd` `Timeline Explorer` `Notepad++`  |
| Andromeda Bot Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/andromeda-bot/) | 🟡 Medium  | ⭐⭐⭐⭐⭐ |  `MemProcFS` `EvtxECmd` `Timeline Explorer` `VirusTotal` `Memory Forensics`  |
| T1598.002 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/t1598002/) | 🟢 Easy | ⭐⭐⭐⭐⭐ |  `oledump` `Google Admin Toolbox Messageheader` |
| RevengeHotels APT Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/revengehotels-apt/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `DB Browser for SQLite` `Event Log Explorer` `Timeline Explorer` `EvtxECmd` `dnSpy` `CyberChef` |
| BankingTroubles Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/bankingtroubles/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `Volatility 2` `Strings` `Foremost` `peepdf` `pdf-parser` `jsunpack`  `Memory Forensics` |
| MrRobot Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/mrrobot/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility 2` `Outlook Forensics Wizard` `R-Studio` `Strings` `Notepad++` `VirusTotal` `Process Injection` `Process Hollowing` `Memory Forensics` |
| Chollima Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/weblogic/) | 🟡 Medium | ⭐⭐ | `MemProcFS` `CyberChef` `Strings` `Memory Forensics` |
| Chollima Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/chollima/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `Event Log Explorer` `Timeline Explorer` `MFTECmd` `VirusTotal` `Notepad++` `Registry Explorer` `Python Analysis` |
| PwnedDC Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/pwned-dc/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `Event Log Explorer` `Arsenal Image Mounter` `Outlook Forensics Wizard` `olevba` `scdbg` `Volatility 2` `ClamScan` `VirusTotal` `HxD` `Resource Hacker` `Strings` `Python` `VBA Stomping` `yara` |
| DetectLog4j Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/detectlog4j/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Arsenal Image Mounter` `Registry Explorer` `Event Log Explorer` `CyberChef` `FakeNet` `Java Decompiler` `VirusTotal` `dnSpy` `CVE-2021-44228` |
| Szechuan Sauce Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/szechuan-sauce/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility 3` `Arsenal Image Mounter` `Registry Explorer` `EvtxECmd` `Timeline Explorer` `VirusTotal` `Wireshark` `NetworkMiner` `DS Internals PowerShell framework` `Crack Station` `Event Log Explorer` `FTK Imager` `Credential Dumping` |
| Zerologon Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/zerologon/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `MFTECmd` `Timeline Explorer` `LECmd` `EvtxECmd` `CyberChef` `Notepad++` `Event Log Explorer` `Windows Forensics` |
| Phishy Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/phishy/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `Autopsy` `Registry Explorer` `WhatsApp Viewer` `CyberChef` `Olevba` `oledump.py` `BrowsingHistoryView` `PasswordFox` `VirusTotal` `Windows Forensics` `Macro analysis` |
| Hammered Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/hammered/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Linux Command Line Tools` `Linux Forensics` |
| SpottedInTheWild Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/spottedinthewild/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `Arsenal Image Mounter` `PECmd` `MFTECmd` `EvtxECmd` `Timeline Explorer` `Strings` `CyberChef` `AnyRun` `CVE-2023-38831` `bitsadmin` `Windows Forensics` |
| Akira Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefedners](https://cyberdefenders.org/blueteam-ctf-challenges/akira/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility 3` `MemProcFS` `EvtxECmd` `Timline Explorer` `Strings` `Text Editor` `Windows Forensics` `PsExec` |
| IcedID 2 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/icedid-2/) | 🟡 Medium | ⭐⭐⭐ | `Volatility 3` `MemProcFS` `Text Editor` `VirusTotal` `Windows Forensics` |
| MinerHunt Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/minerhunt/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `EvtxECmd` `Timeline Explorer` `VirusTotal` `Windows Forensics` `Microsoft SQL Server` `IFEO` `WMI` |
| LummaStealer Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/lummastealer/)  | 🟡 Medium | ⭐⭐⭐⭐⭐ | `EvtxECmd` `Timeline Explorer` `DB Browser for SQLite` `Windows Forensics` |
| VaultBreak Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/vaultbreak/)  | 🟡 Medium | ⭐⭐⭐⭐⭐ | `DB Browser for SQLite` `EvtxECmd` `Timeline Explorer` `MFTECmd` `Windows Forensics` `WMI` `Scheduled Tasks` |
| IronShade | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/room/ironshade) | 🟡 Medium | ⭐⭐⭐⭐ | `Bash` `Linux Forensics` |
| Hunter Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/hunter/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `Registry Explorer` `DCode` `EvtxECmd` `Timeline Explorer` `PECmd` `Sublime` `DB Browser for SQLite` `SysTools Outlook PST Viewer` `ShellBags Explorer` `JumpListExplorer` `Windows Forensics` |
| CrownJewel1 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [HackTheBox](https://app.hackthebox.com/sherlocks/CrownJewel-1) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Hayabusa` `Timeline Explorer` `EVTXCmd` `MFTECmd` `Event Viewer` `ntds.dit` `Volume Shadow Copies` |
| Lockbit Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/lockbit/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `EVTXCmd` `Timeline Explorer` `Notepad ++` `VirusTotal` |
| DarkCrystal Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/darkcrystal/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility3` `Timeline Explorer` `EVTXCmd` |
| QBot Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/qbot/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility3` `VirusTotal` `Malicious Excel Document` |
| ELPACO-team Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/elpaco-team/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `EVTXCmd` `Timeline Explorer` `MFTECmd` `VirusTotal` |
| Retracted                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/r/room/retracted)                             | 🟢 Easy | ⭐⭐ | `Event Viewer` |
| Unattended                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)            | [TryHackMe](https://tryhackme.com/r/room/unattended)                            | 🟡 Medium | ⭐⭐⭐ | `Registry Explorer` `Autopsy` |
| Disgruntled                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)           | [TryHackMe](https://tryhackme.com/r/room/disgruntled)                           | 🟢 Easy | ⭐ | `cat` |
| Secret Recipe                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)         | [TryHackMe](https://tryhackme.com/r/room/registry4n6)                           | 🟡 Medium | ⭐⭐⭐⭐ | `Registry Explorer` |
| Critical                      | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)              | [TryHackMe](https://tryhackme.com/r/room/critical)                              | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Volatility3` `strings` |
| Tempest                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [TryHackMe](https://tryhackme.com/r/room/tempestincident)                       | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Timeline Explorer` `WireShark` `Brim` `CyberChef` `VirusTotal` |
| Boogeyman 2                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)    | [TryHackMe](https://tryhackme.com/r/room/boogeyman2)                            | 🟡 Medium | ⭐⭐⭐⭐⭐ | `text editor` `Olevba` `Volatility2` |
| Ramnit                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/ramnit/) | 🟢 Easy | ⭐⭐⭐⭐ | `Volatility3` `VirusTotal` |
| Reveal                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/reveal/) | 🟢 Easy | ⭐⭐⭐⭐ | `Volatility3` `Timeline Explorer` `VirusTotal` |
| FakeGPT                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/fakegpt/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `ExtAnalysis` `CyberChef` |
| Brave                         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/brave/) | 🟡 Medium | ⭐⭐⭐⭐ | `Volatility3` `HxD` |
| Redline                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/redline/) | 🟢 Easy | ⭐⭐⭐⭐ | `Volatility3` `Timeline Explorer` `VirusTotal` |
| Memory Analysis               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/memory-analysis)             | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Volatility3` `VirusTotal` `Crackstation` |
| Lockbit                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)               | [LetsDefend](https://app.letsdefend.io/challenge/lockbit)                      | 🟢 Easy | ⭐⭐⭐⭐ | `Volatility3` `VirusTotal` |
| WinRar 0-Day                  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)         | [LetsDefend](https://app.letsdefend.io/challenge/winrar-0-day)                 | 🟡 Medium | ⭐⭐⭐ | `Volatility3` `CyberChef` |
| BlackEnergy Lab               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/blackenergy/) | 🟡 Medium | ⭐⭐⭐ | `Volatility3` `Timeline Explorer` `VirusTotal` |
| Memory Analysis - Ransomware | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/memory-analysis-ransomware-7da6c9244d) | 🟡 Medium | ⭐⭐⭐⭐ | `Volatility3` |
| Tardigrade                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)            | [TryHackMe](https://tryhackme.com/room/tardigrade)                             | 🟡 Medium | ⭐ | `Linux command-line` |
| Sysinternals                  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/sysinternals/) | 🟡 Medium | ⭐⭐ | `Autopsy` `AppCompatParser` `AmCacheParser` `VirusTotal` |
| REvil Corp                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)            | [TryHackMe](https://tryhackme.com/room/revilcorp)                              | 🟡 Medium | ⭐⭐⭐ | `Redline` `VirusTotal` | 
| Forensics                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/room/forensics)                              | 🔴 Hard | ⭐⭐⭐⭐⭐ | `Volatility3` `strings` | 
| Dead End?                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)              | [TryHackMe](https://tryhackme.com/room/deadend)                                | 🔴 Hard | ⭐⭐⭐ | `Volatility3` `FTK Imager` `VirusTotal` |  
| Insider Lab                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/insider/) | 🟢 Easy | ⭐⭐⭐ | `FTK Imager` |
| Seized Lab                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/seized/)  | 🟡 Medium | ⭐⭐⭐ | `Volatility3` `strings` |
| Browser Forensics - Cryptominer | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/browser-forensics-cryptominer-aa00f593cb) | 🟢 Easy | ⭐⭐⭐ | `FTK Imager` | 
| Kraken Keylogger Lab         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/krakenkeylogger/) | 🟡 Medium | ⭐⭐ | `DB Browser for SQLite` `LECmd` `text editor` |   
| HireMe Lab                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/hireme/)  | 🟡 Medium | ⭐⭐⭐⭐ | `FTK Imager` `Registry Explorer` `LECmd` `RegRipper` `OST Viewer` |
| DumpMe Lab                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/dumpme/)  | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Voltiliaty2` `VirusTotal` | 
| AfricanFalls Lab             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/africanfalls/) | 🟡 Medium | ⭐⭐⭐ | `FTK Imager` `rifiuti2` `Browsing History View` `PECmd` `ShellBags Explorer` |
| Injector Lab                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/injector/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `Volatility3` `Registry Explorer` `cut` | 
| NintendoHunt Lab             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/nintendohunt/) | 🔴 Hard | ⭐⭐ | `Volatility2` `Strings` |
| DeepDive Lab                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/deepdive/) | 🔴 Hard | ⭐⭐ | `Volatility2` `VirusTotal` |
| CorporateSecrets Lab         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/corporatesecrets/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `MFTECmd` `Timeline Explorer` `RegRipper` `PECmd` |
| Bruteforce                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)        | [BTLO](https://blueteamlabs.online/home/challenge/bruteforce-16629bf9a2)       | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Timeline Explorer` `cat` |
| Silent Breach                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/silent-breach/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `FTK Imager` `Browsing History View` `DB Browser for SQLite` `Strings` `Grep` |
| Amadey Lab                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/amadey/)   | 🟢 Easy | ⭐⭐⭐ | `Volatility3` |
| DiskFiltration               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/room/diskfiltration) | 🔴 Hard | ⭐⭐⭐⭐ | `Autopsy` `Timeline Explorer` `MFTECmd` `Exiftool` `HxD` |
| Volatility Traces Lab        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/volatility-traces/) | 🟢 Easy | ⭐⭐⭐⭐⭐ |  `Volatility 3`  `Defense Evasion` |
| MeteorHit Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/meteorhit/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Registry Explorer` `Timeline Explorer` `EVTXCmd` `MFTECmd` `VirusTotal` `NTFS Forensics` `Sysmon` `Defense Evasion` |  
| Fog Ransomware Lab          | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/fog-ransomware/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `DB Browser for SQLite` `MFTECmd` `Timeline Explorer` `EvtxECmd` `VirusTotal`   
| NetX-Support Lab            | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/netx-support/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `DB Browser for SQLite` `FTK Imager` `MFTECmd` `EVTXCmd` `PECmd` `CyberChef` `Registry Explorer` `LECmd` |  
| Beta Gamer Lab              | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/beta-gamer/) | 🟡 Medium | ⭐⭐⭐⭐⭐ |  `DB Browser for SQLite` `FTK Imager` `MFTECmd` `EVTXCmd` |
| Trigona Ransomware Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/trigona-ransomware/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `EVTXCmd` `Timeline Explorer` `Registry Explorer` `MFTECmd` `PECmd` `AmcacheParser` |
| Deep Blue                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)        | [BTLO](https://blueteamlabs.online/home/investigation/deep-blue-a4c18ce507)     | 🟢 Easy | ⭐⭐⭐ | `deepbluecli` `Event Viewer` |
| Brutus                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [HackTheBox](https://app.hackthebox.com/sherlocks/Brutus) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `grep` `awk` `sed` `sort` `uniq` `last` `grep` `auth.log` `wtmp` |
| Crownjewel-2                  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [HackTheBox](https://app.hackthebox.com/sherlocks/CrownJewel-2) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `EvtxECmd` `Timeline Explorer` |
| Operationa Blackout 2025: Phantom Check | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [HackTheBox](https://app.hackthebox.com/sherlocks/Operation%20Blackout%202025:%20Phantom%20Check/play) | 🟢 Easy | ⭐⭐ | `EvtxECmd` `Timeline Explorer` |
 
<br>

### **Network Forensics**
This category focuses on packet analysis through PCAP files and zeek logs. Tools like Wireshark, Zeek, and Brim are frequently used. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| XXE Infiltration Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/xxe-infiltration/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` |
| JetBrains Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/jetbrains/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `CVE-2024-27198` |
| Openfire Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/openfire/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `CyberChef` `CVE-2023-32315` |
| Trident Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/trident/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` `IDA Pro` `scdbg` `CVE-2021-40444` `shellcode analysis` |
| NukeTheBrowser Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/nukethebrowser/) | 🔴 Hard | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `VirusTotal` `scdbg` `CVE-2005-2127` `shellcode analysis` |
| HoneyBOT Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/honeybot/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` `scdbg` `CVE-2003-0533` `shellcode analysis` |
| Malware Traffic Analysis 5 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malware-traffic-analysis-5/) | 🟡 Medium | ⭐⭐ | `Wireshark` `Zui` `VirusTotal` `Oledump` `Thunderbird`   |
| Malware Traffic Analysis 4 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malware-traffic-analysis-4/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` |
| Malware Traffic Analysis 3 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malware-traffic-analysis-3/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` `GHex` `pesec` `Python` |
| Malware Traffic Analysis 2 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malware-traffic-analysis-2/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` |
| Malware Traffic Analysis 1 Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malware-traffic-analysis-1/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` |
| WireDive Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/wiredive/) | 🟡 Medium | ⭐ | `Wireshark` |
| Acoustic Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/acoustic/) | 🟡 Medium | ⭐⭐ | `Wireshark` `Zui` `VoIP` `Command line` |
| RetailBreach Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/retailbreach/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `CyberChef` `VirusTotal` |
| RCEMiner Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/rceminer/)  | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `VirusTotal` |
| BlueSky Ransomware Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/bluesky-ransomware/)  | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `Event Log Explorer` `CyberChef` `VirusTotal` |
| HawkEye Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/hawkeye/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Zui` `NetworkMiner` `VirusTotal` |
| PacketMaze Lab | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/packetmaze/)  | 🟡 Medium | ⭐ | `Wireshark` `NetworkMiner` |
| Boogeyman 1                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)    | [TryHackMe](https://tryhackme.com/r/room/boogeyman1)                            | 🟡 Medium | ⭐⭐⭐ | `Thunderbird` `lnkparse` `cat` `Wireshark` |
| PacketDetective               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/packetdetective/) | 🟢 Easy | ⭐⭐⭐⭐ | `Wireshark` |
| DanaBot                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/danabot/)  | 🟢 Easy | ⭐⭐⭐⭐ | `Wireshark` `VirusTotal` `Network Miner` |
| Web Investigation             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/web-investigation/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `MaxMind GeoIP database` |
| WebStrike                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/webstrike/) | 🟢 Easy | ⭐⭐⭐⭐ | `Wireshark` |
| PoisonedCredentials           | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/poisonedcredentials/) | 🟢 Easy | ⭐⭐ | `Wireshark` |
| TomCat Takeover               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/tomcat-takeover/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` |
| PsExec Hunt                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/psexec-hunt/) | 🟢 Easy | ⭐⭐⭐ | `Wireshark` |
| Shellshock Attack             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/shellshock-attack)             | 🟢 Easy | ⭐ | `Wireshark` |
| HTTP Basic Auth               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/http-basic-auth)               | 🟢 Easy | ⭐⭐ | `Wireshark` |
| Brute Force Attack            | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/brute-force-attacks)           | 🟡 Medium | ⭐⭐⭐⭐ | `Wireshark` `cat` `grep` |
| OpenWire Lab                  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/openwire/) | 🟡 Medium | ⭐⭐⭐⭐ | `Wireshark` |
| Network Analysis - Web Shell  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/network-analysis-web-shell-d4d3a2821b) | 🟢 Easy | ⭐⭐⭐⭐ | `Wireshark` |
| XMLRat Lab                            | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/xlmrat/)    | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Wireshark` `VirusTotal` `CyberChef` |
| Network Analysis - Ransomware        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)| [BTLO](https://blueteamlabs.online/home/challenge/network-analysis-ransomware-3dd520c7ec) | 🟡 Medium | ⭐⭐ | `Wireshark` |
| l337 S4uc3 Lab                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)| [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/l337-s4uc3/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `Network Miner` `Brim` `volatility 2` |
| Piggy                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                 | [BTLO](https://blueteamlabs.online/home/investigation/piggy-aij2bd8h2)          | 🟢 Easy | ⭐⭐⭐ | `Wireshark` `VirusTotal` | 
| Shiba Insider                         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)         | [BTLO](https://blueteamlabs.online/home/challenge/shiba-insider-5b48123711)     | 🟢 Easy | ⭐⭐ | `Wireshark` `exiftool` | 
| Tshark Challenge II: Directory        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)| [TryHackMe](https://tryhackme.com/r/room/tsharkchallengestwo)                  | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Tshark` `VirusTotal` |
| TShark Challenge 1: Teamwork          | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)| [TryHackMe](https://tryhackme.com/r/room/tsharkchallengesone)                   | 🟢 Easy | ⭐⭐ | `Tshark` `VirusTotal` |
| TShark                                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                     | [TryHackMe](https://tryhackme.com/r/room/tshark)                                | 🟡 Medium | ⭐⭐⭐ | `Tshark` | 
| Carnage                               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)            | [TryHackMe](https://tryhackme.com/r/room/c2carnage)                             | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Wireshark` `VirusTotal` | 
| Warzone 2                             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)        | [TryHackMe](https://tryhackme.com/r/room/warzonetwo)                            | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Brim` `Network Miner` `Wireshark` `VirusTotal` `CyberChef` |
| Warzone 1                             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                   | [TryHackMe](https://tryhackme.com/r/room/warzoneone)                            | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Brim` `Network Miner` `Wireshark` `VirusTotal` | 
| Masterminds                           | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                | [TryHackMe](https://tryhackme.com/r/room/mastermindsxlq)                        | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Brim` `VirusTotal` |
| Zeek Exercises                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/r/room/zeekbroexercises)                      | 🟡 Medium | ⭐⭐⭐⭐⭐ | `zeek` `CyberChef` `VirusTotal` |

<br>

### **Mobile Forensics**
This section focuses on investigating mobile devices. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| AndroidBreach Lab                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/androidbreach/)      | 🟡 Medium | ⭐⭐⭐⭐ | `ALEAPP` `jadx` `CyberChef` `Android Forensics` |
| The Crime lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/the-crime/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `ALEAPP` |
| Eli Lab                      | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/eli/)      | 🟡 Medium | ⭐⭐ | `CLEAPP` |

<br>

### **IDS/IPS**
Writeups here explore intrusion detection and prevention systems like Snort. These labs simulate network-based attacks and help develop skills in detecting and repsonding to suspicious traffic patterns and rule-based alerts. 
| Challenge        | Writeup                                                                                | Challenge Link                                                     | Difficulty | Rating | Tags | 
| ---------------- | -------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |------------|----------|-----------------------------|
| Snort Challenge the Basics  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/snortchallenges2)       | 🟡 Medium | ⭐⭐ |  `Snort` |
| Snort Challenge live attacks | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/jr/snortchallenges2) | 🟡 Medium | ⭐⭐⭐ | `Snort` |

<br>

### **SIEM (ELK, Splunk, etc.)**
These challenges involve using SIEMs like Splunk, ELK, and Wazuh to identify threats. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| T1110-003 Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/t1110003/) | 🟢 Easy  | ⭐⭐⭐⭐ | `ELK` `password spraying` `RDP` |
| REvil Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/revil/) | 🟢 Easy  | ⭐⭐⭐⭐⭐ | `ELK` |
| HafinumAPT Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/hafinumapt/) | 🔴 Hard  | ⭐⭐⭐⭐⭐ | `ELK` |
| GitTheGate Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/gitthegate/) | 🟡 Medium | ⭐⭐⭐ | `ELK` `CVE-2019-7609` |
| Kerberoasted Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/kerberoasted/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` `Kerberoasting` |
| ElasticCase Lab                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/elasticcase/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` |
| Monday Monitor                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)        | [TryHackMe](https://tryhackme.com/r/room/mondaymonitor)                         | 🟢 Easy | ⭐⭐⭐ | `Wazuh` `CyberChef` |
| NerisBot Lab                  | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/nerisbot/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Splunk` `Zeek` `Suricata` `VirusTotal` |
| Peak                          | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [BTLO](https://blueteamlabs.online/home/investigation/peak-98765b84cb)          | 🟡 Medium | ⭐⭐ | `ELK` |
| Defaced                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)          | [BTLO](https://blueteamlabs.online/home/investigation/defaced-593f17897e)       | 🟢 Easy | ⭐⭐ | `ELK` |
| SOC Alpha 3                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [BTLO](https://blueteamlabs.online/home/investigation/soc-alpha-3-cfb2546607)   | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` `VirusTotal` |
| SOC Alpha 2                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [BTLO](https://blueteamlabs.online/home/investigation/soc-alpha-2-f3825dedc4)   | 🟢 Easy | ⭐⭐⭐⭐⭐ | `ELK` |
| SOC Alpha 1                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [BTLO](https://blueteamlabs.online/home/investigation/soc-alpha-1-2ba4c4a550)   | 🟢 Easy | ⭐⭐⭐ | `ELK` |
| Middle Mayhem                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)    | [BTLO](https://blueteamlabs.online/home/investigation/middlemayhem-aa3c27f5d1)  | 🟢 Easy | ⭐⭐⭐ | `ELK` |
| Boogeyman 3                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)    | [TryHackMe](https://tryhackme.com/r/room/boogeyman3)                             | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` |
| New Hire Old Artifacts        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)| [TryHackMe](https://tryhackme.com/r/room/newhireoldartifacts)                   | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` |
| PS Eclipse                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/r/room/posheclipse)                           | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` |
| Conti                         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                 | [TryHackMe](https://tryhackme.com/r/room/contiransomwarehgh)                    | 🟡 Medium | ⭐⭐⭐⭐⭐ | `ELK` |
| SlingShot                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/r/room/slingshot)                             | 🟢 Easy | ⭐⭐⭐⭐ | `ELK` `CyberChef` |
| Benign                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                | [TryHackMe](https://tryhackme.com/r/room/benign)                                | 🟡 Medium | ⭐⭐⭐ | `ELK` |
| Investigating with Splunk     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/investigatingwithsplunk)          | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Splunk` |
| ItsyBitsy                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)             | [TryHackMe](https://tryhackme.com/r/room/itsybitsy)                             | 🟡 Medium | ⭐⭐⭐ | `ELK` |

<br>

### **Cyber Threat Intelligence (CTI)**
These labs focus on cyber threat intelligence, you will learn how to use threat intelligence platforms like VirusTotal, Malpedia, MITRE ATT&CK, and much more. Most of these challenges involve tracking malware campaigns, attributing malware to threat actors, etc. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| Trooper                       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)       | [TryHackMe](https://tryhackme.com/r/room/trooper)                               | 🟢 Easy | ⭐⭐⭐⭐ | `Open CTI` |
| Yellow RAT                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/yellow-rat/) | 🟢 Easy | ⭐⭐ | `VirusTotal` |
| GrabThePhiser                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/grabthephisher/) | 🟢 Easy | ⭐⭐⭐ | `Sublime` |
| Red Stealer                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/red-stealer/) | 🟢 Easy | ⭐⭐ | `VirusTotal` `MalwareBazaar` |
| PhishStrike Lab               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/phishstrike/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Sublime` `URLhaus` `VirusTotal` |
| Tusk Infostealer Lab          | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/tusk-infostealer/) | 🟢 Easy | ⭐ | `Kaspersky Threat Intelligence Portal` `VirusTotal` |
| Oski Lab                      | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/oski/)     | 🟢 Easy | ⭐⭐ | `VirusTotal` `any.run` |
| IcedID                        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/icedid/)   | 🟢 Easy | ⭐ | `VirusTotal` `Tria.ge` `Malpedia` |

<br>

### **Email Analysis**
This section dives into investigating emails, primarily phishing emails. You will learn how to extract headers, decode payloads, verify SPF/DKIM records, and asess malicious indicators in emails. 
| Challenge                      | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| Greenholt Phish               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/phishingemails5fgjlzxc)            | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Thunderbird` `mxtoolbox` `VirusTotal` |
| Snapped Phish-ing Line        | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/snappedphishingline)             | 🟢 Easy | ⭐⭐⭐⭐ | `VirusTotal` `text editor` |
| Phishing Analysis             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/phishing-analysis-f92ef500ce) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Sublime` `URL2PNG` |
| Phishing Analysis 2           | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/phishing-analysis-2-a1091574b8) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Sublime` `CyberChef` |
| Phishy v1                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)         | [BTLO](https://blueteamlabs.online/home/investigation/phishy-v1-e3b5be4fe8)     | 🟡 Medium | ⭐⭐⭐ |

<br>

### **Malware Analysis**
This section focuses on static and dynamic malware analysis. These writeups document the analysis of malicious PE files, scripts, macros, and more. 
| Challenge                                 | Writeup                                                                                   | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|-------------------------------------------|-------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| TeleStealer Lab                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/telestealer/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `DIE` `ProcMon` `Wireshark` `Python`|
| AgentTesla Lab                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/agenttesla/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `DIE` `AutoIT Extractor` `PE-sieve` `Process Explorer` `CFF Explorer` `dnSpy` `CyberChef` `ProcMon` |
| MalaCrypt Lab                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/malacrypt/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `PE Studio` `Floss` `Strings` `CyberChef` `VirusTotal` `ProcMon` `Cutter` `Capa` |
| XWorm Lab                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/xworm/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `PE Studio` `DIE` `dnSpy` `ANY.RUN` `VirusTotal` |
| MalBuster                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)           | [TryHackMe](https://tryhackme.com/r/room/malbuster)                            | 🟡 Medium | ⭐⭐⭐⭐ | `pestudio` `detect it easy` `VirusTotal` `CTF Explorer` `capa` `floss` |
| Mr. Phisher                               | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)           | [TryHackMe](https://tryhackme.com/r/room/mrphisher)                            | 🟢 Easy | ⭐ | `LibreOffice Writer` |
| Dunkle Materie                            | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [TryHackMe](https://tryhackme.com/r/room/dunklematerieptxc9)                  | 🟡 Medium | ⭐⭐⭐⭐ | `ProcDOT` `VirusTotal` |
| Maldoc101                                 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [CyberDefenders](https://cyberdefenders.org/blueteam-ctf-challenges/maldoc101/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `oledump` `VirusTotal` `olevba` `CyberChef` |
| Downloader                                | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [LetsDefend](https://app.letsdefend.io/challenge/downloader)                  | 🔴 Hard | ⭐⭐⭐⭐⭐| `IDA Pro` |
| Malicious Doc                             | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)   | [LetsDefend](https://app.letsdefend.io/challenge/malicious-doic)              | 🟢 Easy | ⭐ | `VirusTotal` | 
| PowerShell Script                         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/powershell-script)         | 🟢 Easy | ⭐⭐| `text editor` `VirusTotal` |
| Suspicious USB Stick                      | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)   | [BTLO](https://blueteamlabs.online/home/challenge/suspicious-usb-stick-2f18a6b124) | 🟡 Medium | ⭐ | `text editor` `VirusTotal` `peepdf` |
| Reverse Engineering - A Classic Injection | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/reverse-engineering-a-classic-injection-9791a9b784) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `pestudio` `detect it easy` `IDA Pro` `Procmon` `CyberChef` |
| PowerShell Analysis - Keylogger           | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/powershell-analysis-keylogger-9f4ab9a11c) | 🟢 Easy | ⭐⭐| `text editor` |
| Injection Series Part 3                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/injection-series-part-3-3f316e3782) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `cutter` `IDA Pro` `CyberChef` |
| Injection Series Part 4                   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/injection-series-part-4-8b3aaae8ca) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `IDA Pro` `CyberChef` |
| Reverse Engineering - Another Injection   | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/reverse-engineering-another-injection-72001745c9) | 🟢 Easy | ⭐⭐⭐⭐ | `detect it easy` `strings` `IDA Pro` `CyberChef` |
| Malware Analysis - Ransomware Script      | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [BTLO](https://blueteamlabs.online/home/challenge/malware-analysis-ransomware-script-4263fe6ecf) | 🟢 Easy | ⭐⭐⭐ | `text editor`
| Nonyx                                     | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                  | [BTLO](https://blueteamlabs.online/home/investigation/nonyx-63b4769449)       | 🟢 Easy | ⭐⭐⭐⭐ | `volatility 2` |
| Anakus                                    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)                 | [BTLO](https://blueteamlabs.online/home/investigation/anakus-dfea6f86e0)      | 🟢 Easy | ⭐⭐⭐ | `detect it easy` `VirusTotal` `sigcheck` `timeline explorer` 

<br>

### **Reverse Engineering**
Challenges in this section involve understanding program logic and uncovering hidden functionality from binaries. They often require IDA Pro, Ghidra, or Radare2.
| Challenge            | Writeup                                                                              | Challenge Link                                                                 | Difficulty | Rating | Tags | 
|---------------------|--------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|------------|----------|-----------------------------|
| Reversing ELF       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)         | [TryHackMe](https://tryhackme.com/r/room/reverselfiles)                         | 🟢 Easy  | ⭐⭐⭐⭐ | `radare2` `strings` |
| DLL Stealer         | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [LetsDefend](https://app.letsdefend.io/challenge/dll-stealer)                  | 🟡 Medium  | ⭐⭐⭐⭐⭐ | `dotPeek` |
| Beginner Crackme    | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)      | [Crackmes.one](https://crackmes.one/crackme/5f907efe33c5d424269a15d1)          | 🟢 Easy  | ⭐ | `IDA Pro`

<br>

### **Pentesting**
This section contains writeups focused on penetration testing. Challenges are typically boot2root which involve scanning, enumeration, vulnerability analysis and exploitation, privilege escalation, and more. Great for building foundation penetration testing skills and learning common attacks. 
| Challenge        | Writeup                                                                                | Challenge Link                                                     | Difficulty | Rating | Tags | 
| ---------------- | -------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |------------|----------|-----------------------------|
| Basic | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [HackThisSite](https://www.hackthissite.org/missions/basic/) | 🟡 Medium | ⭐⭐⭐ | `burp suite` |
| Silver Platter | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/silverplatter) | 🟢 Easy | ⭐⭐⭐ | `Nmap` `GoBuster` `ssh` `privilege escalation` |
| Dav | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/bsidesgtdav) | 🟢 Easy | ⭐⭐⭐ | `Nmap` `GoBuster` `hydra` `privilege escalation` |
| Wgel CTF | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/wgelctf) | 🟢 Easy | ⭐⭐⭐ | `Nmap` `dirb` `ssh` `privilege escalation` |
| Lookup | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/lookup) | 🟢 Easy | ⭐⭐⭐⭐ | `Nmap` `hydra` `searchsploit` `metasploit` `privilege escalation` |
| Toolsrus | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/toolsrus) | 🟢 Easy | ⭐⭐⭐ | `Nmap` `dirbuster` `hydra` `nikto` `metasploit` `msfvenom` |
| Raven 1 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/raven-1,256/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `arp-scan` `Nmap` `GoBuster` `wpscan` `nikto` `hydra` `ssh` `mysql` |
| Pickle Rick | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/rickdiculouslyeasy-1,207/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Nmap` `GoBuster` `nikto` `privilege escalation` |
| Mr Robot | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/mr-robot-1,151/) | 🟡 Medium | ⭐⭐⭐⭐ | `arp-scan` `Nmap` `GoBuster` `nikto` `wpscan` `hydra` `hashcat` `privilege escalation` |
| Photographer | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/photographer-1,519/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `arp-scan` `Nmap` `GoBuster` `nikto` `enum4linux` `SMB` `burp suite` |
| Lazy Admin | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/lazysysadmin-1,205/) | 🟡 Medium | ⭐⭐⭐⭐⭐ | `Nmap` `GoBuster` `hash-identifier` `searchsploit` `privilege escalation` |
| IDE | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/ide) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Nmap` `FTP` `searchsploit` `ssh` `privilege escalation` |
| Easy peasy | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/easypeasyctf) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Nmap` `GoBuster` `hash-identifier` `CyberChef` `steghide` `ssh ` `privilege escalation` |
| Colddbox Vulnhub | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/colddbox-easy,586/) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Nmap` `GoBuster` `wpscan` `hydra` `privilege escalation` |
| Colddbox THM | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/colddboxeasy) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `Nmap` `GoBuster` `wpscan` `hydra` `privilege escalation` |
| Bounty Hacker | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/cowboyhacker) | 🟢 Easy | ⭐⭐⭐⭐ | `Nmap` `FTP` `hydra` `privilege escalation` |
| Blogger1 | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [VulnHub](https://www.vulnhub.com/entry/blogger-1,675/#top) | 🟢 Easy | ⭐⭐⭐⭐⭐ | `arp-scan` `Nmap` `GoBuster` `wpscan` `privilege escalation` |
| Basic Pentesting | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/basicpentestingjt) | 🟢 Easy | ⭐⭐⭐⭐ | `Nmap` `GoBuster` `enum4linux` `SMB` `hydra` `john` `privilege escalation` |
| Anonymous | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc) | [TryHackMe](https://tryhackme.com/r/room/anonymous) | 🟡 Medium | ⭐⭐⭐⭐ | `Nmap` `enum4linux` `SMB` `FTP` `privilege escalation` |
| Agent Sudo       | [PDF](../../../../30-archetypes/archives/personal-collections/ctf_writeups-tim-barc)       | [TryHackMe](https://tryhackme.com/r/room/agentsudoctf)             | 🟢 Easy | ⭐⭐⭐⭐ | `Nmap` `curl` `hydra` `FTP` `binwalk` `steghide` `ssh` `privilege escalation` |

<br>

## Tools Used
Some of the tools used in these writeups include (not limited to):

| Category                                  | Tool Name           | Link                                                                                        |
| ----------------------------------------- | ------------------- | ------------------------------------------------------------------------------------------- |
| **Network Scanning & Enumeration**        | Nmap                | https://Nmap.org/                                                              |
|                                           | GoBuster            | https://www.kali.org/tools/gobuster/                            |
|                                           | WPScan              | https://wpscan.com/                                                         |
|                                           | enum4linux          | https://www.kali.org/tools/enum4linux/                         |
| **Vulnerability Scanning and Exploitation**| Burp Suite | https://portswigger.net/burp |
|                                            | Metasploit | https://www.metasploit.com/ |
|                                            | Nikto | https://www.cisa.gov/resources-tools/services/nikto |
|                                            | Hydra | https://www.kali.org/tools/hydra/ |
|                                            | John the Ripper | https://www.openwall.com/john/ |                                          
| **Packet Analysis and Network Monitoring** | Wireshark | https://www.Wireshark.org/ |
|                                            | TShark | https://www.Wireshark.org/docs/man-pages/tshark.html |
|                                            | Snort | https://www.snort.org/ |
|                                            | Zeek | https://zeek.org/ |
|                                            | Zui/Brim | https://www.brimdata.io/download/ |
|                                            | NetworkMiner | https://www.netresec.com/?page=NetworkMiner |
| **Binary Analysis**                        | Binwalk | inwalk |
| **Log Analysis and SIEM**                  | ELK | https://www.elastic.co/elastic-stack |
|                                            | Splunk | https://www.splunk.com/ |
|                                            | Wazuh | https://wazuh.com/ |
|                                            | Event Viewer | https://learn.microsoft.com/en-us/shows/inside/event-viewer |
|                                            | Sysmon-View | ysmonTools |
| **Cyber Threat Intelligence (CTI)**        | OpenCTI | pencti |
|                                            | Mitre ATT&CK Matrix | https://attack.mitre.org/ |
|                                            | VirusTotal | https://www.VirusTotal.com/gui/home/upload |
|                                            | URLHaus | https://urlhaus.abuse.ch/browse/ |
|                                            | IPInfo | https://ipinfo.io/ |
|                                            | Cisco Talos | https://talosintelligence.com/ |
|                                            | Shodan | https://www.shodan.io/ |
|                                            | Kasperky Threat Intelligence Portal | https://opentip.kaspersky.com/ |
|                                            | Tria.ge | https://tria.ge/ |
|                                            | Malpedia | https://malpedia.caad.fkie.fraunhofer.de/ |
|                                            | Malware Bazaar | https://bazaar.abuse.ch/browse/ |
| **Malware Analysis**                       | pestudio | https://www.winitor.com/download |
|                                            | Detect It Easy | etect-It-Easy |
|                                            | capa | apa |
|                                            | Floss | lare-floss |
|                                            | ProcDOT | https://www.procdot.com/downloadprocdotbinaries.htm |
|                                            | Olevba | letools/blob/master/oletools/olevba.py |
|                                            | Oledump | idierStevensSuite/blob/master/oledump.py |
|                                            | IDA Free | https://hex-rays.com/ida-free |
|                                            | scdbg | https://sandsprite.com/blogs/index.php?uid=7&pid=152 |
|                                            | Radare2 | https://rada.re/n/ |
|                                            | Cutter | https://cutter.re/ |
|                                            | Ghidra | https://ghidra-sre.org/ |
|                                            | AnyRun | https://any.run/ |
|                                            | FakeNet | lare-fakenet-ng |
|                                            | dnSpy | nSpy |
|                                            | Hybrid Analysis | https://hybrid-analysis.com/ |
|                                            | Joes Sandbox | https://www.joesandbox.com/#windows |
| **Forensics and Incident Response**        | Autopsy | https://www.autopsy.com/ |
|                                            | EZ Tools | https://www.sans.org/tools/ez-tools/ |
|                                            | Volatility3 | olatility3 |
|                                            | Volatility 2 | olatility |
|                                            | MemProcsFS | emProcFS |
|                                            | FTK Imager |  https://www.exterro.com/ftk-product-downloads/ftk-imager-4-7-3-81 |                        
|                                            | Browsing History View | https://www.nirsoft.net/utils/browsing_history_view.html |
|                                            | CLEAPP | Leapp |
|                                            | PasswordFox | https://www.nirsoft.net/utils/passwordfox.html |
|                                            | WhatsApp Viewer | hatsapp-viewer |
|                                            | Event Log Explorer | https://eventlogxp.com/ |
|                                            | NirSoft Tools | https://www.nirsoft.net/ |
|                                            | R-Studio | https://www.r-studio.com/Data_Recovery_Download.shtml |
|                                            | DB Browser for SQLite | https://sqlitebrowser.org/ |
|                                            | Hindsight | indsight |
| **Mobile Forensics**                       | ALEAPP | LEAPP |

## Personal Platform Profiles
- [TryHackMe | Top 1%](https://tryhackme.com/p/Timzoes)
- [BlueTeamLabs | Top 10%](https://blueteamlabs.online/home/user/239fed38c2bc3b10c6499d)
- [CyberDefenders | Top 10 Aus](https://cyberdefenders.org/p/TimmyB)
