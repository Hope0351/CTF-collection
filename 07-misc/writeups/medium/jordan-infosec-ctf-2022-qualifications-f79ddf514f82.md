# :game_die: Jordan Infosec Ctf 2022 Qualifications F79Ddf514F82

> **Original Source:** [Jordan Infosec Ctf 2022 Qualifications F79Ddf514F82](https://xelessaway.medium.com/jordan-infosec-ctf-2022-qualifications-f79ddf514f82)
> **Platform:** xelessaway.medium.com | **Category:** `MISC` | **Year:** 2022

---

7- WH4T-TH3-H1LL ( Forensics — 300 Point )


300 Point!!! okay baby you are mine. in this challenge we got a memory dump so it’s time guys yes it’s time to use our favorite tool “ volaility “


so let’s check the profile of this dump


```

python vol.py -f memdump.raw imageinfo
```


well it’s “Win10x64_19041” so let’s continue our job. and see the process list


okay there are many process but I’ll focus on the “Winrar.exe” so let’s scan files and see if there are any zip or rar files we can dump.


```
python vol.py -f memdump.raw — profile=Win10x64_19041 filescan > files.txt
```


ohhh this is interesting. I found “Data.rar” so I’ll try to dump files on these files and see what will I get.


```
python vol.py -f memdump.raw — profile=Win10x64_19041 dumpfiles -Q [offsets] -D.
```


but sadly we couldn’t dump these files nothing appear in the directory. so we have to go another way. I tried mftparser and trying to find “data.rar”


```
python vol.py -f memdump.raw — profile=Win10x64_19041 mftparser > mft.txt
```


well well well for now we are good. we got our file :DD


really :’) another password. so we have 2 thoughts.
1st one password inside the dump


2nd one brute force


I’ve tried bruteforce but it will take long long long time so I know now we must go into the memory again to find that PASSWORD. so let’s see where can I find the password. maybe in cmd ? not there :/ maybe in history of browsers? nah not there too hmmmmm I asked the admin and he said where do u save the password. first I thought maybe it’s inside the broswer settings. but hmmm registry !!! how I forget that ! let’s check registry. using hivelist


```
python vol.py -f memdump.raw — profile=Win10x64_19041 hivelist
```


well well well we found the registries so as usual we google for where password are saved in registry


and now I know it’s in SOFTWARE so let’s dump that little one :DDD


```
python vol.py -f memdump.raw — profile=Win10x64_19041 dumpregistry -o 0xffffb586c1b0b000 -D.
```


so let’s open it in any registry viewer and see if we will find the password or not.


HELLO MY LITTLE FRIEEEEEEEND FINALLY WE GOT YOU.


Password : MySup3rS3kr3tP@ssw0rdJISCTF20202020


let’s extract and get the flag now :D


>JISCTF{M3M0RY_F0R3N$!C$_1S_FUNNY_2022}


- — — — — — — — — -+ — — — — — — — -+ — — — — +
| Challenge | Category | Points |
+ — — — — — — — — -+ — — — — — — — -+ — — — — +
| Easy101✔️ | Forensics | 50 |
| M4LD0C✔️ | Forensics | 50 |
| FitShing✔️ | Forensics | 100 |
| Strange✔️ | Forensics | 100 |
| Filterition-1✔️ | Forensics | 200 |
| Filterition-2✔️ | Forensics | 200 |
| WH4T-TH3-H1LL✔️ | Forensics | 300 |
| BL4CK-0R-WH1T3 | Steganography | 100 |
| C0MM0N 0R N0T | Misc | 100 |
+ — — — — — — — — -+ — — — — — — — -+ — — — — +

---

*Originally published on [Medium](https://xelessaway.medium.com/jordan-infosec-ctf-2022-qualifications-f79ddf514f82). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
