# :game_die: SolarDisruption Lab Writeup (CyberDefenders)

> **Original Source:** [SolarDisruption Lab Writeup (CyberDefenders)](https://infosecwriteups.com/solardisruption-lab-writeup-cyberdefenders-65c631272d58)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

>

*Q5: After completing host discovery, adversaries typically conduct a port scan to identify potential vulnerabilities and determine their attack surface.
How many ports did the attacker scan on each of the discovered hosts?*


we need to know how many ports were scanned on EACH host!


By filtering with the attacker's ip address and all other 7 ip’s we’ve got like this filter for example:


as he is making port scanning, so this is the right way to filter, by looking to the conversations between these ip addresses, we can find that it has 1000 TCP connections with destination ip address “192.168.228.136”. if you changed the filter by changing the ip.dst value to any of the 7 ip addresses we have, you'll find the following statistics :

*Sample*


192.168.228.1 -> 1000 TCP connections


192.168.228.2 -> 1000 TCP connections


192.168.228.136 -> 1000 TCP connections


192.168.228.137 -> 1021 TCP connections


192.168.228.138 -> 1162 TCP connections (most traffic)


192.168.228.254 -> 1000 TCP connections


## Get Loay Salah’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


conclusion: the attacker’s port scan number are quite obvious, just 2 of 7 ip addresses have more than 1000, it also means that the most traffic with more than 1000, may be the attacker could communicate with him lobger, so we may think he found an open port also!!

>

Answer5 → *1000*

---

*Originally published on [Medium](https://infosecwriteups.com/solardisruption-lab-writeup-cyberdefenders-65c631272d58). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
