# :game_die: WebGoat Admin lost password Challenge

> **Original Source:** [WebGoat Admin lost password Challenge](https://infosecwriteups.com/webgoat-admin-lost-password-challenge-3e2b317cc0e5)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# WebGoat Admin lost password Challenge


*WebGoat first challenge*


This is the first of four CTF-like challenges present in WebGoat


The challenge itself is not particularly complex but the process you have to go through is what’s important here


I have spent many hours trying to figure anything plausible on this challenge, [thehackerish](https://thehackerish.com/)’s video that you can find below has been my last resort just to be sure I was somewhat on the right track, since I have been trying to think about solutions in the realm of what I know is somewhat usual in security related CTFs, alas I was mistaken, but this helped me understand a lot about the mental process of figuring out possible solutions


To fully appreciate what it means to go through this particular challenge and every single possible aspect looking for vulnerabilities, I highly recommend watching this video from thehackerish *after* you tried the challenge by yourself

*thehackerish Admin Lost Password live hacking*I have to stress that this is a CTF challenge and it is not a usual real-life security vulnerability issue or a plausible security aimed CTF so stop reading if you do not want any spoilers and go solve it by yourself first


## Get PVXs’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s proceed, once the challenge page is loaded, go check Burp to see what happens during the process


*Burp history filters*


Enable logging for every possible MIME type


*Burp history requests*


Burp History will reveal the full extent of the loading process, of all these things, the ones highlighted in red arrows are loaded specifically for this challenge, the other seems to be shared between all of WebGoat (but this does not really mean anything though)
In particular:


- /WebGoat/Challenge1.lesson.lesson is the challenge page, a lot of HTML but not much interesting info

- /WebGoat/service/lessoninfo.mvc is invoked by the lesson page to get the contents, not much in there

- /WebGoat/challenge/logo is an extentionless PNG image file loaded for the challenge, while boss.jpg has been loaded in other WebGoat pages and it is not in a “challenge” directory


*Challenge page HTML on browser dev tool*


By checking the page HTML source, we can find the /WebGoat/challenge/logo in the lesson div

*logo PNG without extension*


The infamous logo image without file extention


I went over the Debugger dev tool and searched all page loaded files for admin/pass/password/login/username just to be sure but it did not show anything interesting


Then I started to look for admin/pass/password/login/username in the responses on Burp History, Burp is exceptional for this, just put your text on the search bar and click through the responses


*Burp search feature at its best*


And just like that, here we have username and password for this challenge


Login to the challenge page, you will be given the flag


This concludes WebGoat Admin lost password Challenge


I hope you liked it.


PVXs — [https://twitter.com/pivixih](https://twitter.com/pivixih)

---

*Originally published on [Medium](https://infosecwriteups.com/webgoat-admin-lost-password-challenge-3e2b317cc0e5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
