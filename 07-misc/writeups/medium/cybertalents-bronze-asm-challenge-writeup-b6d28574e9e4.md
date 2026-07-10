# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/cybertalents-bronze-asm-challenge-writeup-b6d28574e9e4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# [CyberTalents] Bronze ASM challenge writeup


## *Malware Reverse Engineering | Easy.*


This challenge comes with the description below, and “ASM_Par.asm” file that you can upload [here](https://hubchallenges.s3-eu-west-1.amazonaws.com/Reverse/ASM_Par.asm).

>

the flag is the parameter of the function in the following format ("FLAG{0_%X_0}" % parameter)


The simplest way to check the file before using any tool is a simple text editor, here’s the output :

*ASM_Par.asm*


Honestly It’s been a long time since I studied Assembly, I did some research to understand what every instruction does, and here’s what I found :


*fx description*


In other words, the function means to take the local variable stored in rbp-4 multiply it by 8 (left shift by 3) and compare the result with 5744.


Yes ! The parameter that we are looking for is the value stored in rbp-4, but how we are supposed to know it ? Simply suppose that **parameter*8=5744, **that makes the **parameter=718**.


Still have the message *wrong submission* popping up ? Easy, just have another look in the challenge description, it indicates that the format should be : **FLAG{0_%X_0}**, %X refers to Hexadecimal; As you can already guess the flag is …

---

*Originally published on [Medium](https://infosecwriteups.com/cybertalents-bronze-asm-challenge-writeup-b6d28574e9e4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
