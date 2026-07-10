# 🔍 ECTF 2025 — Complete Digital Forensics Writeup

---

## 📝 Full Writeup

ECTF 2025 — Complete Digital Forensics Writeup![Nathan

](/web/20250626055232/)

[Nathan](/web/20250626055232/)

·
Feb 3, 2025

[

](/web/20250626055232/)

--

1

So I participated in another CTF event, this one was quite fun and again it tested the limits of my knowledge, the first few challenges were fun and I could understand them easily as I’ve encountered similar problems before, but I just didn’t know how to get the data in some, so I had to delve into the world of scapy, photorec, and other registry keys that I wasn’t familiar with. Let’s get started, shall we?
**Challenge 1: **MY DEAREST

This was a nice challenge, but quite simple, we just have to find the last name of the person inside of the docx file, I’m not sure if there is a much more simple way of doing this, but I opened the document went to the “File” section to open the “Info” tab and saw the details here.

Funny enough, I did some testing and you could also do this, which is interesting, makes it a whole lot quicker too haha.

Welp, there’s our flag! ectf{MichelTeller} — now onto the next.
Challenge 2: JUST A PCAP

This challenge was very interesting, it took me a bit to realize how to solve it but I immediately knew what funny stuff was going on in this challenge, anyway, let’s get to solving.

We’re first tossed into this challenge with some clues already, we can see the “exfil” so we can assume it’s some sort of exfiltration, which it is some [DNS exfiltration](https://www.akamai.com/glossary/what-is-dns-data-exfiltration) which was easy to understand, we can see that there is some data there, so I was curious and did a little bit of experimenting.

Okay, we can see that the query name looks similar to a common file header that we see in CTFs, the sequence 8950 just rang some bells and then I went immediately into HxD, had to remove the last part though cause it won’t copy+paste successfully if I kept the .000.exfil.attacker.com.

Bingo, we know how to solve this now, it’s just a bunch of PNG data being sent with DNS queries, let’s see how we can solve this, I have a small clue that this involves the “scapy” library, I knew this because I’ve read a few writeups from other CTF players in old CTFs from when I was still an absolute beginner, but I guess information retention is quite something haha.

I went into their documentation and saw this, I tried googling for ways to extract only the data in the dns field name section but nothing came up, I went to youtube and found a very useful video from Sir Jadi, I’ve watched some of his reverse engineering writeups from old CTFs so it was nice to see his videos helping me out in an active CTF.

[https://www.youtube.com/watch?v=BePREXX1Lik&ab_channel=Jadi](https://www.youtube.com/watch?v=BePREXX1Lik&ab_channel=Jadi)

Well, skipping forward and trying to find the bits needed for our challenge, I found this, so I copied it and adjusted it a little bit so that the queried data would be stored inside of an array to make stuff a little bit easier for me, I did some cleaning at the end cause there would be some invalid inputs.

```
from scapy.all import *
import base64

# Read PCAP
packets = rdpcap("justapcap.pcap")
png = []

# Extract packet
for i in packets:
 if i.haslayer(DNS) and i[DNS].qr == 0:
 if i[DNS].qd:
 query_name = i[DNS].qd.qname.decode('utf-8').split(".")
 png.append(query_name)
 
flag = ""
for i in range(len(png)-2): #I just added -2 cause when I read the hexdump of the file there was some garbage below
 flag += png[i][0]

print(flag)
```

So this is the final script that I came up with, now let’s see the results that it would give us.

So we can see all the right characteristics of a PNG like the gAMA and pHYs section so yeah we can assume that what we did was correct, I went ahead and opened the file to get the flag and was greeted with this :).

Nice, we have our flag, ectf{DN5_3xf1ltr@t10n_15_f1nd3d} — now let’s move on to the next challenge!
Challenge 3: CAPTURE THE HIDDEN

So this challenge was quite simple as well, you’ll see instantly some suspicious data without even typing “http || ftp-data” into the search query.

We can see that the first packet is already quite interesting, and there is some text there that looks very suspicious.

Let’s just copy the hexdump of this thing and paste it on cyberchef, the data part looks just like a base64 string so let’s go.

Just convert it from hexdump and then copy paste to get the base64.

Then now just base64 decode and we have the flag, nice, we have the flag of ectf{P05t_1s_v3ry_345y_T0_F1ND} — let’s move on to the next challenge, it’s quite an interesting one.
Challenge 4: 3 QUESTIONS, 3 ANSWERS

This challenge took some time to understand, but in essence it was quite easy to understand it and I’ve been doing a lot of re-studying of the THM SOC 1 path so this was fun to do overall, kinda tested my knowledge of registry keys as well as ability to search for juicy information, so that’s nice too.

When we open the VM image, we’re immediately greeted with this, it’s very useful to know as well that FTK Imager does not actively read registry keys (to my knowledge) so I just went to System32 and extracted the config folder to get the registry keys.

So let’s export these files and start with the Registry exploration!

So we have this now, I did some looking in the other folders and found nothing of use, no clues, hints, etc, so now I’m fully focused on the registry keys.

So it took me quite some time to get a proper query, I was stuck with a lot of LSA secret documents and funny enough, “Enderman” a content creator for cybersec stuff was the one to help me which was so hilarious to me.

We can see the part that has like {“verison” : 1 “question: blah blah} part so I immediately went to this registry key to see for myself.

Bingo, we have our flag now ectf{LuluPraguePeter} — that was a fun one, but the next one is also quite interesting and I believe I’ve solved a similar question in last years CSAW or was it CISA CTF.
Challenge 5: WHERE WHEN HOW

So this one actually made me spend a few hours trying to figure out how to solve, because I was quite rusty with memdump CTFs, I forgot that you could just use strings to automatically solve these kinds of challenges, I went and tried to use VolatilityWorkbench (GUI ver. of Volatility3 framework) and it was such a pain in the ass trying to figure out how to extract the data, I didn’t know how to do it even after a few hours of watching and searching for content that could possibly help me, so I gave up and tried my luck by using “strings” initially, there was a lot of data and I immediately saw some stuff about “http” in the title and had a EUREKA moment, I just realized that it would be better to use “strings” and “grep http”. And thus, I did.

So nice, we finally have some interesting hits, let’s see if we can go deeper than this though.

I noticed that this had “airfrance” inside of the title, so I assumed that this would be the service that they would be using to book the tickets, since apparently in the challenge it mentions that his girlfriend bought the tickets without his knowledge to surprise, so I spend a couple minutes skimming and came up with this after seeing the value of “arrivalDate”

Nice we can see the data here with Budapest etc, I had some issues with the date at first but realized the return flight was the 2nd date necessary, so our final flag would be ectf{Budapest.2025/01/01–2025/02/22.Airplane} — now that we have our flag, let’s move on to the final boss!
Challenge 6: FIND MY FAVORITE CITY

So this challenge was the ultimate ultimate test for me, this one made me learn how to repair a broken usb image, and it also taught me how to use OpenSSL, it was my first time doing both of these so it took me almost half the day to solve this, enough talk. Let’s get into solving it.

Initially, what I had done with this challenge was I used foremost, binwalk, ftkimager, autopsy (SPOILER: with photorec, but it was so slow), none of these worked, but I realized that FTKImager and Autopsy showed some data, so this was a lot about file carving or at least data recovery, after searching for data recovery techniques

I searched for testdisk as this was one of the hits that I got first, but this did not work for me and was not what I used, I used photorec, I learned about photorec because they were part of the same installation so that really helped a lot. Anyway, we have this interface and basically have to extract from all sources.

This is what it would look like when it starts to recoup the data, it’ll take a few minutes and then you’ll be given some files after.

So this is the end of the file recovery, let’s get into Autopsy and do some digging.

This is the first thing that we see when we look at the users documents, something fishy already with the **secret_pass_salted** file that was deleted, I knew there was more to look for so I started searching deeper, it could be in that text file but it was only gibberish, I went digging and eventually found some juicy information after looking at the recently touched files.

So we can see here that there are some files that are linked, I checked each of them to see if there was anything useful starting above, and the first two hits were useless, then came the wallpaper that gave us this.

After finding the wallpaper, I extracted it and used exiftool and zsteg to get some juicy information.

So this was the result, we see that there is an aes-256-cbc key, well.. at least I thought it was, I spent so many hours trying to understand if this was actually an aes key since there was no “IV” to be located, but whatever, I looked at the salted file next to see how to solve it.

I opened the secret_pass_salted file into HxD and saw the “Salted__” section of the file, and I was interested in this, cause I believe I have seen this in other CTFs as well, so it was something to look out for. And after some googling, I found out that it was an “OpenSSL” encrypted file, so now I have to dig even deeper.

Realization hit me like a truck after digging around for almost an hour on github relating to OpenSSL topics, this was apparently a bruteforcer for OpenSSL, but he didn’t use -k -iv at all, he just used -pass, so I was thinking.. hmm.. what if this is just the password? Since there was no “IV” that was provided, so I tested it and then…

LETS GOOOOOOOOOOOOOOOOOO FINALLY I GOT THE FLAG!! (technically :P).

Now we have our flag, ectf{Kozlany} — THANK GOD!!

I have to say, this CTF was one of the most fun ones that I’ve played, I also had a lot of new lessons in this CTF, I thank the staff at ECTF for making this CTF experience amazing and for the staff member Greg to basically not tell me to give up! I hope to play this event again next year, stay tuned for more future writeups!

---
