# :game_die: TCS Hackquest 5 - CTF Writeup

> **Original Source:** [TCS Hackquest 5 - CTF Writeup](https://infosecwriteups.com/tcs-hackquest-season-5-first-round-ctf-write-up-75c9ccbd3438)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

**Challenge No 4 : **Pandemic Inhibitor


**Flag:** hq5{HopeWeReturnToTheOldNormal}


**Points:** 400 (The only major challenge I got at that time)


**Description: **Vaccine manufacturers and POST requests were the only clues I got after reading it.


**Solution/Approach :**


1. In this, I got that we need to forward an API request externally, so I used postman for it as I had basic knowledge of it.


2. I used the parameters given in tcshackquest portal, the main directory of API parameters by locating to it. (below is the directory snippet)


3. Then I realized that I need to pass several parameters, like a SQL injection pattern.


4. Then, I used the earlier cookie, which we used for main login (for hackquest portal) as follows :


5. Finally, after the **Covaxin** value I got my flag and it showed me a doubtful warning when I used Pfizer vaccine as the value like (will it really cure it?) ***#atmanirbharbharat***

---

*Originally published on [Medium](https://infosecwriteups.com/tcs-hackquest-season-5-first-round-ctf-write-up-75c9ccbd3438). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
