# :game_die: CyberDefender: “DanaBot Lab” Challenge Writeup

---

# CyberDefender: “DanaBot Lab” Challenge Writeup

## Scenario

The SOC team has detected suspicious activity in the network traffic, revealing that a machine has been compromised. Sensitive company information has been stolen. Your task is to use Network Capture (PCAP) files and Threat Intelligence to investigate the incident and determine how the breach occurred.

>

***Category: Network Forensics*

***Tactics: Execution, Command and Control*

***Tools: Wireshark, VirusTotal, ANY.RUN, Network Miner*

## Introduction

In cybersecurity, every byte tells a story — a story of attack and defense, intrusion and investigation. Recently, I participated in a CTF challenge where the SOC detected a breach: sensitive company data was stolen, and it was up to me to dig through network traffic, uncover the attacker’s trail, and analyze the malicious payloads.

I relied heavily on [NetworkForensicsAI](https://github.com/Sh3n0bi/NetForensicAI), my custom deep packet inspection tool, to automate and accelerate packet analysis. Let me take you through the full journey, from identifying the attacker’s IP to hashing malicious DLLs — all with explanations, code snippets, and insights.

## Questions

>

***Q1: ***Which IP address was used by the attacker during the initial access?

I started by running **NetworkForensicsAI’s** deep packet inspection script on the suspicious PCAP file:

```
python3 packetsensei_pro_file_save.py 205-DanaBot.pcap --save-files
```

This command performs a deep inspection and extracts any files carried inside the traffic.

Output snippet:

```
[*] Starting Deep Packet Inspection on 205-DanaBot.pcap
[+] DPI Results (Top 5):
Src: 10.2.14.101:49786 -> Dst: 62.173.142.148:80
Payload: GET /login.php HTTP/1.1
Host: portfolio.serveirc....
...
[+] Saved file: extracted_files/188.114.97.3_80->10.2.14.101_49799.exe (11923100 bytes)
[+] Saved file: extracted_files/10.2.14.101_49804->40.83.50.91_443.exe (40059 bytes)
[+] Saved file: extracted_files/23.0.174.88_443->10.2.14.101_49576.exe (4653 bytes)
[+] Total Files Found: 3
```

The script’s analysis pointed me directly to the external IP `62.173.142.148` as the destination of the initial HTTP request on port 80, indicating the attacker’s control.

```
Answer: 62.173.142.148
```

>

***Q2: ***What is the name of the malicious file used for initial access?

Next, I wanted to know *which* file the attacker used for initial access.
I used **Wireshark’s Follow TCP Stream** on the session between `10.2.14.101` `62.173.142.148` on port 80. The HTTP response revealed:

```
Content-disposition: attachment;filename=allegato_708.js
```

So the malicious file delivered was named:

```
Answer: allegato_708.js
```

>

***Q3: ***What is the SHA-256 hash of the malicious file used for initial access?

Unfortunately, the PCAP did not directly contain a saved copy of this JS file. So I leveraged threat intelligence platforms for clues.

## Get SHENOBIE’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I searched for `allegato_708.js` and the attacker IP in public sandboxes and found matching reports on [Hybrid Analysis](https://hybrid-analysis.com/sample/723f84316119268fe600907e04a446f9c6b3000232b96aceeb1ea41db5ea7dbe/675e64a40f695fe65d0591a1) and [ANY.RUN.](https://any.run/report/847b4ad90b1daba2d9117a8e05776f3f902dda593fb1252289538acf476c4268/a886894d-8ae4-4d59-a990-b59536885da8)

From ANY.RUN a detailed report, I found the SHA-256 hash of the JavaScript payload:

```
Answer: 847B4AD90B1DABA2D9117A8E05776F3F902DDA593FB1252289538ACF476C4268
```

>

***Q4: ***Which process was used to execute the malicious file?

The sandbox behavior report showed that `allegato_708.js` was executed by:

>

`*wscript.exe*`

Windows Script Host’s It `wscript.exe` is a favorite tool for attackers to run scripts stealthily.

```
Answer: wscript.exe
```

>

***Q5: ***What is the file extension of the second malicious file utilized by the attacker?

The sandbox also showed the attacker dropped a second-stage payload:

```
%WINDIR%\system32\advapi32.dll
```

A DLL file — often used for side-loading and persistence.

```
Answer: .dll
```

>

***Q6: ***What is the MD5 hash of the second malicious file?

Digging deeper into the sandbox’s file system, I found a temporary DLL file dropped by the attacker:

```
C:\Users\admin\AppData\Local\Temp\JffleeTicl.dll
```

Its MD5 hash (from the sandbox report) was:

```
Answer: E758E07113016ACA55D9EDA2B0FFEEBE
```

## Conclusion

Network forensics is a thrilling blend of detective work and technical prowess. This investigation took me from a single PCAP file to a complete understanding of how an attacker infiltrated a network and deployed multi-stage malware.

Thanks for coming along on the journey — I hope this walkthrough inspires your cyber hunting adventures!

---
