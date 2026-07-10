# :locked_with_key: [p0isonp4wn] Haxxor4.0 CTF Writeups

> **Original Source:** [[p0isonp4wn] Haxxor4.0 CTF Writeups]()
> **Platform:** medium.com | **Category:** `CRYPTO`

---

# [p0isonp4wn] Haxxor4.0 CTF Writeups


## Haxxor 4.0 is an Information Security Competition / Hacking Game Competition at U.P. Diliman held on July 6, 2019.


>

p0isonP4wn decided to split into two teams and named it p0isonp4wn A & p0isonp4wn B. At first we thought that dominating in haxxor4.0 is impossible due to lack of members and versatility plus the competition has categories that are not included in our area of expertise. Despite of difficulties, we are very lucky that we managed to secure 2nd and 3rd place from the competition.


*haxxor 4.0*


Following Writeups that are written here are selected challenges that we thought are new and fun to learn.


So I’m not gonna waste more of your time so let’s start !

## Challenge Write-ups


### 1. Unencrypted Chatter


>

*Category: Network*


We were given a .pcap file named `UnencryptedChatter.pcapng`


simple binwalk will show us 👇👇


*binwalk `UnencryptedChatter.pcapng`*


Opps ! 🤔 We Got a bunch of data inside the .pcapng file so lets try to extract it `root@kali# binwalk --dd=".*" UnencryptedChatter.pcapng`

*extracted files*


We have 201EB.zip file but we are unable to open it since it was a password protected zip. In this part we already knew that looking for a right password leads us to the flag.


Lets try to grep in recursive mode `root@kali# grep -rn password`


*grep -rn password*


We see that the word “password” does exist in some binary files so let’s use the strings and grep once again


`root@kali# strings * | grep password`


*passwords*


Oops 😲? We got 13 passwords here so we can tell that we have to bruteforce the zip file by these passwords in order to open it but first we need to clean out those unnecessary characters and decode each line to base64.


`strings * | grep password | sed 's/^.\{,9\}//' > password.txt`


Since I’m not a Linux expert, I deleted these characters “<%3D” manually (not proud of myself, apologies for being n00bz 😥)


Here is a simple python script to decode each line to base64 and store it to passwords.txt file


I named it p0isonp4wn.py and run `root@kali# python p0sionp4wn.py`


bruteforce zip file by this command


`root@kali# fcrackzip -v -u -D -p passwords.txt 201EB.zip`


password = golfhotel , extracting zip file gives us secret.png


*flag found!!!*

### 2. Try and Stop Them


>

Category: Network


In this challenge, we were given a .pcap file named `0x.pcap`


Opening the .pcap via wireshark displays👇👇


*0x.pcap*


Following UDP of the first packet 👇👇.


*UDP*


After seeing this, I can tell that the hex is actually a hex dump of JPEG image because of `ffd8ffe0`👈 obviously a file signature of JPEG image.


I can point out that the creator of the challenge wants us to export those hex that were split to all the packets and compile it to bin (Viewable JPEG image).


To get all the DNS queries , I found out that Tshark packet analyzer is the best tool for this.


```
tshark -Y "dns && dns.flags.response == 0" -T fields -e "dns.qry.name" -r 0x.pcap | cut -d '.' -f1 | tr -d '\n' > p0isonp4wn.txt
```


*p0sionp4wn.txt*


OK 🤩! So we did it 😂 next is compiling it to bin (Viewable JPEG image).


```
xxd -r -p p0isonp4wn.txt > p0isonp4wn.jpg
```


*p0isonp4wn.jpg*


BOOM!😂

### 3. ID the Target


>

Category: Forensics


We were given a file named `for_forensics.mem`


Throwing strings command with grep is always our first step in every forensics challenge 👇👇


`root@kali# strings for_forensics.mem | grep haxx4`

*strings*


What? 😲 oh yeah!


== incorrect flag !!!! ===


?😢 I thought that was a cheese 😭


but w8 ? haxx4{comm1t_t0_m3m0ry} ? 👈 this flag tells us that we should commit to memory , oh okay 👍


Now we decided to run Volatility memory forensic tool to analyze the memory file


`root@kali# volatility -f for_forensics.mem imageinfo`


Okay, we verified that it is actually a memory file so let’s dig more.

>

Memory Forensics is very new to us and we have not encountered such challenge before so we spent a lot in google and wasted 2 hours of our time . We started at* Volatility -h *to know all the plugins and fired it one by one but the result is hopeless until we visited this[link](https://infosecuritygeek.com/root-me-command-control/)


We knew that SYSTEM registry of Windows machine holds a wealth of information about the system. One of which holds the hostname of the machine so we decided to visit that part of the memory.


`root@kali# volatility -f for_forensics.mem --profile=Win7SP1x64 hivelist`


Copying the offset and then 👇


`root@kali# volatility -f for_forensics.mem --profile=Win7SP1x64 printkey -o 0xfffff8a000024010 -K 'ControlSet001\Control\ComputerName\ComputerName'`


Computer Name Looks like a flag so we try to enclose it to haxx4{}


flag = haxx4{1D3NT1FYT4RG3TS}


CORRECT FLAG! BOOM! That was a very tiring challenge 😆

## FINAL . . .


It was a good opportunity to compete in Haxx4 CyberSec Competition . It didn’t just gave us nice and memorable experience but also taught us new things as well . We admit that we still have a long way to go and a lot of things to learn so Team p0isonp4wn is open to listen for advises from professionals.

>

Contact me:


Facebook: [babyjamex](https://www.facebook.com/babyjamex)


Gmail*: p0ison.b1tches@gmail.com*


Discord: babyjamex#7781

---

*Originally published on [Medium](https://james-mercado-work.medium.com/p0isonp4wn-haxxor4-0-ctf-writeups-31ca7ce6570d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
