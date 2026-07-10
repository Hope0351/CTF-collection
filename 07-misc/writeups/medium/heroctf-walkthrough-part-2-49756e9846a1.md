# :game_die: HEROCTF WALKTHROUGH part-2

> **Original Source:** [HEROCTF WALKTHROUGH part-2](https://infosecwriteups.com/heroctf-walkthrough-part-2-49756e9846a1)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HEROCTF WALKTHROUGH part-2


After completing of our first forensic challenge we go to the part two .In this second part our challenge is to find the plaintext format of the username and password.


First we need list all hive address.


To find the username and password we need another hive address from the hivelist. Here we use this \SystemRoot\System32\Config\SAM hive address to find username and password. The SAM (Security Account Manager) is a database used in windows XP, Windows Vista, Windows 7, 8.1, and 10 that stores users’ passwords


## Get BlackMamba’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So we know that all the hashes are stored in SAM.so we dump all the hashes to a txt file


Yes, we have done it, our hashes are stored in herohash.txt.Then the next step is to crack the hash. We know that Windows systems are used LM and NTLM algorithms to encrypt the user passwords


Here I am using the [https://crackstation.net/](https://crackstation.net/) to crack the password. The crack station is a powerful hash cracking online tool.


Yes , we crack it. The final flag is


Hero{Razex:liverpoolfc123}


THANK YOU;

---

*Originally published on [Medium](https://infosecwriteups.com/heroctf-walkthrough-part-2-49756e9846a1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
