# :mag: CyberDefender: PoisonedCredentials Lab: Network Forensics

> **Original Source:** [CyberDefender: PoisonedCredentials Lab: Network Forensics](https://infosecwriteups.com/cyberdefenders-write-up-poisonedcredentials-lab-network-forensics-a7b50a2a48af)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

## 🧩 Introduction


In this lab, we investigate a simulated network security incident involving credential poisoning attacks that exploit vulnerabilities in the LLMNR and NBT-NS protocols. These name resolution protocols, while useful in local networks, are inherently insecure due to their reliance on broadcast queries and lack of authentication, making them prime targets for man-in-the-middle attacks.


Using Wireshark, we analyze captured traffic to uncover how an attacker used these weaknesses to intercept queries, impersonate legitimate systems, and capture user credentials. Through this hands-on walkthrough, we identify poisoned queries, trace the rogue machine’s IP, and examine SMB authentication to determine the extent of the compromise.


This exercise highlights the importance of securing legacy protocols and equips you with practical network forensics skills to detect and respond to similar attacks in real-world environments.

>

*Q1: In the context of the incident described in the scenario, the attacker initiated their actions by taking advantage of benign network traffic from legitimate machines. Can you identify the specific mistyped query made by the machine with the IP address 192.168.232.162?*


Attackers like these often begin with a simple typo in a hostname. The victim machine tries to resolve a non-existent name, and the attacker swoops in to respond.


🔍 Filter Used:


```
(udp.port == 5355 or udp.port == 137)
```


This filter narrows the view to LLMNR and NBT-NS traffic. Once applie we located this mistyped query from the machine.


```
fileshaare
```


Boom — that query never should have existed. Thats’s the bait.

>

*Q2: We are investigating a network security incident. To conduct a thorough investigation, We need to determine the IP address of the rogue machine. What is the IP address of the machine acting as the rogue entity?*


Next, we need to find the IP address that responded to the mistyped query. Why? Because in a healthy network, only legitimate DNS servers should answer.


Using this filter:


```
ip.src == * and (udp.port == 5355 or udp.port == 137)
```


We identified a suspicious responder:


```
Rogue IP: 192.168.232.215
```


The IP was not a DNS server, yet it replied to multiple resolution queries — classic poisoning behavior.

>

*Q3: As part of our investigation, identifying all affected machines is essential. What is the IP address of the second machine that received poisoned responses from the rogue machine?*


Poisoning attacks typically spread fast. We need to uncover other victims who had also received poisoned responses.


## Get SHENOBIE’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Using this refined filter:


```
ip.src == 192.168.232.215 and (udp.port == 5355 or udp.port == 137)
```


We tracked all responses from the rogue machine. The second unique destination IP was:


```
Second Victim IP: 192.168.232.176
```


>

*Q4: We suspect that user accounts may have been compromised. To assess this, we must determine the username associated with the compromised account. What is the username of the account that the attacker compromised?*


One next move: determine if the attacker obtained credentials from any of the victims.
We filtered for SMB authentication attempts:


```
ip.addr == 192.168.232.215 and tcp.port == 445
```


And bingo — we found an `NTLMSSP_AUTH` packet. Inside it:


```
Username: janesmith
```


This confirmed it. The attacker didn’t just throw bait — they got a bite.

>

*Q5: As part of our investigation, we aim to understand the extent of the attacker’s activities. What is the hostname of the machine that the attacker accessed via SMB?*


Finally, we traced the SMB connection back to the machine the attacker accessed using jamesith credentials.


In the NTLMSSP handshake and SMB session setup packet, we found


```
Hostname: ACCOUNTNIGPC
```


## 🔒 Conclusion: What We Learned


```
Item | Value
🧑‍ Victim 1 | 192.168.232.162
🎯 Rogue IP | 192.168.232.215
🧑‍ Victim 2 | 192.168.232.176
🕵️ Compromised User | janesmith
💻 Compromised Host | ACCOUNTNIGPC
```


## 💡 Mitigation Tips:


- Disable LLMNR and NBT-NS via GPO in Windows environments.

- Implement network segmentation.

- Deploy intrusion detection systems that catch Responder-style attacks.

- Enforce multi-factor authentication to reduce NTLM risks.

---

*Originally published on [Medium](https://infosecwriteups.com/cyberdefenders-write-up-poisonedcredentials-lab-network-forensics-a7b50a2a48af). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
