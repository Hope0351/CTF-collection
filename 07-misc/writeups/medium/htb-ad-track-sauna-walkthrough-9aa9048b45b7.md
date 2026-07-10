# :game_die: HTB AD Track: Sauna Walkthrough

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
