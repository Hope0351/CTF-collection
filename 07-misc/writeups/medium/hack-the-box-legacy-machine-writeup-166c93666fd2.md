# :game_die: Hack The Box: Legacy Machine Writeup

---

Legacy is one of the great beginner-friendly machines if you wish to practice finding and exploiting SMB vulnerabilities on a Windows system.

At the beginning, we know only one piece of information that the target is a Windows system, which already gives us some direction. Let’s begin with the enumeration phase and take a look at the exposed services.

## 🔍 Enumeration

Let’s begin with a basic port scan using Nmap. I saved the target IP in the `legacy` variable.

```
nmap -p- $legacy

Starting Nmap 7.95 ( [https://nmap.org](https://nmap.org/) ) at 2025-04-18 11:05 EDT
Nmap scan report for 10.10.10.4
Host is up (0.053s latency).
Not shown: 65532 closed tcp ports (reset)
PORT STATE SERVICE
135/tcp open msrpc
139/tcp open netbios-ssn
445/tcp open microsoft-ds

Nmap done: 1 IP address (1 host up) scanned in 50.58 seconds
```

After scanning all the ports, we can notice that ports 135, 139, and 445 are open. Based on this alone, we can conclude that the system is most likely to have SMB installed on it. Let’s dig deeper.

```
nmap -sCV -p135,139,445 -A $legacy
Starting Nmap 7.95 ( [https://nmap.org](https://nmap.org/) ) at 2025-04-18 11:07 EDT
Nmap scan report for 10.10.10.4
Host is up (0.053s latency).

PORT STATE SERVICE VERSION
135/tcp open msrpc…
```

---
