# :game_die: Sticky Notes - H@cktivityCon 2021 CTF

> **Original Source:** [Sticky Notes - H@cktivityCon 2021 CTF](https://infosecwriteups.com/sticky-notes-h-cktivitycon-2021-ctf-c0b6242a80fd)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

# Sticky Notes — H@cktivityCon 2021 CTF


I’m one of the 8 teams that was able to catch the flag for this challenge, if you tried to hack this and you didn’t can don’t worry I was very close to give up.


First of all, recon.


We have two services, authentication and sticky notes app. Later you will see that OAuth is a bit tricky (It gave to me a lot of headache).


*Sticky Notes App — Main*


*Sticky Notes App — Profie*


As always I started the recon creating an account and testing the main features of the app. Shortly I made to me a question, why the ctf creator put a feature for report problems in that platform? That doesn’t have sense… that service doesn’t have people working on in order to read my disturbing problems…


But… what about bots? Maybe they put some script that reads the problems, maybe I can execute some code there. Let’s try…


## Get Corraldev’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I wrote a simple xss payload and wait to get a request in my burp collaborator client.


*It’s a HeadlessChrome (What I supposed before)*


Okay, now we know that this part is vulnerable to XSS and we need to escalate to that account. So first thing I tried was to get more info about the context of the bot. Cookies, Path, Html of the vulnerable container..

*Script used to Steal Info from the Bot.*


Well first look shows that theres no cookies to retrieve and thats because the httponly flag, okay we can’t steal the session and impersonate it but… what about doing a xhr request and exfiltrate the content of the notes or the metadata of the account?

---

*Originally published on [Medium](https://infosecwriteups.com/sticky-notes-h-cktivitycon-2021-ctf-c0b6242a80fd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
