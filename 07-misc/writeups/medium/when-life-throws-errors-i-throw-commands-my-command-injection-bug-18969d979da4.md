# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/when-life-throws-errors-i-throw-commands-my-command-injection-bug-18969d979da4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# When Life Throws Errors, I Throw Commands: My Command Injection Bug🤓


Hey there..! 👋


Free [Link](https://medium.com/@iski/when-life-throws-errors-i-throw-commands-my-command-injection-bug-18969d979da4?sk=a0a09ae439aea58e63fd99e5def3adcc)🎈


I wake up every day hoping to fix my life, but instead, I end up fixing someone else’s web app vulnerabilities. 😅


After a tragic attempt at making breakfast, how my boring day turned into a hacking rollercoaster! 🎢

## 🕵️ The Discovery: Filename or Commandline?


I was casually testing a web app when I stumbled upon a parameter named **filename**. Out of curiosity (and because I had nothing better to do), I entered this:


```
filename=burp.com
```


Guess what? I received an **SMTP request** from my Burp Collaborator server! 💥


At that moment, my brain went:

>

*“Hold on… is this thing vulnerable to Command Injection?!”*


Spoiler alert: It was.


- **“I can’t control my life, but I can control servers with **`**curl**`**."**

## 🔑 The Exploitation: Curling My Way to Victory


I quickly spun up an **ngrok server** to catch outgoing requests:


```
./ngrok http 80
```


Then, I tried injecting a **curl command** into the vulnerable parameter:

---

*Originally published on [Medium](https://infosecwriteups.com/when-life-throws-errors-i-throw-commands-my-command-injection-bug-18969d979da4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
