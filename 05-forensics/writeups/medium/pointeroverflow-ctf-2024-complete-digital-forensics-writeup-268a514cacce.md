# 🔍 PointerOverflow CTF 2024 — Complete Digital Forensics Writeup

---

## 📝 Full Writeup

PointerOverflow CTF 2024 — Complete Digital Forensics Writeup![Nathan

](/web/20250203085950/)

[Nathan](/web/20250203085950/)

·
[Follow](/web/20250203085950/)

·
Jan 25, 2025

[

](/web/20250203085950/)

--

Credits to: Professor Chad. R Johnson.
Hello, once again I am here to share my writeups! I hope that you’ll enjoy my writeup and please let me know if there is anything you’d like to share or critique!

Let’s start with the 1st challenge, which is the DF 100 — A Record of Events, for this challenge we’re tasked with finding data in a dead USB, should be easy enough.
DF 100 — A Record of Events

First let’s open the file in FTK imager for quick analysis.

We are immediately presented with some interesting data, so let’s see what this could be? I opened the file and it was the flag already, just need to extract what it’s saying cause he says it quite quickly.

I found a website that managed to get all the characters correctly, and there we have our flag! poctf{uwsp_57r4n63r_1n_4_57r4n63_14nd} — now that we have our flag, onto the next challenge!
DF 100 — A Flat Circle

Onto our 2nd challenge, here we are given an image and our goal is to find anything interesting on this image, spoiler it took me a long time and I learned a new technique specifically the Error Level Analysis which is apparently some sort of image forensics thing that some challenges have.

Well we have this image, and I tried a lot of things like binwalk, stegsolve, steghide, stegcrack, exiftool, checking HxD, nothing really popped up that was useful, I tried imagemagick too from mimeopen, nothing happened and I got stuck for a few days and found a website called “Forensically” which immediately solved it.

Goingi nto the error level analysis section, it immediately gave us this output and voila our flag. poctf{uwsp_7h3_m4n_1n_7h3_h16h_c457l3} — Now that we have our flag, onto the next challenge!
DF 100 — I’ve Been There Too

So now we’re given an sqlite database, now for this problem I used kali cause it already has a sqlite db reader, and now it’s time to do some digging.

So this is what we have, we see that there are quite a few pieces of data, let’s check out the browse data and see if there is anything useful.

I typed “ctf” in the name section and immediately got a hit, and so I just dug through it using the filter of /\w/ for any alphanumeric stuff and I managed to get this, it was just to make my life easier but here is the flag we got, poctf{uwsp_d0_4ndr01d5_dr34m} — now that we have our flag, lets go onto the next challenge!!
DF 200— Hooper Hollar

This challenge was quite a dupe, I really thought that it would have involved some memory forensics and diving deep into what was inside by maybe using volatility or some other tool, but after an unnecessarily long time of using volatility and receiving an error message, I just decided to use HxD to check if there was any semblance of the flag anywhere, and lo and behold.

This challenge was a little bit disappointing as I was looking forward to an actual memory forensics challenge, but it’s fine, we now at least have the flag poctf{uwsp_13353r_b31ng5} — now onto the next challenge!!
DF 200 — Known Unknowns

This challenge was a standard challenge that involves the use of audacity, we just have to check the spectrogram of the given wav image and we will get our flag.

Nice, we have the flag. poctf{uwsp_7h3_13f7_h4nd_0f_d4rkn355} — now onto the next challenge.
DF 200 — Never Met the Pieman

This time we are now given a .mov file, this challenge was quite something because I had initially thought that the challenge would be something insane like having to use ELA on each frame of the challenge or something like that, but it was way more simple after I started to try and solve it, I did the usual things like using exiftool, strings whatever, and as I went on and used HxD I managed to find the flag. If you’re familiar with how some encoded text looks like, this would be very easy for you to solve as well.

So yeah, that’s how we get the encoded flag for this challenge which is “cG9jdGZ7dXdzcF83MW0zXzNuMHVnaF9mMHJfbDB2M30=”, and after decoding we are given the final flag. poctf{uwsp_71m3_3n0ugh_f0r_l0v3} — now onto the next!
DF 300— It’s All in the Hips

Now we start with the first 300pt challenge, now we’re talking, we now have an actually fun challenge.

We have an interesting challenge, because we can see that there are deleted images so what I did was I extracted them all and checked some of the images out and wondered why some of them weren’t loading.

Compare two different images and looking at their headers, the right side file makes us crash (has our flag) and the left side one is an image of a screenshot I took awhile back.

So now that we realized that the files are corrupted, we just have to do a little bit of fixing, I tried fixing the headers of all the files and I managed to get the flag this way.

Nice, now we have our flag! poctf{uwsp_7h3_574r5_my_d3571n4710n} — nice, let’s move onto the next challenge!
DF 300 — Daily Doses

We now have our first interesting challenge, it’s a pcap forensics challenge that contains our flag, but it’s quite funny how the flag was stored, it wasn’t really something sophisticated moreso just a lot of digging to find the flag, which was some piece of encoded text again.

Well, this pcap was quite uninteresting to say the least, we now just have to dig to find any artefacts or packets that might contain our flag.

Gg now we have our encoded data, let’s just make a simple python script to decrypt it.

```
obf = "706F6374667B757773705F315F346D5F6C3336336E647D"
obf= list(bytes.fromhex(obf)) #Convert hex string to array of bytes

answer = ""

for i in obf:
 answer+= chr(i)
 
print(answer)
```

Once again, we have obtained our flag. poctf{uwsp_1_4m_l363nd} — now onto the next.
DF 300 — I’m a Stranger Here Myself

Another pcap hmm. I hoped that this would be annoying, but it turned out to be a very fun one to solve. I had just opened the pcap file and went directly to http/ftp-data to see if I could export any objects, and we could immediately see this.

Bingo, we have a lead, so what I did here was check their data first, and this immediately gave me an idea on how to solve this lol.

So we can see that this is a jpeg image with the “JFIF” text, so I assume that we just had to merge the JFIF with the other file and it would be fine, let’s try that with HxD and see if we can get the flag that way. It didn’t work — until I saw this goofy section of the header..

Yeah, the typical nonsense you can see in CTFs lol, deadbeef.. so I replaced that with just any working jpg header and managed to get the flag after merging both of the files (using raw bytes btw).

Nice, we have the flag now, poctf{uwsp_f34r_15_7h3_m1nd_k1113r} — onto the next challenge, the one that took a literal week to solve but the solution is so basic it made me choke.
DF 400 — No Irony in Rain

Now that were onto the last challenge, I’d like to thank Professor Chad R. Johnson for making all these wonderful challenges, and making this event possible, I really wish everyday that I had a professor like you, all your students are so lucky to have a wonderful professor with them.

With all that said and done— let’s get onto solving this challenge.

We’re presented with an absolute banger of an intro, it’s mostly a nonsensical video, I went into the discord to see if the Professor had dropped any hints, and he did mention that there was an easy way to solve it and a way to solve it that required advanced image forensic analysis, I had tried for weeks to do the image forensic analysis but I have no idea on how to do it, now it all comes down to understanding the challenge.

First, we have these context clues in the challenge description that were 100% the only way I realized the solution was really as simple as stated by the Professor.

I didn’t realize that it was that simple.. we basically have to check the comments/description to get our next clue, let’s go, we’re near, we just have to dig deeper.

So we have these two images to work on the challenge, I first realized something quite cryptic with what the message was, I assumed it had to involve something “Russian” or “Slavic”, so I tried translating the messages and I ended up not getting anything useful, and then I realized.. the video description has “xaxaxa” in it as well, so that would mean that the account was “used” by said attacker to leave a message behind, but what could we do to uncover that message? I checked the account of anali cause he has the same comment as the description below to see if there could be any leads, but there weren’t any, and then I realized.. it was the “Transcript” of the video — let me explain, most videos do not have this unless they were purposefully placed there or if someone submitted a transcript to the channel I believe, so the only possible thing was to check the transcript, we’re finally there, let’s just dig a little bit deeper, let’s go.

Nice one Prof, but that won’t stop me from solving this problem, after using dcode.fr to translate this piece of morse, we got a meaningless message, and then I realized and looked back onto this segment, hey, there is an option to change the language, and so I did. I changed the language to “Russian” as the assumed “attackers” were of originating from there.

Bingo, we have our final lead to this challenge, we can see the “Russian text -> QWERTY” and some semblance of a flag at 0:30 as well, so after realizing that I tried copy pasting the entire dialogue onto Google Translate, and it tells us to do this.

Okay bingo, we just need to use ChatGPT to solve it then, let’s see what will happen after we do that :).

YESSSSSSSSSS WE FINALLY HAVE THE FINAL FLAG!!!!!!!!!!!!!!! THE FLAG IS poctf{uwsp_50_17_6035} YESSSSSSSSSSSSSSSSSS!!!!!!!!!!!!!

Now that I’ve solved all of the challenges, the grind continues with more academic stuff and most especially progressing with the Soc Analyst Job role path in HackTheBox and also doing more CTFs, I played a bit in the KnightCTF recently and only managed to do a few problems in the “Networking” category. But yeah, thanks to everyone and my friend Mideno who did all the Reverse Engineering challenges, super shout out to him cause he taught me a lot of new stuff along the way!!

GGs. Onto the next CTF!!

---
