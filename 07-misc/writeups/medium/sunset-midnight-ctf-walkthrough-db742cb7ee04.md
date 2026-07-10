# :game_die: Sunset-Midnight-Ctf-Walkthrough 🌄

> **Original Source:** [Sunset-Midnight-Ctf-Walkthrough 🌄](https://infosecwriteups.com/sunset-midnight-ctf-walkthrough-db742cb7ee04)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Sunset-Midnight-Ctf-Walkthrough 🌄


Today we are going to solve another boot2root challenge called “Sunset: Midnight”. It’s available at VulnHub for penetration testing. Here I Shreya Talukdar am presenting sunset midnight ctf walk through. Let’s get started and learn how to successfully break it down.


## 🐞 Penetration Testing Methodology


## Reconnaissance


▪️ Nmap

## Enumeration


▪️Hydra brute force MySQL service

## Exploiting


▪️ WordPress administrator’s password change
▪️ Modification of code to build a web shell

## Privilege Escalation


😎Misuse of recycled passwords
😎Binary abuse without fixed load path
😎 Capture the flag

## Usage !!


👻 With the use of nmap

### -sn 192.168.0/24


we first see the networks connected to the host. It is basically a ping scan
👻 After we get the vm’s ip(the vulnerable machine) we perform an aggressive scan with

### nmap -A

---

*Originally published on [Medium](https://infosecwriteups.com/sunset-midnight-ctf-walkthrough-db742cb7ee04). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
