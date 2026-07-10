# :game_die: Hacking Headless on Hack The Box: OSCP Prep

---

# Hacking Headless on Hack The Box: OSCP Prep

Recon, exploitation, privilege escalation.

🔥FREE VERSION — Free Article 🔥

*Headless*

Welcome back. This time we’re going to take a shot at Headless. This is an Easy box on the hackthebox platform.

## 01. Recon

As with most boxes, we usual want to start by adding the domain to our /etc/hosts file to avoid DNS problems and so that we won’t run into any problems visiting the web application (if there is one).

```
sudo nano /etc/hosts

127.0.0.1 localhost
127.0.1.1 kali
::1 localhost ip6-localhost ip6-loopback
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters

10.10.11.8 headless.htb
```

Let’s begin by checking open ports with nmap as per usual:

```
$ nmap -sC -sV -A 10.10.11.8 -p 22,5000
Starting Nmap 7.95 ( https://nmap.org ) at 2025-03-02 16:23 EST
Nmap scan report for 10.10.11.8
Host is up (0.056s latency).

PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 9.2p1 Debian 2+deb12u2 (protocol 2.0)
| ssh-hostkey:
| 256 90:02:94:28:3d:ab:22:74:df:0e:a3:b2:0f:2b:c6:17 (ECDSA)
|_ 256 2e:b9:08:24:02:1b:60:94:60:b3:84:a9:9e:1a:60:ca (ED25519)
5000/tcp open http Werkzeug httpd 2.2.2 (Python 3.11.2)
|_http-server-header: Werkzeug/2.2.2 Python/3.11.2
|_http-title: Under Construction…
```

---
