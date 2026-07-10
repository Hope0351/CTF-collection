# :game_die: Password-Checker CSAW CTF 2021 Write-Up

> **Original Source:** [Password-Checker CSAW CTF 2021 Write-Up](https://infosecwriteups.com/password-checker-csaw-ctf-2021-write-up-8949dd62c948)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

# Password-Checker CSAW CTF 2021 Write-Up


This is a warm-up challenge for Binary Exploitation.


Downloadable file is 64-bit binary file which is not stripped.


Using checksec we can analyze the binary file.


After making the file writable we can execute it.


We have to enter the correct password to get in. I tried “charlie” for first time and no luck.


Then I tried “password”, it worked but there is no sign of any flag.


So we have to check the binary file how it works.


I used Ghidra to open the binary file and analyze the functions.


On analyzing the functions, main function calls a function called password_checker.


String comparison is happening that’s why “password” got accepted. But there is vulnerable function is this program which is gets().


When we open gets() man page, it gives us a warning to not use this function because gets() will store characters past the buffer allocation which will lead to Buffer-Overflow vulnerability.

---

*Originally published on [Medium](https://infosecwriteups.com/password-checker-csaw-ctf-2021-write-up-8949dd62c948). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
