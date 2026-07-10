# :game_die: WebGoat Without account Challenge

> **Original Source:** [WebGoat Without account Challenge](https://infosecwriteups.com/webgoat-without-account-challenge-9abbeaf4ba44)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# WebGoat Without account Challenge


*WebGoat Without account Challenge page*


From the interface I guess I should try to vote so let’s try it by clicking on the stars

*Nope!*


We get a clear response on the page


*Request and response on Burp*


And on burp we get the same message


## Get PVXs’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Send the message to Burp Repeater and try to see if there is a /login /log endpoint, but there is none


*PUT request, Nope! again*


So let’s try to change the request method, here it is the PUT method, no go


*POST request, Nope! again again*


Here is the POST method, no go


*OPTION request, some interesting info*


With a OPTIONS request, we get the available methods on the “Allow” response header but no success message, so next up I guess is HEAD method


*HEAD request and goal*


And with a HEAD method we get a flag to submit in the lesson page


This concludes WebGoat Without account Challenge


I hope you liked it.


PVXs — [https://twitter.com/pivixih](https://twitter.com/pivixih)

---

*Originally published on [Medium](https://infosecwriteups.com/webgoat-without-account-challenge-9abbeaf4ba44). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
