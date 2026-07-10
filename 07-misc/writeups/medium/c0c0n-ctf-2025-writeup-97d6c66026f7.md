# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/c0c0n-ctf-2025-writeup-97d6c66026f7)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

## 🔍 Step 3: Whispers in the Wire - The Hidden C2 Channel


The attacker exfiltrated an encrypted package. The brief mentioned they “repurposed a fundamental internet protocol” for secret communications. I knew this pointed to DNS tunneling — a classic technique for covert data exfiltration and C2.


I filtered the traffic for the attacker’s IP to focus only on their activity:


```
ip.addr == 203.0.113.10
```


Then, I specifically looked for DNS traffic involving this IP:


```
dns and ip.addr == 203.0.113.10
```


Scrolling through the packets, I quickly spotted an anomalous DNS query to `status.cdn-updates.test` requesting a TXT record. The domain name itself seemed suspicious—like a prearranged drop point.


The corresponding DNS response contained a TXT record with the value:
`K9p3-4vQx-72Bm-NEt1`


This was the decryption key delivered out-of-band via DNS — exactly as the brief described. The Shadow Snakes used DNS as their hidden command-and-control channel, bypassing traditional security monitoring that might focus only on HTTP traffic.

>

`*c0c0n-ctf{K9p3-4vQx-72Bm-NEt1}*`


## API Challenges: Fire Station 13 at Risk


### Uncovering the API Breach That Threatened Adversary City’s Emergency Response


### 🚨 The Crisis at Fire Station 13


Fire Station 13 stood as a symbol of strength and reliability in Adversary City — until their digital infrastructure became the target of a sophisticated attack. While firefighters battled blazes, a different kind of threat smoldered in their computer systems, where small oversights in their incident management application created catastrophic vulnerabilities.


## Get Sheldon Menezes’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The station’s seemingly ordinary shift assignment and incident logging tools had become the entry point for attackers. Exposed APIs provided a direct path to sensitive information: firefighter rosters, dispatch records, response times, and eventually, their secure communication system.

---

*Originally published on [Medium](https://infosecwriteups.com/c0c0n-ctf-2025-writeup-97d6c66026f7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
