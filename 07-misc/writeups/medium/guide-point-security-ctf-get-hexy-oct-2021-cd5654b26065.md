# :game_die: Guide Point Security CTF - Get Hexy (OCT 2021)

> **Original Source:** [Guide Point Security CTF - Get Hexy (OCT 2021)](https://infosecwriteups.com/guide-point-security-ctf-get-hexy-oct-2021-cd5654b26065)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

# Guide Point Security CTF — Get Hexy (OCT 2021)


*GetHexy - GuidePoint Security CTF OCT 2021*


In the Misc Category of Guide Point CTF which was going on from October 12th to October 18th 2021, there was a challenge called “Get Hexy”. let’s solve this challenge.


First, try to run file command on this


it’s just simply zip archive. I use unzip to extract file inside of *hexy.zip*:


we are given a corrupted zip file. let’s use exiftool if we get any metadata on this file


oh! at the end of output, we get File format error.


try to use zipdetails todisplay the internal structure of zip files:


try to use hexeditor on this file:


if you’ll notice at the very very top of the file, the hexadecimal side on left and kind of the ASCII side on right, it’s just starting the file with “70 4b 03 04”. A regular PKZIP archive file should be starts with “50 4b 03 04”. we must to modify 70 to PKZIP archive file header magic bytes (50).


save this file. unzip file and it’ll go ahead and ask for password.


now, we must to crack this file. we can use two methods to crack this file.


## Get Aydin Naserifard’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


1) using tool called “john the ripper”:


first, we’re going to use the zip2john tool to convert the zip file into a hash format that John is able to understand, and hopefully crack.


*content of hex.txt*


I used many wordlists and spent about 12 hours to find a wordlist that helped me to found the correct password! The password found is *forgetfulness*.


you can download “cain and able” wordlist from S[ecLists repository](https://github.com/danielmiessler/SecLists/tree/master/Passwords/Software).


2)using tool called “fcrackzip”:


Unzipping it gives us a file called flag which contains the flag of this challenge


and the challenge flag is:

>

GPSCTF{871daf25893451d1ea8ba3b6736cce52}


hope you enjoyed this write-up.

---

*Originally published on [Medium](https://infosecwriteups.com/guide-point-security-ctf-get-hexy-oct-2021-cd5654b26065). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
