# :game_die: Bugcrowd’s Blackhat USA CTF - Writeup

> **Original Source:** [Bugcrowd’s Blackhat USA CTF - Writeup](https://4bh1-md.medium.com/bugcrowds-blackhat-usa-ctf-writeup-fc28adef7ea9)
> **Platform:** 4bh1-md.medium.com | **Category:** `MISC`

---

# Bugcrowd’s Blackhat USA CTF — Writeup


Hello, Everyone. I had some time recently, so I decided to solve a few interesting challenges in the Web Exploitation category of Bugcrowd CTF.

## Web


### Open Sesame


*Open Sesame Description*


The challenge gave us a web service called *Secure Note Service*. From the first look, it seemed simple — you log in and view your notes. Interestingly, I noticed it already gave me a User ID and some kind of ID value when I accessed it.


*Web Applicaiton Interface*

>

This one turned out to be about insecure cookies — basically, cookies are small pieces of data stored in your browser by the website, and if they’re not protected properly, changing them can give unintended access.


The first thing I did was open the browser’s developer tools (F12 → Application tab) to check the cookies. And there it was — a cookie that looked like it was storing my role as `user`


Insecure cookie handling means if the server doesn’t validate the cookie properly, we can modify it. So, I edited the cookie value from `user` to `admin`.


After refreshing the page… I now had admin access, and the flag was displayed right there.


Quick win, but a great reminder of why cookie validation on the server side is important — never trust client-side data blindly.

---

*Originally published on [Medium](https://4bh1-md.medium.com/bugcrowds-blackhat-usa-ctf-writeup-fc28adef7ea9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
