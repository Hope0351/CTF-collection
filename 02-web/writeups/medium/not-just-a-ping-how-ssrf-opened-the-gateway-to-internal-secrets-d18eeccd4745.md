# :globe_with_meridians: 🚰 Not Just a Ping: How SSRF Opened the Gateway to Internal Secrets 🔓🧠

> **Original Source:** [🚰 Not Just a Ping: How SSRF Opened the Gateway to Internal Secrets 🔓🧠](https://infosecwriteups.com/not-just-a-ping-how-ssrf-opened-the-gateway-to-internal-secrets-d18eeccd4745)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# 🚰 Not Just a Ping: How SSRF Opened the Gateway to Internal Secrets 🔓🧠


Free [Link](https://medium.com/@iski/not-just-a-ping-how-ssrf-opened-the-gateway-to-internal-secrets-d18eeccd4745?sk=237909756b1a90b0397fb7d1c7f9d4e6)🎈


Hey there!😁


*Image by Copilot*


You know that feeling when you poke something *just a little*, and the whole thing falls apart like a Jenga tower?
That’s what this SSRF bug felt like. One small ping… BOOM — internal secrets, cloud keys, and money raining down. 💸😂


If curiosity killed the cat, thank god I’m a hacker, not a cat. 🐱‍💻


Grab your coffee ☕ — here’s the full story of how I *accidentally* became an internal server’s best friend. 🧑‍🤝‍🧑

## 🔍 Phase 1: Recon Recon Recon — The Dating App for Bug Hunters ❤️


I was doing what all serious bounty hunters do:
Mass recon while binge-watching Netflix in the background. 🎬


Here’s how I started:


```
subfinder -d target.com -silent > subs.txt
httpx -l subs.txt -mc 200,302 -title -tech-detect -vhost > live.txt
nuclei -l live.txt -t ssrf -severity high,critical
```

---

*Originally published on [Medium](https://infosecwriteups.com/not-just-a-ping-how-ssrf-opened-the-gateway-to-internal-secrets-d18eeccd4745). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
