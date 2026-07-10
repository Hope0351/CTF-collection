# :globe_with_meridians: DaVinciCTF - Web Challenges - Writeup

> **Original Source:** [DaVinciCTF - Web Challenges - Writeup](https://infosecwriteups.com/davincictf-web-challenges-writeup-517e77d6fa39)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# DaVinciCTF — Web Challenges — Writeup


This weekend, I had the pleasure to play the DaVinci CTF and score first place with my team FAUST. It was great fun and a good quality CTF with some nice and creative challenges.


Since we solved all challenges and web challenges are my favorite category, I decided to create writeups for all of them. The challenges are ordered by their points, feel free to skip the ones you solved.

## Obfuscation — 10 points and 318 solves


>

My password is my secret. You will never find it…
[http://challs.dvc.tf:5555/](http://challs.dvc.tf:5555/)
To validate this chall, please enter the secret code as the flag.


When we visit the website, we can see an input field to submit a secret. As we don’t know the secret, we first look into the source code of the webpage and see obfuscated Javascript.


With [JSnice](http://www.jsnice.org/) we can deobfuscate the code a bit and see the following.

*Deobfuscated Javascript*


I did not read all the code but only tried the first two lines of the testSecret function in line 37/38. The result is the flag, don’t ask me why :)


dvCTF{1t_is_n0t_4_secr3t_4nym0r3}

*When trying this function in the console it returns the flag*

## Authentication — 10 points and 265 solves


>

Can you find a way to authenticate as admin?
[http://challs.dvc.tf:1337/](http://challs.dvc.tf:1337/)


The second challenge is an SQLi challenge. We can see a login page with the goal to log in as admin.


Of course, we could try various SQLi techniques, but here, already the first SQLi textbook exploit works: *‘ OR 1==1--* as username logs us in as admin.


On the webpage, we don’t see a flag so we open the source code of the page with *ctrl-u *and find the flag as a hidden field at the bottom of the page.


```
<p style="visibility: hidden;">dvCTF{!th4t_w4s_34sy!}</p>
```


## Members — 66 points and 61 solves


>

Can you get more information about the members?

---

*Originally published on [Medium](https://infosecwriteups.com/davincictf-web-challenges-writeup-517e77d6fa39). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
