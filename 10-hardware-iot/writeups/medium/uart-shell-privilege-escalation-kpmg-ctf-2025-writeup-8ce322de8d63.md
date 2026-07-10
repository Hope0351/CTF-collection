# :electric_plug: UART Shell Privilege Escalation - KPMG CTF 2025 Writeup

> **Original Source:** [UART Shell Privilege Escalation - KPMG CTF 2025 Writeup](https://infosecwriteups.com/uart-shell-privilege-escalation-kpmg-ctf-2025-writeup-8ce322de8d63)
> **Platform:** infosecwriteups.com | **Category:** `HARDWARE / IoT` | **Year:** 2025

---

# UART Shell Privilege Escalation - KPMG CTF 2025 Writeup


## Challenge Overview


**Challenge**: KPMG UART Shell
**Category**: Hardware
**Objective**: Extract the flag from a UART interface with restricted permissions

## Initial Analysis


The challenge presented a basic UART shell with three files available:


- `firmware.bin`

- `readme.txt`

- `flag`


Attempting to read the flag directly returned an access denied error with a crucial hint:


```
Access Denied: Insufficient permissions
developer access is required
```


## Solution Path


The error message pointed directly to needing developer access. Testing various privilege escalation commands led to discovering the `devmode` functionality.


## Get Sheldon Menezes’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

## Key Steps:


- Enable Developer Mode


```
uart> devmode on
Developer mode enabled.
```


2. Read the flag


```
uart> read flag
KPMG_CTF{PgXeg5m6YvviRZDZfNGXB-LiyY2qvKTYDnzkLFYDBLLylhfcl0FPTfQLUMQG1sUYmACBdAnbvKIZWas6onEBrIC7vLnRzuVeb2_o5qXY}
```


## Key Takeaways


- Error messages often contain valuable hints that the “developer access is required” message directly indicated the solution path

- Simple commands can hide powerful functionality as here `devmode` was the key to privilege escalation

- UART interfaces frequently contain debug features that can be exploited for access


*Image of the solved challenge*

---

*Originally published on [Medium](https://infosecwriteups.com/uart-shell-privilege-escalation-kpmg-ctf-2025-writeup-8ce322de8d63). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of hardware / iot CTF writeups.*
