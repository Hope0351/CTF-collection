# :game_die: Natas0 — Wargames solution writeup

> **Original Source:** [Natas0 — Wargames solution writeup](https://infosecwriteups.com/natas0-wargames-solution-writeup-98a7385828c4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Natas0 — Wargames solution writeup


Hello buddies, 🙂 I am Adithya M S and this is my first ever blog on medium.com. I have always been curious about how websites and web services work, thus many a times indulge in observing patterns in URLs when I upload a profile photo, view comments in forums, subscribe to a newsletter, download a software package and so on, in addition to tampering with certain URL and path parameters and observe how the behaviour of the application changes. Here, I would like to start my blog series on solving Wargames Natas challenges.


Wargames is a collection of security challenges hosted on a website called OverTheWire. Natas is a game which is part of Wargames that teaches the basics of server-side web security. Web Servers play a critical role in the secure and efficient implementation of any website or web-based service as it is the role of a server to validate and serve the requests of clients according to their browsers, privilege levels etc.


Each level of Natas provides a small, simple web application that has a single functionality with some vulnerability in it. Exploiting this loophole exposes the password for the next level.


In this blog post, we shall delve into solving the level natas0 from the webpage [https://overthewire.org/wargames/natas/](https://overthewire.org/wargames/natas/)


*This is how the Natas game looks when you visit the URL provided above*


We are now gonna visit the URL shown on this page [http://natas0.natas.labs.overthewire.org/](http://natas0.natas.labs.overthewire.org/) to start level 0 of this game, the introductory web security challenge. Let’s get into it


*Webpage of natas0*


You can see the webpage of natas0 above. It clearly says that the password is on this page. But it does’nt seem to be seen directly on this page. Web pages are specified to the browser via a markup language called HTML. HTML tags (and some stylesheets) are responsible for how content is laid out on a webpage.


## Get Adithya M S’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


HTML markup may also contain comments which do not form any elements shown on the page. We have an option in most modern web browsers to show the source code that forms the page we are currently reading.


Let us view the source code of this page.


Observe the source code carefully.


You can easily see the HTML comment


<! — The password for natas1 is → on the page. (passwords are starred and blurred out to avoid copyright issues. It is pretty simple enough for you guys to try out on your own.)


You may wonder what is the significance of this task and the resulting security “vulnerability” we encountered here, in real world applications. And so did I, a few years ago. What happens is that developers often write comments like these to put their API keys (which are secret pieces of information that provide access to their internal APIs) so that the key can just be copy pasted and the API may be tested easily by developers along with the rest of the application. The problem here is that, they may sometimes forget to remove these secret pieces of data from client side code before pushing their app to production, which may result in access to sensitive company data through the secret APIs being exposed. Bugs like these often can be found quite easily when users are quick to stay updated whenever changes are being made to the application and easy to fix too!! Just remove the comment.


Hope you enjoyed reading this blog post! Please give me 50 claps 👏 if you really liked it. I shall come back very soon with the next blog in this series. Till then, Have a Merry Hacky Christmas 🎄and Happy Breaking!!

---

*Originally published on [Medium](https://infosecwriteups.com/natas0-wargames-solution-writeup-98a7385828c4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
