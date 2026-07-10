# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/cscpsut-metactf25-qualifications-writeups-1974e9a7f03e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# CSCPSUT MetaCTF25 Qualifications Writeups


بسْمِ اللَّـهِ الرَّحْمَـٰنِ الرَّحِيمِ


Hello everyone, This writeup covers a selection of CTF challenges from the **PSUT MetaCTF Qualifications 2025**. The competition featured eight categories, but unfortunately, due to my not so good skills :p I was only able to solve a few. In this article, I’ll walk you through the challenges I managed to complete and explain how I approached them. Let’s get started!

## Warmup Category:


- **No Strings Attached**


This challenge is by far the easiest one, I downloaded the attached file which is just a ELF executable, then ran the strings command since the challenge name is “No strings attached”, I got the flag but only to realize that it needs some modification, the original flag from the strings command output was:


METACTF{HC3PT41N_HOBV1OUS_H1S_NOT_SHNOT_SO_HOBV1OUS}


Then i decided to remove the H letters in addition to the “SHNOT” string so it would make more sense ( I was lucky :D ) the final correct flag was:


METACTF{C3PT41N_OBV1OUS_1S_NOT_SO_OBV1OUS}


2.** Seizure**


After launching the instance I get a nc command to run to establish a connection, I ran the nc command followed with the domain and the port but got no output, so I decided to just head over to the domain:port in my firefox browser and got the flag straightaway.


Flag: METACTF{flaaaaaaaa yes this a flag}


3.** SkyFail: The Unfriendly Skies**


After launching the instance I get a link to the webpage and this was the front-end page:


Decided to open up Burpsuite and place in some random values and clicked on the “Submit to flight control” button to intercept the request, after intercepting it I sent it to the repeater to see what response it would give me and I get the flag in one of the response headers:


Flag: METACTF{SkyFail_is_the_best_airline_744aozc}

## Web Category:


- **Mongo Skies**


After starting the instance I get a link for a webpage with a login form, this was the webpage:


The first thing that came to my mind was obviously SQL Injection, but my friend Tareq caught a hint from the challenge name since it had “Mongo” in it I realized that this is a NoSQL Injection challenge.


## Get Qais Hammad’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I made a quick google search for some Injections to try for NoSQL and I tried the one from this site:


The Injection code I tried was this:


```
username[$eq]=admin&password[$ne]=foo
```


So I placed some random values, intercepted the request, modified the POST parameters which were “user” and “pass” like so:


The POST parameters before modification:
user=<anything>&pass=<anything>


The POST parameters after modification:


user[$eq]=admin&pass[$ne]=anything


Flag: METACTF{whoami03_zaky39ho}

## OSINT Catergory:


- **A Clownfish that is Cryptic**


Since the challenge didn’t provide me with any description, attachment or link I decided to search on google for his socials and i came across his github page:


[GitHub — CrypticClownfish/CrypticClownfish](https://github.com/CrypticClownfish/CrypticClownfish)


Searched his github thoroughly but couldn’t find anything until I clicked on his profile picture and something in the right bottom corner caught my eyes which was the flag written on the board.


Flag: METACTF{DONT_CROP_ME_BRO}


These are the challenges that I was able to solve, Thanks for reading.


[My Linkedin](https://linkedin.com/in/qaishammad)

---

*Originally published on [Medium](https://infosecwriteups.com/cscpsut-metactf25-qualifications-writeups-1974e9a7f03e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
