# :globe_with_meridians: Shodan’t Have Shown That: How an Exposed Device Led to Source Code 📡📜

> **Original Source:** [Shodan’t Have Shown That: How an Exposed Device Led to Source Code 📡📜](https://infosecwriteups.com/shodant-have-shown-that-how-an-exposed-device-led-to-source-code-27346a93f22e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Shodan’t Have Shown That: How an Exposed Device Led to Source Code 📡📜


Free [Link](https://medium.com/@iski/shodant-have-shown-that-how-an-exposed-device-led-to-source-code-27346a93f22e?sk=e2739d2842dad3b94b5dc88780f24422) 🎈


Hey there!😁


*Image by Gemini AI*


You know you’ve reached peak hacker mode when your morning routine is:


- Coffee.

- Shodan.

- Accidentally breaking into someone’s DevOps pipeline while still in pajamas. ☕️👷‍


One morning, while I was pretending to be productive (a.k.a. checking memes), I remembered that I hadn’t done a proper Shodan recon in a while. So, I did what every responsible adult does:

>

*I fired up Shodan, typed *`*port:8080 Jenkins*`*, and went treasure hunting.*


Little did I know, I was about to fall face-first into a Jenkins server more open than my Google Docs in 2015.

## Step 1: Mass Recon with Shodan 🧰


To begin, I searched for:


```
port:8080 title:Jenkins country:"IN"
```


Boom. Over 200+ exposed Jenkins servers — some login-protected, most… *not*.

---

*Originally published on [Medium](https://infosecwriteups.com/shodant-have-shown-that-how-an-exposed-device-led-to-source-code-27346a93f22e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
