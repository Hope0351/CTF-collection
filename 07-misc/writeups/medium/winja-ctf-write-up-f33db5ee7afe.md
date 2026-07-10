# :game_die: Winja Ctf Write Up F33Db5Ee7Afe

> **Original Source:** [Winja Ctf Write Up F33Db5Ee7Afe](https://infosecwriteups.com/winja-ctf-write-up-f33db5ee7afe)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Today I participated in Winja CTF, It was a really Awesome Experience.


I was able to solve 7 challenges so here I am sharing my approach to solve them.

## 1. Liar Liar


The first thing I did was check “file” command itself.

*file*


So it’s ASCII text file.


so I tried cat this_is_a_binary


*cat file*


So in img src, we can see we have one base64 string. So next thing I did was decode it using base64


*base64*


So we got HEX value.


so next thing i did was “HEX to ASCII”

*hex to ascii*

>

Flag : flag{8su3nsh_HONESTY_is_the_Best_Policy}


## 2. ZIP BOMB


So I download attachment,


So it was a zip file so I extracted it one by one while extracting the 2nd zip file we need to give a password so I guessed the password “pass123” and my guessing was right. else I will do zip password cracking online using “ilostmypass.com”


The next step is to open flag.txt file


>

Flag : flag{n0t_as_g0od_as_middl3_0u1_righ1}


## 3. F@#$ YOUR MIND


we have been given one txt file. it looks like this


At first look, I know this is javascript obfuscator code ( As you play more CTF you can surly predict things by just looking them)


So I used “[https://lelinhtinh.github.io/de4js/](https://lelinhtinh.github.io/de4js/)” to deobfuscate.


In challenge they told us to put string in “flag{}”

>

Flag:flag {cr@zy-e50t3r1c-l@ngu@g3_ejsSoOM7bh_MyNameIsDrLeamas}


## 4. Attack.log


we have been given one pcap file.


## Get Raj Upadhyay’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The first thing I did was exported all the files. (Export HTTP object list)


So as we can see we have 3 files. one “Linux-virus” file and two HTML files


So I tried strings on linux-virus file.


In the above image, you can see I have highlighted some Hash values,


At first look, it was strange to see HASH values in strings. So I tried to crack this HASH value via CRACKSTATION. and i was right it’s HASH value and got value “999999”


So now I opened HTML files and try to find “999999”


I found “999999” on the HTML file and I submitted a flag value.

>

Flag : flag{ZDBKEPXZQUECXDVJT}


## 5. Risk Aversion


We have been given one exe file.


So first thing i did was “File” command on exe


So we can see it’s not an exe file it’s ASCII text file.


So next thing I did was “cat format-c.exe”


>

Flag: flag{QKHek1Oblm_MrGrinnyWouldLikeToCongratulateYou}


## 6. Trader’s Gambit 1


*trader’s Gambit 1*


So firstly I visited this website


*bank.site*


So looked at different things “source code”,”javascript file”,”css” etc.


After then I thought let me try different URLs like “/admin,/login,/robots.txt”.


After a while, I tried “/flags” and I got 2 flags.

*flags*


So the First flag was for this challenge.

>

Flag : flag{YouFoundKorla_SqlInjectionSuccessful}


## 7. Trader’s Gambit 2


So when I saw the URL, it’s was the same URL so in previous challenge we found 2 flags so the 2nd flag was for this challenge.

>

flag : flag{LimitBypassed_IVFfxMQQwb_ThisAccountBelongsToKorla}


Thank you for reading.


You can find all resources at the link below.


[https://github.com/raj1997/CTF-Write-up/tree/master/Winja_CTF](https://github.com/raj1997/CTF-Write-up/tree/master/Winja_CTF/)

---

*Originally published on [Medium](https://infosecwriteups.com/winja-ctf-write-up-f33db5ee7afe). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
