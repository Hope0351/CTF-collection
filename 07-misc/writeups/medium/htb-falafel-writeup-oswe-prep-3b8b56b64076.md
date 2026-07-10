# :game_die: [HTB] Falafel - Writeup (OSWE-Prep)

---

# [HTB] Falafel — Writeup (OSWE-Prep)

Falafel is a hard difficulty Linux box. Really good learning path for:

- SQLi (Boolean-based Blind)

- PHP Type Juggling Attack (Loose Comparison Weakness / Magic Hashes)

- Filename Truncation Attack to Upload a PHP Script

- Linux Framebuffer (`video` group privilege)

- Linux File System Debug (`disk` group privilege)

## Initial Recon

### Nmap

```
# nmap -Pn --open -T4 -sV -sC -p- 10.10.10.73Starting Nmap 7.80 ( [https://nmap.org](https://nmap.org) ) at 2021-04-10 20:40 EDT
Nmap scan report for 10.10.10.73
Host is up (0.081s latency).
Not shown: 65533 closed ports
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 7.2p2 Ubuntu 4ubuntu2.4 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 2048 36:c0:0a:26:43:f8:ce:a8:2c:0d:19:21:10:a6:a8:e7 (RSA)
| 256 cb:20:fd:ff:a8:80:f2:a2:4b:2b:bb:e1:76:98:d0:fb (ECDSA)
|_ 256 c4:79:2b:b6:a9:b7:17:4c:07:40:f3:e5:7c:1a:e9:dd (ED25519)
80/tcp open http Apache httpd 2.4.18 ((Ubuntu))
| http-robots.txt: 1 disallowed entry
|_/*.txt
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Falafel Lovers
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

- HTTP (80/TCP) — A FalafeLovers web page.

---
