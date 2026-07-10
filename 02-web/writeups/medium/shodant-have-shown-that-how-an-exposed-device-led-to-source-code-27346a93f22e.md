# :globe_with_meridians: Shodan’t Have Shown That: How an Exposed Device Led to Source Code 📡📜

---

# Shodan’t Have Shown That: How an Exposed Device Led to Source Code 📡📜

Free Link 🎈

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
