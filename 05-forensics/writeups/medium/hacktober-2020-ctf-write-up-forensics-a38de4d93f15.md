# :mag: Hacktober 2020 Ctf Write Up Forensics A38De4D93F15

> **Original Source:** [Hacktober 2020 Ctf Write Up Forensics A38De4D93F15](https://sumb0dy.medium.com/hacktober-2020-ctf-write-up-forensics-a38de4d93f15)
> **Platform:** sumb0dy.medium.com | **Category:** `FORENSICS` | **Year:** 2020

---

## Public Service (Bonus Challenge)


>

“There is a flag associated with the malicious process from *Evil Twin* on a popular site used to check malware hashes. Find and submit that flag.”


This is related to the malware you find in the Evil Twin challenge. I didn’t solved the Evil Twin challenge, but a quick summary is identify which process was duplicated to look legit. You can tell that is explorer, because once you use volatility to see where processes are coming from, there is one explorer process coming from a different path than the others.


So we know the malware is called explorer.exe . First thing we want to do is to somehow extract this file from the memory dump so we can hash it. As the challenge description mentions, we are using a popular site to check the malware hash ( Virus Total !). Volatility is the best tool for linux out there when dealing with raw memory dumps.


It has this great plugin called procdump, which allow us to extract any processes executable/files in a memory dump file.


We first run a *psscan* and grep for explorer so we can find all explorer.exe processes in the dump. This also give us their PIDs so we can use it to extract it (and important info for future challenges). Now, we can use *procdump* and extract each PID, in this case: 6096, 3100,5448,2316 . We see that 3100 fails, but that’s okay.


Now that we have all the explorer.exe executable, we can hash them all. Once we have their md5sum, it’s just as easy as copying the hash and going to virus total to see if any malware matches the same hash.


We found it! But that not the flag. Always look for information about the malware in Virus Total, and I notice there is 2 community comments on this particular malware.


One of the comments is the flag itself !


flag{h4cktober_ctf_2020_nc).


Now that we have most of the information about this malware, the other challenges in the forensics category becomes easier to deal with.

---

*Originally published on [Medium](https://sumb0dy.medium.com/hacktober-2020-ctf-write-up-forensics-a38de4d93f15). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
