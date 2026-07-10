# :game_die: HTB: Business CTF 2024 - Tangled Heist

---

# HTB: Business CTF 2024 — Tangled Heist

Difficulty: Easy

### Assets

[capture.pcap](https://github.com/sigee/CTF/blob/main/HackTheBox/business-ctf-2024/forensics/01_tangled_heist/assets/capture.pcap)

### Description

The survivors’ group has meticulously planned the mission ‘Tangled Heist’ for months. In the desolate wasteland, what appears to be an abandoned facility is, in reality, the headquarters of a rebel faction. This faction guards valuable data that could be useful in reaching the vault. Kaila, acting as an undercover agent, successfully infiltrates the facility using a rebel faction member’s account and gains access to a critical asset containing invaluable information. This data holds the key to both understanding the rebel faction’s organization and advancing the survivors’ mission to reach the vault. Can you help her with this task?

### Enumeration

*capture.pcap*

*Protocol Hierarchy*

The provided file contains network traffic from different protocols, more specifically:

- LDAP traffic of a Windows Active Directory environment (port 389)

- KRB5 (port 88)

### Tasks

[1/11] Which is the username of the compromised user used to conduct the attack? (for example: username)

*Wireshark filter: ntlmssp.auth.username*

Answer: Copper

---
