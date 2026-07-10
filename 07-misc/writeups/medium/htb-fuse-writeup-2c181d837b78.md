# :game_die: HTB Fuse [writeup]

> **Original Source:** [HTB Fuse [writeup]](https://infosecwriteups.com/htb-fuse-writeup-2c181d837b78)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Fuse [writeup]


## Domain Controller Reconnaissance | Password-spraying | Brute-force attack | SeLoadDriverPrivilege Abuse


## Summary


*This machine drove me nuts! pwning this box would have been very difficult without the guidance of people who have already rooted this machine.*


With this machine, taking one step at a time is beneficial here. Run the nmap scan or keep scrolling below and you will know why :-) The NMAP result indicates its a Domain Controller. Initially, started with manual site inspection and captured all the publicly exposed data. Next, I used the gathered information against all the open ports services. After a lengthly process of reconnaissance/enumeration, password-spray attack and brute-force, I finally found an account that got me access to the shell.


For Root — once a vulnerability is identified, google search for its exploit and use it as a guide to exploit this machine.


*Note: Some tool may not provide a desired result. Hence, verify it by using another but similar tool and notice the output.*OS and Arch: Windows Server 2016 Standard 14393 (Windows Server 2016 Standard 6.3)


Tools & Commands Used: `nmap` | `cewl` | `msfconsole` | `smbclient` | `rpcclient` | `smbpasswd` | `wget` | `nc` | `evil-winrm.rb`

---

*Originally published on [Medium](https://infosecwriteups.com/htb-fuse-writeup-2c181d837b78). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
