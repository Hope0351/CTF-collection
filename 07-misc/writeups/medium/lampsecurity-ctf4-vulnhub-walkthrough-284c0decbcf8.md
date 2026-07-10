# :game_die: LAMPSECURITY: CTF4 [Vulnhub] Walkthrough

---

# LAMPSECURITY: CTF4 [Vulnhub] Walkthrough

Hello, friends I'm Sudeepa Shiranthaka and I’m here with another CTF challenge. This called LAMPSECURITY ctf4 and it’s a boot to root beginner-level challenge. You can find this box from [Vulnhub](https://www.vulnhub.com/entry/lampsecurity-ctf4,83/).

### Methodology

- Network scanning and enumeration

- Surfing the HTTP port 80 service

- SQLMAP scanning

- Retrieve user data from the database

- Log in to the target machine via SSH

- Exploiting the target by using SUDO binaries

- Escalate the root privileges

### Network scanning and enumeration

First, we scan the network for getting the target IP. You can use netdiscover for that.

*figure 1-Network scanning with netdiscover*

After getting our target then, scan the network for finding open ports and services through Nmap. We will be able to find open ports for port 22(SSH), port 80 (HTTP), port 25 (SMTP).

---
