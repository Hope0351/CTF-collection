# :globe_with_meridians: Flashback Fuzzing: How I Found JWT Tokens in the Past & Got Paid for It

> **Original Source:** [Flashback Fuzzing: How I Found JWT Tokens in the Past & Got Paid for It](https://infosecwriteups.com/flashback-fuzzing-how-i-found-jwt-tokens-in-the-past-got-paid-for-it-8da88d6daf09)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Flashback Fuzzing: How I Found JWT Tokens in the Past & Got Paid for It


— a cyber-thriller story by Harsh Kothari

>

*“Pura system hi hack kar diya.”*
— Me, after scrolling through the past on Wayback Machine.


## Prologue: The Boring Day That Wasn’t


It started like any other day:
Low energy, 3 tabs open, 1 chai down.
I wasn’t looking for a bug. I was looking for *“timepass”*.


So I whispered to myself:

>

“Chalo, kuch endpoints extract karte hai. Kuch toh milega.”


## Act I: The Whisper from the Past


It started as just another routine recon session — me, a cup of chai, and `https://account.proton.me`, a domain from a company renowned for its dedication to online privacy.


I fired up my trusted browser extension to extract API endpoints, expecting the usual list of requests. But then, one endpoint caught my attention — /api/core/v4/auth/jwt


Hmmm. 👀An auth endpoint with ‘jwt’ in it?
That’s either gold… or a ghost town.


But I wasn’t done.
This is where the story turns…

## Act II: “Flashback Fuzzing” Begins


I fed this endpoint into my old friend — Wayback Machine.


>

“Kal ka data, aaj ka attack surface.”


58 snapshots appeared. Some from 2024. Some from 2025.
I clicked on one from May 4, 2025.


Lo and behold.

>

{
“AccessToken”:”u6m7nhrktfiieg2lvko*”,
“UserID”:”D6Gcoc1Suq5e…”,
“ExpiresIn”:1800,
“TokenType”:”Bearer”,
“Scopes”:[“user”,”newssettings”]
}


JWT tokens. Live once. Archived forever.


At this moment, I was:

>

🧠 Thinking: “Is this real?”
💀 Feeling: “Bro, mujhe goosebumps ho rahe hai.”


## Act III: The Risks No One Thought Of


Here’s what was at stake:


⚠️ Risk ‎ — ⚡ Details‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎ ‎
Access Token Exposure — Tokens exposed in plaintext


User Metadata Leaked — Included user IDs, scope, expiration


Session Hijacking Risk — If accessed while live, APIs could’ve been abused


Archive-wide Exposure — 50+ versions = bigger attack surface


Misconfig Evidence — Likely bad caching headers or insecure GET usage

## 😂 Meme Break


Me entering Wayback Machine & finding JWTs in 2025:


>

*“Apun hi bhagwan hai.”*
— Every hacker who pulls tokens from thin air


## I Call It: Flashback Fuzzing


This wasn’t just dumb luck. I followed a method — and now it has a name.

>

Flashback Fuzzing


*Recon that uses past endpoints + archive data to dig out forgotten sensitive responses.*


## Steps:


- Extract API endpoints from JS files or browser tools

- Feed them into Wayback Machine

- Review archived responses

- Look for anything sensitive — tokens, keys, IDs, misconfig clues

- Report. Repeat. Rejoice.

## Act IV: The Responsible Disclosure


I wrote a respectful, clear report to the Proton Security Team.


## Get Harsh kothari’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Told them:


- JWT tokens were publicly accessible from web archives

- They were tied to real scopes like `user` and `newssettings`

- The issue still exists in the archive — a security time bomb

## Act V: The Unexpected Reward


Few days later…


🛎️Inbox pinged.

>

“Thank you for your report… As a token of our appreciation, here’s a $100 coupon to use on Proton services.”


## Takeaways


- Old APIs never die, they just get archived.

- Sensitive data + poor caching = sleeping bugs.

- The past is a goldmine — learn to dig it right.

- Respectful reporting = community respect + rewards 💸

>

We have to uphold the internet’s integrity.


Because…


>

“Jab system fail hota hai, hacker hi system banta hai.”


## Final Thoughts


This wasn’t a CVE. This wasn’t a critical 0-day.


But it was a reminder that recon is an art, and curiosity is your biggest tool.


And

>

“To every silent warrior out there — your time is coming.”


The browser extension i used for endpoint extraction:-

>

[Endpoint Extractor](https://chromewebstore.google.com/detail/endpoint-extractor/jpkbcgdafcpbnjhdaecnakgjoijiecph)


If you loved this story and want more hacking thrillers, memes & methods, follow me or hit me up for collabs.


Jai recon. Jai fuzzing. 🫡
— *Harsh Kothari, aka the Flashback Fuzzer*


🥱 Still reading? You’re a real one.


And since you made it this far…


🎁 Bonus Level Unlocked: The Mentorship Side Quest!


Ever felt like:
*“Bhai, recon toh kar liya… ab aage kya?”*
or
*“Payloads toh hai, but report likhne mein JEE ka paper lagta hai!”*I got you. 🚀

>

*🚀 Offering Free 1:1 Mentorship on Cybersecurity & Bug Hunting!
Stuck somewhere? Just starting out in cyber? Need guidance, feedback, or just want to chat?
I’m also learning every day, and that’s why I’m offering free mentoring sessions — to grow together.📅 Book a session here on Topmate: *[https://topmate.io/cyberhrsh](https://topmate.io/cyberhrsh)*
👨‍💻 Let’s connect on LinkedIn: *[https://www.linkedin.com/in/harshh-kothari](https://www.linkedin.com/in/harshh-kothari)

---

*Originally published on [Medium](https://infosecwriteups.com/flashback-fuzzing-how-i-found-jwt-tokens-in-the-past-got-paid-for-it-8da88d6daf09). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
