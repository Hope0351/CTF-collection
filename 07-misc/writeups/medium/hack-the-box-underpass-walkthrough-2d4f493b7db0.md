# :game_die: Hack The Box - UnderPass Walkthrough

---

*credit — hac kthebox*

# Hack The Box — UnderPass Walkthrough

This is how I hacked underpass machine easily and how can you do that yourself

I began the challenge by conducting a TCP scan using `nmap` to find open ports, but it yielded no valuable results. Switching tactics, I tried brute-forcing directories with ffuf, followed by an attempt to brute-force subdomains. Unfortunately, both approaches led to dead ends.

With no significant progress, I turned to UDP scanning:

### NMAP SCAN

nmap -sS -sU -p- underpass.htb

┌─[root@parrot]─[/home/cryptoknights]
└──╼ #nmap -sS -sU -p- underpass.htb
Starting Nmap 7.94SVN ( [https://nmap.org](https://nmap.org) ) at 2025–02–05 13:42 IST
Stats: 0:01:29 elapsed; 0 hosts completed (1 up), 1 undergoing SYN Stealth Scan
This revealed UDP Port 161 (SNMP) was open. To probe further, I ran the following command:

```
This revealed UDP Port 161 (SNMP) was open. To probe further, I ran the following command:
```

### snmpwalk

*snmpwalk -v 2c -c public underpass.htb*

---
