# :game_die: InCTF pro finals 2021: Look deeper writeup

> **Original Source:** [InCTF pro finals 2021: Look deeper writeup](https://infosecwriteups.com/inctf-pro-finals-2021-look-deeper-writeup-8f2333576f48)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

# InCTF pro finals 2021: Look deeper writeup


Hello Hackers!!! I am back with another forensic write-up this time. InCTF professionals finals 2021 happened this week. Challenges were pretty good and difficult to solve. But somehow we managed to get the first position this year.


Ok, Let’s solve this forensics challenge


>

Challenge file: [https://github.com/UVvirus/ctf_files-inctf-pro-finals-2021](https://github.com/UVvirus/ctf_files-inctf-pro-finals-2021)


If we open the given pdf there is some base64 encoded data and a key


Decoding it gives this

>

e3yn_7kd_v0_sn4z_gc7_hu3yzt


Hmm…still it isn’t in readable form


Ok, let’s get into this afterwards.


Let’s try pdfid.


Looking at the output we don’t get anything interesting. So let’s try pdf-parser


Wow!!! we got something.
In object 1 we can see the name called chall_dsound.wav, but as per the Reference it’s in Object 7
so Let’s navigate to Object 7


It references Object 8


OK, By seeing the /Length and /Type we can conclude that there is some data is present in here.


Let’s dump the object

>

./pdf-parser.py -o 8 — filter — raw -d dump_obj_filename chall_file.pdf


Let us examine the dump file using file command


When using file command it says that it is a wavfile.


So what happened until now is we extracted an audio file from a pdf file.


## Get Yuvarajan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


But still, now we haven’t got the flag


So I tried a few things like strings, binwalk, morse code, sonic visualizer on that wavfile but again got nothing.
seems like a dead-end…


But then after hours of researching, I found this nice write-up.

>

[https://ctftime.org/writeup/9638](https://ctftime.org/writeup/9638)


From this writeup, I downloaded the tool and opened the file in it.


But here is another twist. The flag is password protected


To find the password recall the first step, there was some base64 encoded text is present in the pdf file.


Decode it and put it in the vignere cipher with the key INCTF

>

password: w3ll_7ry_n0_fl4g_bu7_us3ful


you’ll get the password


Now open the wavfile in the deepsound tool, you’ll get the flag.zip


By Extracting the zip file we will get flag.png


But!!!! this file is corrupted


By looking at the hex we can see that it contains both jpeg header and png header


Removing the jpeg header will give us the flag.


END CREDITS:


Thanks to my amazing teammates


[https://www.linkedin.com/in/gokulavasan-p-ba24a0211/](https://www.linkedin.com/in/gokulavasan-p-ba24a0211/)

---

*Originally published on [Medium](https://infosecwriteups.com/inctf-pro-finals-2021-look-deeper-writeup-8f2333576f48). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
