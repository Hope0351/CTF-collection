# :globe_with_meridians: Behind the Scene of XSS. Some useful links and tricks to bypass XSS

> **Original Source:** [Behind the Scene of XSS. Some useful links and tricks to bypass XSS](https://infosecwriteups.com/behind-the-scene-xss-6a7ff5559b54)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Behind the Scene: XSS(Updated 2025)


Hey Cyberpunks , I hope you all are doing great in your life and if not, then you are at the right place to at least remove the queries of XSS from your life. This article is going to make you somewhere close to perfection (as we all know nobody is perfect :P). So, without wasting any time let’s take a dive into this.

>

Note:- I am going to keep it very simple so that you actually understand #BehindtheScene of XSS. Also, I will not cover the different types of XSS as you can find it anywhere over internet. This Article will talk about the backend process and some techniques to bypass XSS. No bookish language. Just Hackers Language.


[BOOK YOU MUST HAVE : TO BECOME PRO IN PENTRATION TESTING << BEGINNER’S FRIENDLY](https://amzn.to/43UtlAc)


Before we start let’s understand what actually XSS is ?


What the hack is XSS (Cross-Site-Scripting)?XSS is a Client Side Code Injection attack. With that I mean, by embedding malicious code in a genuine web page, the attacker hopes to execute harmful scripts on the victim’s web browser.


I found this image to be helpful to understand the concept clearly. Have a look and try to understand what is actually happening?

---

*Originally published on [Medium](https://infosecwriteups.com/behind-the-scene-xss-6a7ff5559b54). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
