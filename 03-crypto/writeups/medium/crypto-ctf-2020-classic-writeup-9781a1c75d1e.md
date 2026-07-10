# :locked_with_key: Crypto CTF 2020: Classic Writeup. This is my first time joining a CTF…

> **Original Source:** [Crypto CTF 2020: Classic Writeup. This is my first time joining a CTF…](https://alexislingad.medium.com/crypto-ctf-2020-classic-writeup-9781a1c75d1e)
> **Platform:** alexislingad.medium.com | **Category:** `CRYPTO` | **Year:** 2020

---

# Crypto CTF 2020: Classic Writeup


*The view of the challenge from Crypto CTF 2020*


This is my first time joining a CTF that is purely focused on cryptography. As I saw the challenges, I was discouraged because most of the challenges are full of evil mathematics haha
This CTF is really extremely HARD (for me)…


There are 20 challenges overall and before this, what we just finished is the warm up and baby challenge…. and then this challenge which is categorized as “EASY” but only few got the flag and based on my experience, this is not really an easy one. Maybe a medium or hard one? haha
Well we just solved this 1 minute before the game ends (a buzzer beater indeed) but the score was not shown maybe because the scoreboard was freeze for the last 15 minutes?


So first here’s the encrypted text that we must decrypt in order to see or get the flag:


It is a group of five characters each. It took me several hours to find out that there are no existing encryption that by five characters but I noticed that there is this three character encryption called “Trigrams”. The title of the challenge is classic so basically, Trigrams is one of the candidate encryption method that I can use since it is also “classic” hahaha I hope I made sense.


For another few hours, I tried to use some already made tools online but it’s taking too long and sometimes the results are unreliable. So one hour before the CTF ends, I decided to code everything on my own (such a desperate moves haha). Well, I am a no programmer so I researched a lot of Trigram python script. I remove the spaces using: sed s/’\s’//g enc.txt > nospace


and then do the Trigrams bu the result of my script is unsatisfying but maybe it is not done yet. Maybe, the five character is just to lure us that it is a 3 character encryption but doesn’t mean we can find the flag there.


I am now in deep pressure, as in super deep pressure since there are only few minutes left. So I decided to continue my trigram script and combined it with frequency analysis because it is also classified as classic. I managed to google some frequency analysis script and an automated substitution since again, the tools online is loading forever or it is just my Internet haha


Here’s the final script that let me see the flag with a bit of manual substitution, you can now get the flag:


Here’s the result:


The flag is CCTF{The_main_classical_cipher_types_are_substitution_cipher}

---

*Originally published on [Medium](https://alexislingad.medium.com/crypto-ctf-2020-classic-writeup-9781a1c75d1e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
