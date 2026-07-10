# :game_die: HTB AD Track: Sauna Walkthrough

> **Original Source:** [HTB AD Track: Sauna Walkthrough](https://infosecwriteups.com/htb-ad-track-sauna-walkthrough-9aa9048b45b7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB AD Track: Sauna Walkthrough


Hello Everyone!! Here’s my writeup for the machine Sauna.


Let’s start scanning and enumeration using Nmap.


Command: nmap -sS -T4 -A -p- -oA <output_file> <target-ip>

>

-sS: TCP SYN Scan


-T4: Faster scan time


-A: Enables OS and version detection, scans ports using common nmap scripts for specific vulnerabilities and performs traceroute.


-p-: Scan all 65535 ports


-oA: Save scan in 3 file formats (.nmap, .xml, .gnmap)


<output_file>: Replace with a file name of your choice


<target-ip>: Replace with the given IP address of the target machine


Following ports and services are discovered:

---

*Originally published on [Medium](https://infosecwriteups.com/htb-ad-track-sauna-walkthrough-9aa9048b45b7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
