# :game_die: WebGoat Without password Challenge

> **Original Source:** [WebGoat Without password Challenge](https://infosecwriteups.com/webgoat-without-password-challenge-3a0f0c831ad9)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# WebGoat Without password Challenge


*WebGoat Without password challenge*


Second WebGoat challenge, we have to log in as Larry, let’s see what’s in here


The “Forgot Password” link is fake and not much in HTML source


Burp shows that, apart from the request to /WebGoat/Challenge5.lesson.lesson and its HTML, there is not much else when requesting the page


There is a /WebGoat/lesson_css/challenge6.css file loaded for the challenge but it does not have anything interesting inside


Let’s try to log in as Larry


*Login request on Burp*


Here’s the login request on Burp, and of course “password” is not the correct password


If username and password parameters are present but their value is missing in the request, the challenge will complain for the lack of input


If username or password parameter is missing altogether, we get error status code 400 — Bad Request


the “remember” parameter is optional both in value and in parameter presence


## Get PVXs’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


let’s see what happens by putting a single quote in


*Request with single quote in Burp*


We get a nice Java SQL exception


*Java SQL error*


And by checking the error, there we have the login SQL query


*Java SQL error with injection*


So yes we have SQL injection here


*Request with SQL injection and authentication bypass*


There you go, we have logged in as Larry and the response has a flag further down the feedback string


Put the flag in the lesson submit field and you are done


This concludes WebGoat Without password Challenge


I hope you liked it.


PVXs — [https://twitter.com/pivixih](https://twitter.com/pivixih)

---

*Originally published on [Medium](https://infosecwriteups.com/webgoat-without-password-challenge-3a0f0c831ad9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
