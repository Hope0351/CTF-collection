# :mag: Digital Forensics🔍-[Ali Hadi - Mystery Hacked System Case]

> **Original Source:** [Digital Forensics🔍-[Ali Hadi - Mystery Hacked System Case]](https://infosecwriteups.com/digital-forensics-ali-hadi-mystery-hacked-system-case-24f3b6cb1a08)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# Digital Forensics🔍-[Ali Hadi — Mystery Hacked System Case]


Hey CyberDefenders, I surely we can learn a lot from Ali Hadi’s case, so bear with me to the end!


Scenario : One day an IT dept. guy/gal came to work to find the message below written in a file on his/her system! He/Her immediately reported that to you. Now you must:


- How did the threat actor get into the system? (What is your hypothesis)

- What evidence did you find that proves your hypothesis?

- How did you approach and solve the case? (write a report)

- Anything you would like to add?

>

*Let’s do Digital Forensics Investigation!*Hypothesis —


- (Initial Access) Was it through the user’s browser, binary exploitation or remote service installation?

- (Execution & Persistence) Is there any suspicious parent-children process activity, temporary folder, scheduled task or Run/RunOnce key creation?

- (C2 connection) Is there any outbound connection made, and by which process if so?

- (Data Exfiltration) Any sensitive data is exfiltrated?


Evidence tells the truth —


Checking MP Support Logs artifacts (*ProgramData/Microsoft/Windows Defender/Support*), looks like there’s no malicious file being detected and picked up by Windows Defender.

---

*Originally published on [Medium](https://infosecwriteups.com/digital-forensics-ali-hadi-mystery-hacked-system-case-24f3b6cb1a08). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
