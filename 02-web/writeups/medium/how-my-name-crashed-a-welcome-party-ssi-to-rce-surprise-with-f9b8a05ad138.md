# :globe_with_meridians: How My Name Crashed a Welcome Party: SSI to RCE Surprise! with $$$$🎉

> **Original Source:** [How My Name Crashed a Welcome Party: SSI to RCE Surprise! with $$$$🎉](https://infosecwriteups.com/how-my-name-crashed-a-welcome-party-ssi-to-rce-surprise-with-f9b8a05ad138)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How My Name Crashed a Welcome Party: SSI to RCE Surprise! with $$$$🎉


Free [Link](https://medium.com/@iski/how-my-name-crashed-a-welcome-party-ssi-to-rce-surprise-with-f9b8a05ad138?sk=2671fe8019fcedb255246fe02d82f2f4)🎈


Hey there!


*Image by ChatGpt*


Life lesson number 237: If they don’t remember your name, just break the system until they do! 😎


Hi, I’m Iski, and today I bring you a wild ride from a friendly registration form to a full-blown Server-Side Template Injection (SSTI) leading to Remote Code Execution (RCE). Yup, it’s one of those stories where my name quite literally broke the system.

## Recon and Discovery


## The “Hello There” Gone Wrong 🚪


It all started with good ol’ recon. After sifting through endpoints like a detective with a magnifying glass, I came across a sign-up page. While most people enter their names without a second thought, I saw an opportunity.


Here’s where the fun began. Like every responsible bug hunter, I thought, why not see how they handle my name? Instead of using the boring ol’ “Iski,”, I went with the classic test payload:


```
{{7*7}}
```

---

*Originally published on [Medium](https://infosecwriteups.com/how-my-name-crashed-a-welcome-party-ssi-to-rce-surprise-with-f9b8a05ad138). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
